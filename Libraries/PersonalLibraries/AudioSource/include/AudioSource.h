//
// Created by Txwh on 2021/8/21.
//

#ifndef AudioSource_H
#define AudioSource_H
#include <iostream>
#include <string>

extern "C" {
#include <libavutil/log.h>
#include <libavcodec/avcodec.h>
#include <libavdevice/avdevice.h>
#include <libavformat/avformat.h>
};

/////-----------------------------音频数据获取------------------------------
class AudioSource{
private:
    const AVInputFormat *m_pAudioInputFormat;
    AVDictionary *options;
    AVFormatContext * m_pAudioFmtCtx;
//    AVCodecContext *c_ctx;
//参考：https://blog.csdn.net/u014338577/article/details/107597216
/**教程里的c_ctx不要去写! 否则release的时候会报空指针错误**/

    AVPacket *pkt;

public:
    //音频总帧大小（BYTE）
    int numAvailable;
    bool isAvailable = false;
public:
    //初始化设备
    //char *devicename = "video=Integrated Camera";
    //char *devicename = "audio=virtual-audio-capturer";
    //char *devicename = "麦克风 (Realtek High Definition Au)";
    bool init(const char *device_name);
    //开始录制，并且返回PCM数据首位的地址
    uint8_t * read_frame();
    //释放pkt
    void release_frame();
    //停止录制并且删除变量
    void release_audio();
};
/////-----------------------------音频数据获取结束------------------------------

/////-----------------------------数据操作类---------------------------------
class PCMData_handle{
public:
    //PCM原数据
    uint8_t PCMDatasource[3000]= {0};

    //PCM高八位低八位合成16位后的数据
    /**@note:先执行PCMDataComBineTo16bit函数这里才会有数据**/
    int16_t PCMDataCombine[1500] = {0};

    //PCM16位合成后的左声道数据
    /**@note:需要先执行声道分离函数**/
    int16_t PCMDataCombine_left[750] = {0};
    //PCM16位合成后的右声道数据
    int16_t PCMDataCombine_right[750] = {0};

    //源PCM数据有效长度
    int AvailableByteCount;
public:
    /**
     * @brief: PCM源数据复制
     * @param: 指向音频数据首地址的指针
     * @param: 获取到的音频数据长度
     * **/
    void PCMDataCopy(unsigned char *pAudioData, int numAvailable);
    //PCM高低八位合成16位,返回合成后数组有效数据大小
    /**@return: 合成后的数据长度**/
    int PCMDataCombineTo16Bit();
    //左右声道分离
    /**@return: 分离后每个声道的数据长度**/
    int PCMDataSplit();
};
/////-----------------------------数据操作类结束------------------------------
#endif //AudioSource_H