//
// Created by Txwh on 2021/8/26.
//

#ifndef MEDIASTATE_NETEASE_MUSIC_INFO_H
#define MEDIASTATE_NETEASE_MUSIC_INFO_H

#include "iostream"
#include "fstream"
#include "json.hpp"
#include "curl/curl.h"

class Netease_Music_info{
public:
    //歌曲名称
    std::string music_name;
    //专辑图片链接
    std::string album_picUrl;
    //演唱者名字
    std::string artists_name;
public:
    //复制文件，避免影响网易云音乐正常工作
    bool NE_Copy_InfoFile(const std::string &inFilePath, const std::string &outFilePath);
    //得到文件信息(解析json)
    bool GetInfoContent(const std::string &inFilePath);
    //获取图片
    bool GetAlbumPhoto(const std::string &Img_Url, const std::string &outFilePath);

private:
    //Liburl写入文件函数,必须使用static，这样不会传递self
    static size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
};

#endif //MEDIASTATE_NETEASE_MUSIC_INFO_H
