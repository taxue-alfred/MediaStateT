//
// Created by Txwh on 2022/1/17.
//

#include "MtFrequencyInfo.h"

void MtFrequencyInfo::init(){
    //创建新线程需要重新分配timer，不能在头文件直接创建timer
    timer = new QTimer;

    audioSource.init("audio=virtual-audio-capturer");

    //更新一次音频pcm数据
    update_shake_value();

    fftwCallLeft.DFT_init(pcmDataHandle.AvailableByteCount/4);
    fftwCallRight.DFT_init(pcmDataHandle.AvailableByteCount/4);

    connect(timer, SIGNAL(timeout()), this, SLOT(update_shake_value()));
    connect(timer, SIGNAL(timeout()), this, SLOT(update_bar_value()));

    timer->start(1);

    std::cout << "MtFrequencyInfo: Threading: start" << std::endl;

    isAvailable = true;
}

void MtFrequencyInfo::update_shake_value() {
    uint8_t * pcmSource = audioSource.read_frame();
    audioSource.release_frame();
    pcmDataHandle.PCMDataCopy(pcmSource, audioSource.numAvailable);
    pcmDataHandle.PCMDataCombineTo16Bit();
    available_num = pcmDataHandle.PCMDataSplit();

    tidyFreDataInList();
}

void MtFrequencyInfo::update_bar_value() {
    fftwCallLeft.DFT_start(pcmDataHandle.PCMDataCombine_left, available_num);
    fftwCallRight.DFT_start(pcmDataHandle.PCMDataCombine_right, available_num);
    int available_bar_num = fftwCallLeft.DataToFrequencyDomain();
    fftwCallRight.DataToFrequencyDomain();

    tidyBarDataInList(available_bar_num);
}

void MtFrequencyInfo::tidyFreDataInList() {
    if(shake_left_value.size() != available_num){
        shake_left_value.clear();
        shake_right_value.clear();
        for (int i = 0; i < available_num; ++i) {
            shake_left_value.push_back(*(pcmDataHandle.PCMDataCombine_left + i));
            shake_right_value.push_back(*(pcmDataHandle.PCMDataCombine_right + i));
        }
    }else{
        for (int i = 0; i < available_num; ++i) {
            shake_left_value.replace(i, *(pcmDataHandle.PCMDataCombine_left + i));
            shake_right_value.replace(i, *(pcmDataHandle.PCMDataCombine_right + i));
        }
    }
}

void MtFrequencyInfo::tidyBarDataInList(int &bar_available_num) {
    if(bar_left_value.size() != bar_available_num){
        bar_left_value.clear();
        bar_right_value.clear();
        for (int i = 0; i < bar_available_num; ++i) {
            bar_left_value.push_back((int)*(fftwCallLeft.DataFrequencyDomain + i));
            bar_right_value.push_back((int)*(fftwCallRight.DataFrequencyDomain + i));
        }
    }else{
        for (int i = 0; i < bar_available_num; ++i) {
            bar_left_value.replace(i, (int)*(fftwCallLeft.DataFrequencyDomain + i));
            bar_right_value.replace(i, (int)*(fftwCallRight.DataFrequencyDomain + i));
        }
    }

    //通知上层类，数据已经更新完毕信号
    emit signal_updated_value();
}

void MtFrequencyInfo::destroy() {
    timer->stop();
    fftwCallLeft.DFT_free();
    fftwCallRight.DFT_free();
    audioSource.release_audio();

    delete timer;
    timer = nullptr;

    isAvailable = false;
}
