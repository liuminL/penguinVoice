/*
 * Author: fanmin
 * Date: 2016/07/28
 * Function: 与中心节点结合后的喇叭抽象
*/
#include <ros/ros.h>
#include <std_msgs/String.h>

#include "qisr.h"
#include "qtts.h"
#include "msp_cmn.h"
#include "msp_errors.h"
#include "wav_header.h"
//#include "client/hori_centreClient.h"

#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>


#define	BUFFER_SIZE	4096
#define FRAME_LEN	640
#define HINTS_SIZE  100


/*
ID	38 	接收中心＂暂停＂命令
ID	40 	接收中心＂继续＂命令
ID	39 	发给中心＂已暂停＂消息
ID	41 	发给中心＂正常运行＂消息
ID	42 	发给中心＂播放完成＂消息
ID	43 	发给中心＂正在播放＂消息
*/

//hori_centreClient *cC;

int text_to_speech(const char* src_text, const char* des_path, const char* params)
{
	int          ret          = -1;
	FILE*        fp           = NULL;
	const char*  sessionID    = NULL;
	unsigned int audio_len    = 0;
	wave_pcm_hdr wav_hdr      = default_wav_hdr;
	int          synth_status = MSP_TTS_FLAG_STILL_HAVE_DATA;

	if (NULL == src_text || NULL == des_path)
	{
		printf("params is error!\n");
		return ret;
	}
	fp = fopen(des_path, "wb+");
	if (NULL == fp)
	{
		printf("open %s error.\n", des_path);
		return ret;
	}
	/* 开始合成 */
	sessionID = QTTSSessionBegin(params, &ret);
	if (MSP_SUCCESS != ret)
	{
		printf("QTTSSessionBegin failed, error code: %d.\n", ret);
		fclose(fp);
		return ret;
	}
	ret = QTTSTextPut(sessionID, src_text, (unsigned int)strlen(src_text), NULL);
	if (MSP_SUCCESS != ret)
	{
		printf("QTTSTextPut failed, error code: %d.\n",ret);
		QTTSSessionEnd(sessionID, "TextPutError");
		fclose(fp);
		return ret;
	}
	printf("\n正在合成 ...\n");
	fwrite(&wav_hdr, sizeof(wav_hdr) ,1, fp); //添加wav音频头，使用采样率为16000
	while (!feof(fp))
	{
		/* 获取pcm音频数据 */
		const void* data = QTTSAudioGet(sessionID, &audio_len, &synth_status, &ret);
		if (MSP_SUCCESS != ret)
			break;
		if (NULL != data)
		{
			fwrite(data, audio_len, 1, fp);
		    wav_hdr.data_size += audio_len; //计算data_size大小
		}
		if (MSP_TTS_FLAG_DATA_END == synth_status)
			break;
		printf(">");
		usleep(150*1000); //防止频繁占用CPU
	}//合成状态synth_status取值请参阅《讯飞语音云API文档》
	printf("\n");
	if (MSP_SUCCESS != ret)
	{
		printf("QTTSAudioGet failed, error code: %d.\n",ret);
		QTTSSessionEnd(sessionID, "AudioGetError");
		fclose(fp);
		return ret;
	}
	/* 修正wav文件头数据的大小 */
	wav_hdr.size_8 += wav_hdr.data_size + (sizeof(wav_hdr) - 8);

	/* 将修正过的数据写回文件头部,音频文件为wav格式 */
	fseek(fp, 4, 0);
	fwrite(&wav_hdr.size_8,sizeof(wav_hdr.size_8), 1, fp); //写入size_8的值
	fseek(fp, 40, 0); //将文件指针偏移到存储data_size值的位置
	fwrite(&wav_hdr.data_size,sizeof(wav_hdr.data_size), 1, fp); //写入data_size的值
	fclose(fp);
	fp = NULL;
	/* 合成完毕 */
	ret = QTTSSessionEnd(sessionID, "Normal");
	if (MSP_SUCCESS != ret)
	{
		printf("QTTSSessionEnd failed, error code: %d.\n",ret);
	}

	return ret;
}

void kill_play(std::string wavfile)
{
    pid_t fpid;
    int status;
    fpid = fork();
    if (fpid < 0)
        printf("error in fork!");
    else if (fpid == 0) {
        printf("child process pid : [%d] ,fork[%d]\n",getpid(),fpid);
        system(wavfile.c_str());
        exit(0);
    }
    else{
        printf("father process pid : [%d] ,fork[%d]\n",getpid(),fpid);
        waitpid( fpid, &status, 0 );
        printf("\nchild exit\n");
    }
}



std::string S_command;
void*killPlay(void *arg)
{
	kill_play(S_command);

	//cC->pubToCenter(42);
	return NULL;
}

/* ros的回调函数 */
bool centercommand = true;
bool recognitionFlg = true;
char OUTX[BUFFER_SIZE]	= {'\0'};
void chatterCallback(const std_msgs::String::ConstPtr& msge)
{
	ROS_INFO("text_result is %s:",msge->data.c_str());

		if (msge->data == "warning")
		{
//			cC->pubToCenter(43);
//			cC->pubToCenter(43);
			std::string path = "play ";
			path += getenv("HOME");
			path += "/warning.wav";
			system (path.c_str());
//			cC->pubToCenter(42);
//			cC->pubToCenter(42);
		}
		else if  ( msge->data.length()!=0 &&(centercommand == true))
		{
			printf("\nget the text message...\n");
			strcpy(OUTX,msge->data.c_str()); // 将订阅到的文字赋值给OUTX
			recognitionFlg = false;
		}
	
}
void eventCall(int eve,void *p)
{
	ROS_INFO("get callback [%d]",eve);
	if (eve == 38)
	{
		ROS_INFO("pause");
		centercommand = false;
//		cC->pubToCenter(39);
	}
	if (eve == 40)
	{
		ROS_INFO("continue");
		centercommand = true;
//		cC->pubToCenter(42);
	}
	if (eve == 44)
	{
		ROS_INFO("stop play");
		//centercommand = true;
		system("gnome-terminal -x bash -c 'killall play'");
	}
}

//ke da xun fei pram
    int  ret = MSP_SUCCESS;
  	char pose[BUFFER_SIZE]			=	{'\0'};
  	int  upload_on = 1;
  	const char* login_params = "appid = 5c7e38af, work_dir = ."; // 登录参数，appid与msc库绑定,请勿随意改动 563f0251
  	const char* session_begin_params2 = "voice_name = xiaofeng, text_encoding = UTF8, sample_rate = 16000, speed = 20, volume = 50, pitch = 50, rdn = 2";
  	const char* filename              =  "tts_feedback.wav";

void *main_process(void *arg){
    for(;;){
        if((!recognitionFlg) && centercommand)
	    {
	            std::string::size_type position;
                std::string subs0(OUTX);
	            position = subs0.find("wavefile"); //find函数返回wavfile在s中的下标位置
	            if (position != subs0.npos)
	            {
		            std::cout << "position is : " << position << std::endl;
		            std::string subs1 = subs0.substr(position+8,subs0.size()-8);
		            std::string s_command = "play ";
		            s_command += subs1 + ".wav";
		            S_command = s_command;
//		            cC->pubToCenter(43);
		            system(s_command.c_str());
//		            cC->pubToCenter(42);
	            }
	            else{
	                char *text = OUTX;
	                ret = text_to_speech(text, filename, session_begin_params2);
	                if (MSP_SUCCESS != ret)
	                {
		                printf("text_to_speech failed, error code: %d.\n", ret);
	                }
	                printf("\n合成完毕!\n");
//	                cC->pubToCenter(43);
	                system("play tts_feedback.wav");
//	                cC->pubToCenter(42);
	            }		
	        recognitionFlg = true;
	    }
	   
	    usleep(150*1000);
    }

    return NULL;
}


/* 主函数入口 */
int main(int argc, char **argv)
{
    ros::init(argc, argv, "hori_horn_node");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("/text_result",1, chatterCallback);//获取订阅到的文字，保存到OUTX[]中,from to hori_voicecenter
    ros::Rate loop_rate(100);
   

  	ret = MSPLogin(NULL, NULL, login_params);
  	if (MSP_SUCCESS != ret)
  	{
  		printf("MSPLogin failed , Error code %d.\n",ret);
  		//goto exit; //登录失败，退出登录
  		MSPLogout(); //退出登录
	    return 0;
  	}

	printf("\n#######################################################\n");
	printf("##                hori_horn喇叭节点            ##\n");
	printf("#######################################################\n\n");

//	cC = new hori_centreClient("hori_horn",&n,eventCall,NULL);
//	cC->pubToCenter(41);
	if (centercommand != true)
	{
//		cC->pubToCenter(39);
	}

    pthread_t process_thread;
	int ress = pthread_create (&process_thread, NULL,main_process,NULL);
	if(ress!=0)
	{
	    perror("Thread creation failed!");
		exit(EXIT_FAILURE);
	}

/*while(ros::ok())
{
	

	ros::spinOnce();   //进入chatterback函数,同时接下来执行while(ros::ok())
	loop_rate.sleep();
}*/
    ros::spin();

	MSPLogout(); //退出登录
	return 0;
}
