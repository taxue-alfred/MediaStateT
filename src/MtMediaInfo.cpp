//
// Created by Txwh on 2022/1/7.
//

#include "MtMediaInfo.h"

MtMediaInfo::MtMediaInfo(QObject * parent) : QObject(parent){
    neteaseMusicInfo = new Netease_Music_info;
    startWithSystem = new StartWithSystem;
    ne_fileSystemWatcher = new QFileSystemWatcher;

    if (playApp == "NetEaseMusic"){
        ne_fileSystemWatcher->addPath(QString::fromStdString(NE_path_get()));
        connect(ne_fileSystemWatcher, SIGNAL(fileChanged(QString)),
                this, SLOT(on_ne_file_changed(QString)));
    }else if (playApp == "qqMusic"){

    }

    //添加Hotkey
    if (!hotkey1){
        hotkey1 = new QHotkey(QKeySequence("Ctrl+Alt+1"), true);
        QObject::connect(hotkey1, &QHotkey::activated, this, &MtMediaInfo::on_hot_key_call_1);
    }
    if (!hotkey2){
        hotkey2 = new QHotkey(QKeySequence("Ctrl+Alt+2"), true);
        QObject::connect(hotkey2, &QHotkey::activated, this, &MtMediaInfo::on_hot_key_call_2);
    }
    if(!hotkey3){
        hotkey3 = new QHotkey(QKeySequence("Ctrl+Alt+3"), true);
        QObject::connect(hotkey3, &QHotkey::activated, this, &MtMediaInfo::on_hot_key_call_3);
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

void MtMediaInfo::onQmlMusicInfoGet() {
    if (playApp == "NetEaseMusic"){
        //这里music_info和player_info一般情况下是一起使用的，所以这里复制文件解析json后player_info_get()直接用
        std::string copy_file_path = "./NE_history.json";
        neteaseMusicInfo->NE_Copy_InfoFile(NE_path_get(), copy_file_path);
        neteaseMusicInfo->GetInfoContent(copy_file_path);
        emit sig_qml_music_info_get(QString::fromStdString(neteaseMusicInfo->music_name));
    }else if (playApp == "qqMusic"){

    }
}

void MtMediaInfo::onQmlImgDownload() {
    std::string imgPath = "./album.jpg";
    if (playApp == "NetEaseMusic"){
        neteaseMusicInfo->GetAlbumPhoto(neteaseMusicInfo->album_picUrl,imgPath);
    }else if (playApp == "qqMusic"){
    }
}

void MtMediaInfo::onQmlPlayerInfoGet() {
    if (playApp == "NetEaseMusic"){
        emit sig_qml_player_info_get(QString::fromStdString(neteaseMusicInfo->artists_name));
    }else if (playApp == "qqMusic"){

    }
}

void MtMediaInfo::on_ne_file_changed(const QString & path){
    std::string copy_file_path = "./NE_history.json";
    neteaseMusicInfo->NE_Copy_InfoFile(NE_path_get(), copy_file_path);
    neteaseMusicInfo->GetInfoContent(copy_file_path);
    emit sig_qml_netease_file_changed();
}

void MtMediaInfo::on_qml_create_sws() {
    std::string full_path = startWithSystem->get_programme_path();
    startWithSystem->start_with_system("MediaStateT", full_path);
}

void MtMediaInfo::on_qml_check_start_with_system() {
    std::string full_path = startWithSystem->get_programme_path();
    int start_symbol = startWithSystem->sws_statue("MediaStateT", full_path);
    if (start_symbol){
        emit sig_qml_autostart_status(true);
    }else{
        emit sig_qml_autostart_status(false);
    }
}

void MtMediaInfo::on_qml_remove_sws() {
    std::string full_path = startWithSystem->get_programme_path();
    startWithSystem->remove_sws("MediaStateT");
}

void MtMediaInfo::on_hot_key_call_1() {
    emit sig_qml_hot_key_activated(1);
}

void MtMediaInfo::on_hot_key_call_2() {
    emit sig_qml_hot_key_activated(2);
}

void MtMediaInfo::on_hot_key_call_3() {
    emit sig_qml_hot_key_activated(3);
}

void MtMediaInfo::on_qml_get_mouse_cursor() {
    QPoint screen_pos = QCursor::pos();
    emit sig_qml_got_mouse_cursor(screen_pos.x(), screen_pos.y());
}

MtMediaInfo::~MtMediaInfo(){
    delete hotkey1;
    delete hotkey2;
    delete neteaseMusicInfo;
    delete startWithSystem;
};