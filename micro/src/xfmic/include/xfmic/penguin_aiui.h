/*
author:yellor	
time  :2019/4/15
*/
#ifndef AIUIAGENTTEST_H_
#define AIUIAGENTTEST_H_

#include "aiui/AIUI.h"


#include <string>
#include <iostream>

#include "FileUtil.h"

#include <unistd.h>
#include <pthread.h>

#define TEST_ROOT_DIR "./AIUI/"

//配置文件打的路径，里面是客户端设置的参数
#define CFG_FILE_PATH "./AIUI/cfg/aiui.cfg"

//测试音频的路径
#define AUDIO_PATH "./AIUI/audio/test.pcm"

#define GRAMMAR_FILE_PATH "./AIUI/asr/call.bnf"

#define LOG_DIR "./AIUI/log"


using namespace aiui;
using namespace std;

#define MAX_PATH	(260)
#define APPID		("5c7e38af")
#define RATE		(16000)
#define CHNS		(1)
#define BITS		(16)
#define FRMSMP		(640)   //帧长度调整
#define BLKCNT		(16)
#define BLKLEN		(FRMSMP*CHNS*BITS/8)
#define DEVICE 		("default")



#define IVW_AUDIO_FILE_NAME "audio/awake.pcm"
#define FRAME_LEN	640 //16k采样率的16bit音频，一帧的大小为640B, 时长20ms

#ifndef PENGUIN_AIUI_H
#define PENGUIN_AIUI_H
/* wav音频头部格式 */
typedef struct _wave_pcm_hdr
{
	char            riff[4];                // = "RIFF"
	int		        size_8;                 // = FileSize - 8
	char            wave[4];                // = "WAVE"
	char            fmt[4];                 // = "fmt "
	int		        fmt_size;				// = 下一个结构体的大小 : 16

	short int       format_tag;             // = PCM : 1
	short int       channels;               // = 通道数 : 1
	int		        samples_per_sec;        // = 采样率 : 8000 | 6000 | 11025 | 16000
	int		   		avg_bytes_per_sec;      // = 每秒字节数 : samples_per_sec * bits_per_sample / 8
	short int       block_align;            // = 每采样点字节数 : wBitsPerSample / 8
	short int       bits_per_sample;        // = 量化比特数: 8 | 16

	char            data[4];                // = "data";
	int				data_size;              // = 纯数据长度 : FileSize - 44
} wave_pcm_hdr;
#endif

//写测试音频线程
class WriteAudioThread
{
private:
	IAIUIAgent* mAgent;

	string mAudioPath;

	bool mRepeat;

	bool mRun;

	FileUtil::DataFileHelper* mFileHelper;

  pthread_t thread_id;
  bool thread_created;

private:
	bool threadLoop();

  static void* thread_proc(void * paramptr);

public:


	WriteAudioThread(IAIUIAgent* agent, const string& audioPath, bool repeat);
	~WriteAudioThread();
	void stopRun();
	bool run();
};


//监听器，SDK通过onEvent（）回调抛出状态，结果等信息
class TestListener : public IAIUIListener
{
private:
	FileUtil::DataFileHelper* mTtsFileHelper;
public:
	//wave_pcm_hdr wav_hdr;
	//void play_pcm_wav();
	//FILE* aiui_fp = NULL;
	void onEvent(const IAIUIEvent& event) const;
	TestListener();
	~TestListener();

};


//测试主类
class AIUITester
{
private:
	IAIUIAgent* agent;

	TestListener  listener;

	WriteAudioThread * writeThread;

	string encode(const unsigned char* bytes_to_encode, unsigned int in_len);

public:
	AIUITester() ;

	~AIUITester();
private:

	void showIntroduction(bool detail);
	//创建AIUI 代理，通过AIUI代理与SDK发送消息通信
	void createAgent();

	//唤醒接口
	void wakeup();

	//开始AIUI，调用stop()之后需要调用此接口才可以与AIUI继续交互
	void start();

	//停止AIUI
	void stop();

	//写音频接口，参数表示是否重复写
	void write(bool repeat);

	void stopWriteThread();

	void reset();

	//写文本接口
	void writeText();

	void syncSchema();

	void querySyncStatus();

	void buildGrammar();

	void updateLocalLexicon();

	//开始tts
	void startTts();

	//暂停tts
	void pauseTts();

	//继续上次的tts
	void resumeTts();

	//取消本次tts
	void cancelTts();

	void destory();

public:
	void readCmd();

	void run();
};
#endif /* AIUIAGENTTEST_H_ */