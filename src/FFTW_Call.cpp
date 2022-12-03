//
// Created by Txwh on 2022/1/15.
//

#include "FFTW_Call.h"

bool FFTW_Call::DFT_init(int size_dataAvailableCount) {
    //为fft输入计算分配空间
    in = (double*) fftw_malloc(sizeof(fftw_complex) * size_dataAvailableCount);
    //为fft输出计算分配空间
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * size_dataAvailableCount);
    return true;
}

void FFTW_Call::DFT_start(const short *pAudioData, int size_dataAvailableCount) {
    numSample = size_dataAvailableCount;
    //复制数据
    for (int i = 0; i < size_dataAvailableCount; ++i) {
        in[i] = pAudioData[i];
    }
    //进行DFT变换
    plan = fftw_plan_dft_r2c_1d(size_dataAvailableCount, in, out, FFTW_ESTIMATE);
    //执行变换
    fftw_execute(plan);
    //删除计划，不然会造成内存泄露
    fftw_destroy_plan(plan);
}

int FFTW_Call::DataToFrequencyDomain(){
    for (int i = 0; i < numSample / 2; ++i) {
        double val = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
        ////解释:https://zhidao.baidu.com/question/366315512132574852.html?ivk_sa=1022817r
        val = val / ((double)numSample / 2);
        //写入数组
        DataFrequencyDomain[i] = val;
    }
    return numSample / 2;
}

void FFTW_Call::DFT_free() {
    fftw_free(in);
    fftw_free(out);
}