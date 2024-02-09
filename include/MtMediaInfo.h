//
// Created by Txwh on 2022/1/7.
//

#ifndef MEDIASTATET_MTMEDIAINFO_H
#define MEDIASTATET_MTMEDIAINFO_H
#include <QObject>
#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <cstdio>
#include <QCoreApplication.h>
#include <QCursor>

#include "Netease_Music_info.h"
#include "StartWithSystem.h"
#include "qhotkey.h"
#include "QFileSystemWatcher"

#include "AudioSource.h"

class MtMediaInfo : public QObject{
    Q_OBJECT

public:
    Netease_Music_info * neteaseMusicInfo = nullptr;
    StartWithSystem * startWithSystem = nullptr;
    std::string playApp = "NetEaseMusic";  //默认为QQ音乐，可选NetEaseMusic

private:
    QHotkey * hotkey1 = nullptr;    
    QHotkey * hotkey2 = nullptr;
    QHotkey * hotkey3 = nullptr;
    QFileSystemWatcher * ne_fileSystemWatcher = nullptr;

public:
    MtMediaInfo(QObject * parent = nullptr);
    ~MtMediaInfo();

signals:
    void sig_qml_music_info_get(QString music_name);
    void sig_qml_player_info_get(QString player_name);

    void sig_qml_netease_file_changed();

    void sig_qml_autostart_status(bool value);

    void sig_qml_hot_key_activated(int value);

    void sig_qml_got_mouse_cursor(int x, int y);

public slots:
    void onQmlImgDownload();
    void onQmlMusicInfoGet();
    void onQmlPlayerInfoGet();

    //start with system function
    void on_qml_create_sws();
    void on_qml_check_start_with_system();
    void on_qml_remove_sws();

    //热键slot
    void on_hot_key_call_1();
    void on_hot_key_call_2();
    void on_hot_key_call_3();

    //获取鼠标值
    void on_qml_get_mouse_cursor();

public slots:
    void on_ne_file_changed(const QString & path);

private:
    std::string NE_path_get();
    //获取程序执行路径
    std::string AppPath_get();
};

#endif //MEDIASTATET_MTMEDIAINFO_H
