/**
 * 本代码知识文章阅读：https://blog.csdn.net/u011389706/article/details/106306166
 * 示例示范：https://blog.csdn.net/sy84436446/article/details/104216183
 * **/

//
// Created by Txwh on 2022/1/15.
//

#ifndef MEDIASTATET_FFTW_CALL_H
#define MEDIASTATET_FFTW_CALL_H
#include "iostream"
#include "cmath"

extern "C"{
#include "fftw3.h"
};

class FFTW_Call{
private:
    //声明输入指针
    double *in;
    //声明输出指针
    fftw_complex *out;
    //声明"计划"
    fftw_plan plan;

    //声明采样点数(PCM合并16位short后的大小)
    int numSample;
public:
    //定义指X向频域信息的数组
    double DataFrequencyDomain[600] = {0};

public:
    //定义DFT变量,每个数据使用周期只能分配一次，不然会造成内存泄露
    bool DFT_init(int size_dataAvailableCount);
    //DFT开始(r2c)
    void DFT_start(const short *pAudioData, int size_dataAvailableCount);
    //数据处理,输出频域数据,并且返回处理后有效数据个数
    int DataToFrequencyDomain();
    //释放FFTW相关变量
    void DFT_free();
};
#endif //MEDIASTATET_FFTW_CALL_H
