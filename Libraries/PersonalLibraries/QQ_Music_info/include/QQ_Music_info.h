//
// Created by taxue on 2023/7/22.
//

#ifndef MEDIASTATET_QQ_MUSIC_INFO_H
#define MEDIASTATET_QQ_MUSIC_INFO_H

#include "iostream"
#include "json.hpp"
#include "curl/curl.h"

class QQ_Music_info{
public:
    //歌曲名称
    std::string music_name;
    //专辑图片链接
    std::string album_picUrl;
    //演唱者名字
    std::string artists_name;

public:
    bool GetInfoContent(const std::string &inFilePath);
    bool GetAlblumPhoto(const std::string &imgUrl, const std::string outImgPath);

private:
    //Liburl写入文件函数,必须使用static，这样不会传递self
    static size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
};

#endif //MEDIASTATET_QQ_MUSIC_INFO_H
