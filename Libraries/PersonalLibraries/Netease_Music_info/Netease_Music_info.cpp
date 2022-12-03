//
// Created by Txwh on 2021/8/26.
//
#include "../include/Netease_Music_info.h"

bool Netease_Music_info::NE_Copy_InfoFile(const std::string &inFilePath, const std::string &outFilePath) {
    using namespace std;
    //复制文件，避免影响网易云音乐正常工作
    ////参考代码:https://blog.csdn.net/Carvin_Zh/article/details/45875525
    ////        https://www.cnblogs.com/mfryf/archive/2013/03/17/2964207.html
    ifstream in(inFilePath, ios_base::in|ios_base::binary);
    ofstream out(outFilePath, ios_base::binary);
    if (!in || !out){
        cout << "Netease_Music_info: Copy File Failure." << endl;
        cout << "inFilePath: " << inFilePath << std::endl;
        cout << "outFilePath: " << outFilePath << std::endl;
    }

    //写入文件
    out << in.rdbuf();

    in.close();
    out.close();
    return true;
}

bool Netease_Music_info::GetInfoContent(const std::string &inFilePath) {
    using namespace std;
    using json = nlohmann::json;

    json jMessage;
    ifstream jsonFile(inFilePath);
    if (!jsonFile.is_open()){
        cout << "Netease_Music_info: Open json file failed!" << endl;
        return false;
    }
    //将文件流写入json流
    jsonFile >> jMessage;
    if (jMessage.is_discarded()){
        cout << "Netease_Music_info: Parse json data filed!" << endl;
        return false;
    }
    ////参考：https://zhuanlan.zhihu.com/p/385010367
    //歌曲名称
    json NE_dictionary = jMessage[0];
    json NE_track = NE_dictionary.at("track");
    NE_track.at("name").get_to(music_name);
    json NE_album = NE_track.at("album");
    NE_album.at("picUrl").get_to(album_picUrl);
    //演唱者
    json NE_artist = NE_track.at("artists");
    json NE_artist_info = NE_artist[0];
    NE_artist_info.at("name").get_to(artists_name);
    return true;
}

bool Netease_Music_info::GetAlbumPhoto(const std::string &Img_Url, const std::string &outFilePath) {
    ////参考：https://www.zhihu.com/question/443339832 (Windows)
    ////    https://blog.csdn.net/DaSo_CSDN/article/details/77587916/
    ////    https://stackoom.com/question/3tBtr

    //初始化CURL
    CURL * curl;
    CURLcode res;

    curl = curl_easy_init();
    FILE * photo = fopen(outFilePath.c_str(), "wb");
    if (photo == NULL){
        //文件读取失败
        std::cout << "Netease_Music_info: Album Photo read fail!" << std::endl;
        std::cout << "FilePath: " << outFilePath << std::endl;
    }
    res = curl_easy_setopt(curl, CURLOPT_URL, Img_Url.c_str());
    if (res != CURLE_OK){
        curl_easy_cleanup(curl);
        return false;
    }
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, photo);
    curl_easy_perform(curl);
    fclose(photo);
    curl_easy_cleanup(curl);
    return true;
}

size_t Netease_Music_info::write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}