/*
author:yellor	
time  :2019/4/15
*/

#include "penguin_aiui.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <jsoncpp/json/json.h>
#include <semaphore.h>
#include "msp_cmn.h"
#include <chrono>
//using namespace VA;
//using namespace std;
//using namespace chrono;
static const string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


//extern wave_pcm_hdr tts_wav_hdr;
int rc;
extern sem_t sem_audio;
extern int chns, readp;
extern unsigned char buf[BLKCNT][BLKLEN];
//音频后端点标识
bool vad_end = false;
chrono::steady_clock::time_point start_time, end_time;
//chrono::steady_clock::duration d_;
//循环写入测试音频
bool WriteAudioThread::threadLoop()
{ 
	//char audio[1280];
	//int len = mFileHelper->read(audio, 1280);
	int len = BLKLEN/chns;
	chrono::steady_clock::duration d_;

	sem_wait(&sem_audio);
	end_time = chrono::steady_clock::now();
	d_ = end_time - start_time;
	//cout << std::chrono::duration_cast<chrono::milliseconds>(d_).count() << endl;
	// convert stereo to mono(left channel)
	if (2 == chns)
		for (rc = 1; rc < FRMSMP; rc++) 
		{
			buf[readp][rc*2+0] = buf[readp][rc*4+0];
			buf[readp][rc*2+1] = buf[readp][rc*4+1];
		}
	//cout<<"vad_end is "<< vad_end<<endl;
	//cout<<"start to Write Audio data"<<endl;
	if ((buf[readp] != NULL) && (vad_end != true))
	{
		Buffer* buffer = Buffer::alloc(len);//申请的内存会在sdk内部释放
		memcpy(buffer->data(), buf[readp], len);
		//cout<<"aiuiwrite!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
		IAIUIMessage * writeMsg = IAIUIMessage::create(AIUIConstant::CMD_WRITE,
			0, 0,  "data_type=audio,sample_rate=16000", buffer);	
		if (NULL != mAgent)
		{
			//cout<<"sendMessage!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
			mAgent->sendMessage(writeMsg);
		}

		readp = (readp + 1) % BLKCNT;		
		writeMsg->destroy();
		usleep(40 * 1000);
	} 
	else 
	{
		//if (mRepeat)
		//{
		//	mFileHelper->rewindReadFile();
		//} 
		//else 
		//{
			IAIUIMessage * stopWrite = IAIUIMessage::create(AIUIConstant::CMD_STOP_WRITE,
				0, 0, "data_type=audio,sample_rate=16000");

			if (NULL != mAgent)
			{
				mAgent->sendMessage(stopWrite);
			}
			stopWrite->destroy();

			cout<<"start to stop Write Audio data"<<endl;

			vad_end = false;
			mFileHelper->closeReadFile();
			mRun = false;
		//}
	}

	return mRun;
}


void* WriteAudioThread::thread_proc(void * paramptr)
{
	WriteAudioThread * self = (WriteAudioThread *)paramptr;
	
	int xx = 0;
	while(xx < 100)
	{
		start_time = chrono::steady_clock::now();
		while (1) 
		{
			if (! self->threadLoop())
				break;
		}
		self->mRun = true;
		xx++;
		cout<<"xx is "<<xx<<endl;
	}
	return NULL;
}

WriteAudioThread::WriteAudioThread(IAIUIAgent* agent, const string& audioPath, bool repeat):
mAgent(agent), mAudioPath(audioPath), mRepeat(repeat), mRun(true), mFileHelper(NULL)
,thread_created(false)
{
	mFileHelper = new FileUtil::DataFileHelper("");
	mFileHelper->openReadFile(mAudioPath, false);
}

WriteAudioThread::~WriteAudioThread()
{
	if (NULL != mFileHelper)
	{
		delete mFileHelper;
		mFileHelper = NULL;
	}
}

void WriteAudioThread::stopRun()
{
    if (thread_created) {
        mRun = false;
        void * retarg;
        pthread_join(thread_id, &retarg);
        thread_created = false;
    }
}

bool WriteAudioThread::run()
{
    if (thread_created == false) {
        int rc = pthread_create(&thread_id, NULL, thread_proc, this);
        if (rc != 0) {
            exit(-1);
        }
        thread_created = true;
        return true;
    }
    return false;
}

string mSyncSid;

const char* aiui_wav_path = "aiui_tts_feedback.wav"; 

int simplest_pcm16le_to_wave(const char *pcmpath, const char *wavepath)
{
		/* 默认wav音频头部数据 */
	wave_pcm_hdr tts_wav_hdr =
	{
		{ 'R', 'I', 'F', 'F' },
		0,
		{'W', 'A', 'V', 'E'},
		{'f', 'm', 't', ' '},
		16,
		1,
		1,
		16000,
		32000,
		2,
		16,
		{'d', 'a', 't', 'a'},
		0
	};
	wave_pcm_hdr wav_hdr = tts_wav_hdr;
	FILE *aiui_wav_fp, *aiui_pcm_fp;
	unsigned char* m_pcmData;

	aiui_wav_fp = fopen(wavepath, "wb+");
	if (aiui_wav_fp == NULL)
	{
		cout<<"open wave file error "<<endl;
		return -1;
	}
	aiui_pcm_fp = fopen(pcmpath, "rb+");
	if (aiui_pcm_fp == NULL)
	{
		cout << "open pcm file error" << endl;
		return -1;
	}
	//fread(m_pcmData, sizeof(unsigned short), 1, aiui_pcm_fp);
	printf("\n正在合成 ...\n");
	fwrite(&wav_hdr, sizeof(wav_hdr) ,1, aiui_wav_fp); //添加wav音频头，使用采样率为16000
	cout<<"wav音频头写完"<<endl;
	while(!feof(aiui_pcm_fp))
	{
		fread(m_pcmData, sizeof(unsigned short), 1, aiui_pcm_fp);
		cout<<"wav音频头写完55555555"<<endl;
		if (m_pcmData != NULL)
		{
			fwrite(m_pcmData, sizeof(unsigned short), 1, aiui_wav_fp);
		    wav_hdr.data_size += sizeof(unsigned short); //计算data_size大小
		}
	}
	/* 修正wav文件头数据的大小 */
	wav_hdr.size_8 += wav_hdr.data_size + (sizeof(wav_hdr) - 8);
	cout<<"wav音频头写完222233333"<<endl;
	/* 将修正过的数据写回文件头部,音频文件为wav格式 */
	fseek(aiui_wav_fp, 4, 0);
	fwrite(&wav_hdr.size_8,sizeof(wav_hdr.size_8), 1, aiui_wav_fp); //写入size_8的值
	fseek(aiui_wav_fp, 40, 0); //将文件指针偏移到存储data_size值的位置
	fwrite(&wav_hdr.data_size,sizeof(wav_hdr.data_size), 1, aiui_wav_fp); //写入data_size的值
	fclose(aiui_wav_fp);
	fclose(aiui_pcm_fp);
	aiui_wav_fp = NULL;
	aiui_pcm_fp = NULL;
	return 0;
	/* 合成完毕 */
}
//事件回调接口，SDK状态，文本，语义结果等都是通过该接口抛出
void TestListener::onEvent(const IAIUIEvent& event) const
{
	switch (event.getEventType()) {
	//SDK 状态回调
	case AIUIConstant::EVENT_STATE:
		{
			switch (event.getArg1()) {
			case AIUIConstant::STATE_IDLE:
				{
					cout << "EVENT_STATE:" << "IDLE" << endl;
				} break;

			case AIUIConstant::STATE_READY:
				{
					cout << "EVENT_STATE:" << "READY" << endl;
				} break;

			case AIUIConstant::STATE_WORKING:
				{
					cout << "EVENT_STATE:" << "WORKING" << endl;
				} break;
			}
		} break;

	//唤醒事件回调
	case AIUIConstant::EVENT_WAKEUP:
		{
			cout << "EVENT_WAKEUP:" << event.getInfo() << endl;
		} break;

	//休眠事件回调
	case AIUIConstant::EVENT_SLEEP:
		{
			cout << "EVENT_SLEEP:arg1=" << event.getArg1() << endl;
		} break;

	//VAD事件回调，如找到前后端点
	case AIUIConstant::EVENT_VAD:
		{
			switch (event.getArg1()) {
			case AIUIConstant::VAD_BOS://前端点
				{
					cout << "EVENT_VAD:" << "BOS" << endl;
				} break;

			case AIUIConstant::VAD_EOS://后端点
				{
					cout << "EVENT_VAD:" << "EOS" << endl;
					
				} break;

			case AIUIConstant::VAD_VOL:
				{
					//						cout << "EVENT_VAD:" << "VOL" << endl;
				} break;
			}
		} break;

	//最重要的结果事件回调
	case AIUIConstant::EVENT_RESULT:
		{
			Json::Value bizParamJson;
			Json::Reader reader;
			
			if (!reader.parse(event.getInfo(), bizParamJson, false)) {
				cout << "parse error!" << endl << event.getInfo() << endl;
				break;
			}
			Json::Value data = (bizParamJson["data"])[0];
			Json::Value params = data["params"];
			Json::Value content = (data["content"])[0];
			string sub = params["sub"].asString();
			//sub字段表示结果的类别，如iat听写，nlp语义结果
			cout << "EVENT_RESULT:" << sub << endl;

			if (sub == "nlp")
			{
				Json::Value empty;
				Json::Value contentId = content.get("cnt_id", empty);

				if (contentId.empty())
				{
					cout << "Content Id is empty" << endl;
					break;
				}

				string cnt_id = contentId.asString();
				int dataLen = 0;
				const char* buffer = event.getData()->getBinary(cnt_id.c_str(), &dataLen);
				string resultStr;

				if (NULL != buffer)
				{
					resultStr = string(buffer, dataLen);

					cout << resultStr << endl;
				}
				else
				{
					cout << "buffer is NULL" << endl;
				}
			} 
			else if (sub == "tts")
			{
				cout << event.getInfo() << endl;

				string cnt_id = content["cnt_id"].asString();

				int dataLen = 0;
				const char* data = event.getData()->getBinary(cnt_id.c_str(), &dataLen);

				cout << "data_len=" << dataLen << endl;

				int dts = content["dts"].asInt();
				cout << "dts=" << dts << endl;

				string errorinfo = content["error"].asString();

				cout << "error info is " << errorinfo << endl;

				if (2 == dts && errorinfo == "AIUI DATA NULL")
				{
					//满足这两个条件的是空结果,不处理,直接丢弃
				}
				else if (3 == dts)
				{
					cout << "tts result receive dts = 3 result" << endl;
					mTtsFileHelper->createWriteFile("tts", ".pcm", false);
					mTtsFileHelper->write((const char*) data, dataLen, 0, dataLen);
					mTtsFileHelper->closeFile();
					//vad_end = true;
				}
				else
				{
					if (0 == dts)   //开始下发PCM
					{
						mTtsFileHelper->createWriteFile("tts", ".pcm", false);
						//mTtsFileHelper->createWriteFile("tts2", ".wav", false);
						//vad_end = true;
						//mTtsFileHelper->write((const char*) wav_hdr, sizeof(wav_hdr), 0, sizeof(wav_hdr));
					}

					mTtsFileHelper->write((const char*) data, dataLen, 0, dataLen);
					//vad_end = true;

					if (2 == dts)
					{
						mTtsFileHelper->closeWriteFile();
						vad_end = true;  //完成一次语义理解下发的PCM完成时间点，即dts=2
						system("sox -t raw -c 1 -e signed-integer -b 16 -r 16000 tts.pcm tts.wav");
						system("play tts.wav");
						//simplest_pcm16le_to_wave("tts.pcm", "tts.wav");
					}
				}
			}

		}
		break;

		//上传资源数据的返回结果
	case AIUIConstant::EVENT_CMD_RETURN:
	{
		//cout << "onEvent --> EVENT_CMD_RETURN: arg1 is " << event.getArg1() << endl;
		if (AIUIConstant::CMD_SYNC == event.getArg1())
		{
			int retcode = event.getArg2();
			int dtype = event.getData()->getInt("sync_dtype", -1);

			//cout << "onEvent --> EVENT_CMD_RETURN: dtype is " << dtype << endl;

			switch (dtype)
			{
				case AIUIConstant::SYNC_DATA_STATUS:
					break;

				case AIUIConstant::SYNC_DATA_ACCOUNT:
					break;

				case AIUIConstant::SYNC_DATA_SCHEMA:
				{
					string sid = event.getData()->getString("sid", "");
					string tag = event.getData()->getString("tag", "");

					mSyncSid = sid;

					if (AIUIConstant::SUCCESS == retcode)
					{
						cout << "sync schema success." << endl;
					} else {
						cout << "sync schema error=" << retcode << endl;
					}

					cout << "sid=" << sid << endl;
					cout << "tag=" << tag << endl;
				} break;

				case AIUIConstant::SYNC_DATA_SPEAKABLE:
					break;

				case AIUIConstant::SYNC_DATA_QUERY://查询结果
				{
					if (AIUIConstant::SUCCESS == retcode)
					{
						cout << "sync status success" << endl;
					} else {
						cout << "sync status error=" << retcode << endl;
					}
				} break;
			}
		} else if (AIUIConstant::CMD_QUERY_SYNC_STATUS == event.getArg1()) {
			int syncType = event.getData()->getInt("sync_dtype", -1);
			if (AIUIConstant::SYNC_DATA_QUERY == syncType)
			{
				string result = event.getData()->getString("result", "");
				cout << "result:" << result << endl;

				if (0 == event.getArg2())
				{
					cout << "sync status:success." << endl;
				} else {
					cout << "sync status error:" << event.getArg2() << endl;
				}
			}
		} else if (AIUIConstant::CMD_BUILD_GRAMMAR == event.getArg1()) {
			if (event.getArg2() == 0)
			{
				cout << "build grammar success." << endl;
			}
			else
			{
				cout << "build grammar error, errcode = " << event.getArg2() << endl;
				cout << "error reasion is " << event.getInfo() << endl;
			}
		} else if (AIUIConstant::CMD_UPDATE_LOCAL_LEXICON == event.getArg1()) {
			if (event.getArg2() == 0)
			{
				cout << "update lexicon success" << endl;
			}
			else
			{
				cout << "update lexicon error, errcode = " << event.getArg2() << endl;
				cout << "error reasion is " << event.getInfo() << endl;
			}
		}
	} break;

	case AIUIConstant::EVENT_ERROR:
		{
			cout << "EVENT_ERROR:" << event.getArg1() << endl;
			cout << " ERROR info is " << event.getInfo() << endl;
		} break;
	}
}

AIUITester::AIUITester() : agent(NULL), writeThread(NULL)
{

}

AIUITester::~AIUITester()
{
	if (agent != NULL)
	{
		agent->destroy();
		agent = NULL;
	}
}

TestListener::TestListener()
{
	mTtsFileHelper = new FileUtil::DataFileHelper("");
}

TestListener::~TestListener()
{
	if (mTtsFileHelper != NULL)
	{
		delete mTtsFileHelper;
		mTtsFileHelper = NULL;
	}
}


void AIUITester::showIntroduction(bool detail)
{
	cout << "demo示例为输入命令，调用对应的函数，使用AIUI SDK完成文本理解，语义理解，文本合成等功能，如：" << endl;
	cout << "c命令，创建AIUI代理，与AIUI SDK交互都是通过代理发送消息的方式进行, 所以第一步必须是输入该命令；" << endl;
	cout << "w命令，发送外部唤醒命令唤醒AIUI，AIUI只有在唤醒过后才可以交互；" << endl;
	cout << "wr命令，单次读取本地pcm音频文件，写入sdk，sdk会返回云端识别的听写，语义结果；" << endl;
	cout << "wrt命令，字符串文本写入sdk，sdk会返回云端识别的语义结果；" << endl;
	cout << "stts命令，单合成示例，返回合成的音频，demo将音频保存为本地的pcm文件；" << endl;
	cout << "help命令，显示本demo提供的示例的介绍；" << endl;

	if (detail)
	{
		cout << "输入c命令后，正常情况返回结果为：" << endl;
		cout << "EVENT_STATE:READY" << endl;
		cout << "输入w命令后，正常情况返回结果为: " << endl;
		cout << "EVENT_WAKEUP:{\"CMScore\":-1,\"angle\":-1,\"beam\":0,\"channel\":-1,\"power\":-1}" << endl;
		cout << "EVENT_STATE:WORKING" << endl;

		cout << "听写，语义，合成等结果在onEvent函数，该函数是结果回调，请仔细研究。" << endl;
	}
}

//创建AIUI代理
void AIUITester::createAgent()
{
	string appid = APPID;
	Json::Value paramJson;
	Json::Value appidJson;

	appidJson["appid"] = appid;
	string fileParam = FileUtil::readFileAsString(CFG_FILE_PATH);
	//cout<<fileParam<<endl;
	Json::Reader reader;

	if(reader.parse(fileParam, paramJson, false))
	{
		paramJson["login"] = appidJson;

		//for ivw support
		string wakeup_mode = paramJson["speech"]["wakeup_mode"].asString();
		//cout<<wakeup_mode<<endl;
		//如果在aiui.cfg中设置了唤醒模式为ivw唤醒，那么需要对设置的唤醒资源路径作处理，并且设置唤醒的libmsc.so的路径为当前路径
		if(wakeup_mode == "ivw")
		{
			//readme中有说明，使用libmsc.so唤醒库，需要调用MSPLogin()先登录
			//string lgiparams = "appid=5c7e38af,engine_start=ivw";
			//MSPLogin(NULL, NULL, lgiparams.c_str());
			string ivw_res_path = paramJson["ivw"]["res_path"].asString();
			if(!ivw_res_path.empty())
			{
				ivw_res_path = "fo|" + ivw_res_path;
				paramJson["ivw"]["res_path"] = ivw_res_path;
			}

			string ivw_lib_path = "libmsc.so";

			paramJson["ivw"]["msc_lib_path"] = ivw_lib_path;
		}
		//end

		Json::FastWriter writer;
		string paramStr = writer.write(paramJson);
		//cout<<"paramStr is "<<paramStr<<endl;
		//cout<<"paramStr.c_str() is "<<paramStr.c_str()<<endl;
		agent = IAIUIAgent::createAgent(paramStr.c_str(), &listener);
		cout<<"aaaaaabbb"<<endl;
	}
	else
	{
		cout << "aiui.cfg has something wrong!" << endl;
	}
}

/*
	外部唤醒接口，通过发送CMD_WAKEUP命令对SDK进行外部唤醒，发送该命令后，SDK会进入working状态，用户就可以与SDK进行交互。
*/
void AIUITester::wakeup()
{
	if (NULL != agent)
	{
		IAIUIMessage * wakeupMsg = IAIUIMessage::create(AIUIConstant::CMD_WAKEUP);
		agent->sendMessage(wakeupMsg);
		wakeupMsg->destroy();
	}
}

//停止AIUI服务，此接口是与stop()对应，调用stop()之后必须调用此接口才能继续与SDK交互，如果你没有调用过stop(),就不需要调用该接口
void AIUITester::start()
{
	if (NULL != agent)
	{
		IAIUIMessage * startMsg = IAIUIMessage::create (AIUIConstant::CMD_START);
		agent->sendMessage(startMsg);
		startMsg->destroy();
	}
}

//停止AIUI服务
void AIUITester::stop()
{
	if (NULL != agent)
	{
		IAIUIMessage *stopMsg = IAIUIMessage::create (AIUIConstant::CMD_STOP);
		agent->sendMessage(stopMsg);
		stopMsg->destroy();
	}
}

//写入测试音频
void AIUITester::write(bool repeat)
{
	if (agent == NULL)
	{
		cout << "write anget == null" << endl;
		return;
	}

	if (writeThread == NULL) {
		writeThread = new WriteAudioThread(agent, AUDIO_PATH,  repeat);
		cout << "writeThread is NULL"<<endl;
		writeThread->run();
	}	
}



void AIUITester::stopWriteThread()
{
	if (writeThread) {
		writeThread->stopRun();
		delete writeThread;
		writeThread = NULL;
	}
}

void AIUITester::reset()
{
	if (NULL != agent)
	{
		IAIUIMessage * resetMsg = IAIUIMessage::create(AIUIConstant::CMD_RESET);
		agent->sendMessage(resetMsg);
		resetMsg->destroy();
	}
}

void AIUITester::buildGrammar()
{
	if (NULL != agent)
	{
		string grammarContent = FileUtil::readFileAsString(GRAMMAR_FILE_PATH);

		IAIUIMessage *grammarMsg = IAIUIMessage::create(AIUIConstant::CMD_BUILD_GRAMMAR, 0, 0, grammarContent.c_str());

		agent->sendMessage(grammarMsg);
		
		grammarMsg->destroy();
	}
}

void AIUITester::updateLocalLexicon()
{
	if (NULL != agent)
	{
		Json::Value paramJson;

		paramJson["name"] = "contact";
		paramJson["content"] = "张山\n李思\n刘得花\n";

		Json::FastWriter writer;
		string paramStr = writer.write(paramJson);

		IAIUIMessage *updateMsg = IAIUIMessage::create(AIUIConstant::CMD_UPDATE_LOCAL_LEXICON, 0, 0, paramStr.c_str(), NULL);     

		agent->sendMessage(updateMsg);

		updateMsg->destroy();
	}
}


//文本语义测试接口
void AIUITester::writeText()
{
	if (NULL != agent)
	{
		string text = "刘德华的歌。";
		// textData内存会在Message在内部处理完后自动release掉
		Buffer* textData = Buffer::alloc(text.length());
		text.copy((char*) textData->data(), text.length());

		IAIUIMessage * writeMsg = IAIUIMessage::create(AIUIConstant::CMD_WRITE,
			0,0, "data_type=text", textData);	

		agent->sendMessage(writeMsg);
		writeMsg->destroy();		
	}
}

string AIUITester::encode(const unsigned char* bytes_to_encode, unsigned int in_len) {
	std::string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (in_len--) {
		char_array_3[i++] = *(bytes_to_encode++);
		if (i == 3) {
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for(i = 0; (i <4) ; i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i)
	{
		for(j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while((i++ < 3))
			ret += '=';

	}

	return ret;
}

//动态上传资源数据
void AIUITester::syncSchema()
{
	if (NULL != agent)
	{
		Json::Value paramsJson;
		paramsJson["tag"] = "tag_abc";

		Json::Value dataParamJson;
		dataParamJson["id_name"] = "uid";
		dataParamJson["res_name"] = "IFLYTEK.telephone_contact";

		string rawData = "{\"name\":\"程序员\", \"alias\":\"开发\"}\n";
		rawData.append("{\"name\":\"设计师\", \"alias\":\"设计\"}\n");
		rawData.append("{\"name\":\"产品经理\", \"alias\":\"产品\"}");

		string rawDataBase64 = encode((const unsigned char*) rawData.c_str(),
												rawData.length());

		Json::Value dataJson;
		dataJson["param"] = dataParamJson;
		dataJson["data"] = rawDataBase64;

		Json::FastWriter writer;

		string dataStr = writer.write(dataJson);
		string params = writer.write(paramsJson);

		Buffer* dataBuffer = Buffer::alloc(dataStr.length());
		dataStr.copy((char*) dataBuffer->data(), dataStr.length());

		IAIUIMessage * syncMsg = IAIUIMessage::create(AIUIConstant::CMD_SYNC,
			AIUIConstant::SYNC_DATA_SCHEMA, 0, params.c_str(), dataBuffer);

		agent->sendMessage(syncMsg);

		syncMsg->destroy();
	}
}

//查询数据同步状态
void AIUITester::querySyncStatus()
{
	if (NULL != agent)
	{
		Json::Value paramJson;

		//参数包含需要对应同步上传操作的sid
		cout << "query sid is " << mSyncSid << endl;
		paramJson["sid"] = mSyncSid;

		Json::FastWriter writer;
		string paramStr = writer.write(paramJson);

		IAIUIMessage * querySyncMsg = IAIUIMessage::create(AIUIConstant::CMD_QUERY_SYNC_STATUS,
			AIUIConstant::SYNC_DATA_SCHEMA, 0, paramStr.c_str(), NULL);

		agent->sendMessage(querySyncMsg);

		querySyncMsg->destroy();
	}
}

//语音单独合成示例，开始合成
void AIUITester::startTts()
{
	if (NULL != agent)
	{
		string text = "科大讯飞作为中国最大的智能语音技术提供商，在智能语音技术领域有着长期的研究积累，"
				"并在中文合成、语音识别、口语评测等多项技术上拥有国际领先的成果。科大讯飞是我多唯一以语音技"
				"术为产业化方向的“国家863计划成果产业基地”。";

		Buffer* textData = Buffer::alloc(text.length());
		text.copy((char*) textData->data(), text.length());

		/*
		 arg1取值说明：
			START	开始合成	合成发音人，语速语调等
			CANCEL	取消合成	无
			PAUSE	暂停播放	无
			RESUME	恢复播放	无
		*/

		/*
		合成参数示例：
		String params = "vcn=xiaoyan,speed=50,pitch=50,volume=50"

		参数字段说明：
			vcn	发音人，如xiaoyan
			speed	速度，0-100
			pitch	语调，0-100
			volume	音量，0-100
			ent	引擎，默认aisound，如果需要较好的效果，可设置成xtts
		*/
		string paramStr = "vcn=xiaoyan";
		paramStr += ",speed=50";
		paramStr += ",pitch=40";
		paramStr += ",volume=60";

		IAIUIMessage * ttsMsg = IAIUIMessage::create(AIUIConstant::CMD_TTS,
			AIUIConstant::START, 0, paramStr.c_str(), textData);

		agent->sendMessage(ttsMsg);

		ttsMsg->destroy();
	}
}

//暂停本次合成
void AIUITester::pauseTts()
{
	if (NULL != agent)
	{
		IAIUIMessage * ttsMsg = IAIUIMessage::create(AIUIConstant::CMD_TTS,
			AIUIConstant::PAUSE, 0, "", NULL);

		agent->sendMessage(ttsMsg);

		ttsMsg->destroy();
	}
}

//继续暂停的合成
void AIUITester::resumeTts()
{
	if (NULL != agent)
	{
		IAIUIMessage * ttsMsg = IAIUIMessage::create(AIUIConstant::CMD_TTS,
			AIUIConstant::RESUME, 0, "", NULL);

		agent->sendMessage(ttsMsg);

		ttsMsg->destroy();
	}
}

//取消本次合成
void AIUITester::cancelTts()
{
	if (NULL != agent)
	{
		IAIUIMessage * ttsMsg = IAIUIMessage::create(AIUIConstant::CMD_TTS,
			AIUIConstant::CANCEL, 0, "", NULL);

		agent->sendMessage(ttsMsg);

		ttsMsg->destroy();
	}
}

void AIUITester::destory()
{
	stopWriteThread();

	if (NULL != agent)
	{
		agent->destroy();
		agent = NULL;
	}
}

//接收用户输入命令，调用不同的测试接口
void AIUITester::readCmd()
{
	showIntroduction(false);

	cout << "input cmd:" << endl;

	string cmd;
	while (true)
	{
		cin >> cmd;

		if (cmd == "c")
		{
			cout << "createAgent" << endl;
			createAgent();
		} else if (cmd == "w") {
			cout << "wakeup" << endl;
			wakeup();
		} else if (cmd == "s") {
			cout << "start" << endl;
			start();
		} else if (cmd == "st") {
			cout << "stop" << endl;
			stop();
		} else if (cmd == "d") {
			cout << "destroy" << endl;
			destory();
		} else if (cmd == "r") {
			cout << "reset" << endl;
			reset();
		} else if (cmd == "e") {
			cout << "exit" << endl;
			break;
		} else if (cmd == "wr") {
			cout << "write" << endl;
			write(false);
		} else if (cmd == "wrr") {
			cout << "write repeatly" << endl;
			write(true);
		} else if (cmd == "swrt") {
			cout << "stopWriteThread" << endl;
			stopWriteThread();
		} else if (cmd == "wrt") {
			cout << "writeText" << endl;
			writeText();
		} else if (cmd == "q") {
			destory();
			break;
		} else if (cmd == "ssm") {
			cout << "syncSchema" << endl;
			syncSchema();
		} else if (cmd == "qss") {
			cout << "querySyncStatus" << endl;
			querySyncStatus();
		} else if (cmd == "stts") {
			cout << "startTts" << endl;
			startTts();
		} else if (cmd == "ptts") {
			cout << "pauseTts" << endl;
			pauseTts();
		} else if (cmd == "rtts") {
			cout << "resumeTts" << endl;
			resumeTts();
		} else if (cmd == "ctts") {
			cout << "cancelTts" << endl;
			cancelTts();
		} else if (cmd == "help") {
			showIntroduction(true);
		} else {
			cout << "invalid cmd, input again." << endl;
		}
	}
}

void AIUITester::run()
{
	AIUISetting::setAIUIDir(TEST_ROOT_DIR);
	AIUISetting::initLogger(LOG_DIR);


	//readCmd();
	createAgent();
	usleep(10000);
	//cout<<"hello run "<<endl;
	wakeup();
	usleep(10000);
	while(1)
		write(false);
}
