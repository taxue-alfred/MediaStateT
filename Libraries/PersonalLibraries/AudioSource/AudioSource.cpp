//
// Created by Txwh on 2021/8/21.
//
#include "include/AudioSource.h"

////参考：https://blog.csdn.net/u014338577/article/details/107597216

/////-----------------------------音频数据获取------------------------------
bool AudioSource::init(const char *device_name) {
    int ret = -1;
    char *errors = new char[1024];

    //设置日志等级,可以控制控制台输出的信息
    av_log_set_level(AV_LOG_ERROR);
    //注册声音设备
    avdevice_register_all();

    //char *devicename = "video=Integrated Camera";
    //char *devicename = "audio=virtual-audio-capturer";
    //char *devicename = "麦克风 (Realtek High Definition Au)";
    m_pAudioInputFormat = av_find_input_format("dshow");
    options = nullptr;
    m_pAudioFmtCtx = avformat_alloc_context();
    //pkt分配
    pkt = av_packet_alloc();

    ret = avformat_open_input(&m_pAudioFmtCtx, device_name, m_pAudioInputFormat, &options);
    if (ret < 0){
        av_strerror(ret, errors, sizeof(errors));
        fprintf(stderr, "Fail top open audio device, [%d]%s\n", ret ,errors);
        std::cout << "AudioDevice init Error!" << std::endl;
        return false;
    }
    std::cout << "AudioSource:audio have been inited!" << std::endl;
    isAvailable = true;
    return true;
}

uint8_t * AudioSource::read_frame() {
    av_read_frame(m_pAudioFmtCtx, pkt);

    //赋值
    numAvailable = pkt->size;

    return pkt->data;
}

void AudioSource::release_frame() {
    av_packet_unref(pkt);//release frame
}

void AudioSource::release_audio() {
    //close device and release ctx
    avformat_close_input(&m_pAudioFmtCtx);
//    avcodec_free_context(&c_ctx);
    av_dict_free(&options);
    av_packet_free(&pkt);
    av_log(nullptr, AV_LOG_DEBUG, "finish!\n");
    isAvailable = false;
    std::cout << "AudioDevice_FFMPEG have been stopped!" << std::endl;
}
/////-----------------------------音频数据获取结束------------------------------

/////-----------------------------数据操作类------------------------------
void PCMData_handle::PCMDataCopy(unsigned char *pAudioData, int numAvailable) {
    memcpy(PCMDatasource, pAudioData, numAvailable);
    AvailableByteCount = numAvailable;
}

int PCMData_handle::PCMDataCombineTo16Bit() {
    for (int i = 0, j = 0, k = 1; i <  AvailableByteCount / 2; ++i,  j+=2, k+=2) {
        //将高位先进行数据转换
        PCMDataCombine[i] = PCMDatasource[k];
        //将数据左移八位
        PCMDataCombine[i] <<= 8;
        //进行或位运算,结合数据为16位
        PCMDataCombine[i] |= PCMDatasource[j];
    }
    return AvailableByteCount / 2;
}

int PCMData_handle::PCMDataSplit() {
    for (int i = 0, k = 0, j = 1; i < AvailableByteCount / 4; ++i, j+=2, k+=2) {
        //左声道
        PCMDataCombine_left[i] = PCMDataCombine[k];
        //右声道
        PCMDataCombine_right[i] = PCMDataCombine[j];
    }
    return AvailableByteCount / 4;
}
/////-----------------------------数据操作类结束------------------------------