//
// Created by Txwh on 2022/1/7.
//

#include "MtMediaInfo.h"

MtMediaInfo::MtMediaInfo(QObject * parent) : QObject(parent){
    neteaseMusicInfo = new Netease_Music_info;
    fileBasicInfo = new FileBasicInformation;
    startWithSystem = new StartWithSystem;
    ne_fileSystemWatcher = new QFileSystemWatcher;

    if (playApp == "NetEaseMusic"){
        std::string copy_file_path = "./NE_history.json";
        neteaseMusicInfo->NE_Copy_InfoFile(NE_path_get(), copy_file_path);
        neteaseMusicInfo->GetInfoContent(copy_file_path);
        ne_fileSystemWatcher->addPath(QString::fromStdString(NE_path_get()));
        connect(ne_fileSystemWatcher, SIGNAL(fileChanged(QString)),
                this, SLOT(ne_file_changed(QString)));
    }else if (playApp == "qqMusic"){

    }

    //添加Hotkey
    if (!hotkey1){
        hotkey1 = new QHotkey(QKeySequence("Ctrl+1"), true);
        QObject::connect(hotkey1, &QHotkey::activated, this, &MtMediaInfo::hot_key_call_1);
    }
    if (!hotkey2){
        hotkey2 = new QHotkey(QKeySequence("Ctrl+2"), true);
        QObject::connect(hotkey2, &QHotkey::activated, this, &MtMediaInfo::hot_key_call_2);
    }
    if(!hotkey3){
        hotkey3 = new QHotkey(QKeySequence("Ctrl+3"), true);
        QObject::connect(hotkey3, &QHotkey::activated, this, &MtMediaInfo::hot_key_call_3);
    }
}

std::string MtMediaInfo::NE_path_get() {
    std::string home_path = getenv("HOMEPATH");
    std::replace(home_path.begin(), home_path.end(), '\\', '/');
    std::string disk_signal = "C:";
    std::string path = disk_signal + home_path +
                       std::string("/AppData/Local/Netease/CloudMusic/webdata/file/history");
    return path;
}

std::string MtMediaInfo::AppPath_get() {
     return QCoreApplication::applicationDirPath().toStdString();
}

void MtMediaInfo::music_info_get() {
    if (playApp == "NetEaseMusic"){
        //这里music_info和player_info一般情况下是一起使用的，所以这里复制文件解析json后player_info_get()直接用
        std::string copy_file_path = "./NE_history.json";
        neteaseMusicInfo->NE_Copy_InfoFile(NE_path_get(), copy_file_path);
        neteaseMusicInfo->GetInfoContent(copy_file_path);
        emit music_info_got(QString::fromStdString(neteaseMusicInfo->music_name));
    }else if (playApp == "qqMusic"){

    }
}

void MtMediaInfo::img_download() {
    std::string imgPath = "./album.jpg";
    if (playApp == "NetEaseMusic"){
        neteaseMusicInfo->GetAlbumPhoto(neteaseMusicInfo->album_picUrl,imgPath);
    }else if (playApp == "qqMusic"){
    }
}

void MtMediaInfo::player_info_get() {
    if (playApp == "NetEaseMusic"){
        emit player_info_got(QString::fromStdString(neteaseMusicInfo->artists_name));
    }else if (playApp == "qqMusic"){

    }
}

void MtMediaInfo::ne_file_changed(const QString & path){
    std::string copy_file_path = "./NE_history.json";
    neteaseMusicInfo->NE_Copy_InfoFile(NE_path_get(), copy_file_path);
    neteaseMusicInfo->GetInfoContent(copy_file_path);
    printf("File changed triggered:%s\n", path.toStdString().c_str());
    int64_t temp_time = fileBasicInfo->get_modificationTime(NE_path_get().c_str());
    emit ne_file_time_got(QString::number(temp_time));
}

void MtMediaInfo::create_sws() {
    std::string full_path = startWithSystem->get_programme_path();
    startWithSystem->start_with_system("MediaStateT", full_path);
}

void MtMediaInfo::check_start_with_system() {
    std::string full_path = startWithSystem->get_programme_path();
    int start_symbol = startWithSystem->sws_statue("MediaStateT", full_path);
    if (start_symbol){
        emit autostart_status(true);
    }else{
        emit autostart_status(false);
    }
}

void MtMediaInfo::remove_sws() {
    std::string full_path = startWithSystem->get_programme_path();
    startWithSystem->remove_sws("MediaStateT");
}

void MtMediaInfo::hot_key_call_1() {
    emit hot_key_activated(1);
}

void MtMediaInfo::hot_key_call_2() {
    emit hot_key_activated(2);
}

void MtMediaInfo::hot_key_call_3() {
    emit hot_key_activated(3);
}

void MtMediaInfo::get_mouse_cursor() {
    //参考：https://docs.microsoft.com/zh-cn/windows-hardware/manufacture/desktop/dpi-related-apis-and-registry-settings?view=windows-11
    //https://blog.csdn.net/qq_21743659/article/details/114312564
    POINT p;
    GetCursorPos(&p);
    HWND hd = GetDesktopWindow();
    int zoom = GetDpiForWindow(hd);
    float scale = 0;
    switch(zoom){
        //百分比对应DPI
        case 96:
            scale = 1.0;
            break;
        case 120:
            scale = 1.25;
            break;
        case 150:
            scale = 1.5;
            break;
        case 192:
            scale = 2.0;
            break;
        default:
            scale = 1;
            break;
    }

    emit got_mouse_cursor(p.x, p.y, scale);
}

MtMediaInfo::~MtMediaInfo(){
    delete hotkey1;
    delete hotkey2;
    hotkey1 = nullptr;
    hotkey2 = nullptr;
    delete neteaseMusicInfo;
    delete fileBasicInfo;
    delete startWithSystem;
    neteaseMusicInfo = nullptr;
    fileBasicInfo = nullptr;
    startWithSystem = nullptr;
};