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
    void music_info_got(QString music_name);
    void player_info_got(QString player_name);

    void ne_file_time_got();

    void autostart_status(bool value);

    void hot_key_activated(int value);

    void got_mouse_cursor(int x, int y);

public slots:
    void img_download();
    void music_info_get();
    void player_info_get();

    void create_sws();
    void check_start_with_system();
    void remove_sws();

    //热键slot
    void hot_key_call_1();
    void hot_key_call_2();
    void hot_key_call_3();

    //获取鼠标值
    void get_mouse_cursor();

public slots:
    void ne_file_changed(const QString & path);

private:
    std::string NE_path_get();
    //获取程序执行路径
    std::string AppPath_get();
};

#endif //MEDIASTATET_MTMEDIAINFO_H
