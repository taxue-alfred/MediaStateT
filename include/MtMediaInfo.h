//
// Created by Txwh on 2022/1/7.
//

#ifndef MEDIASTATET_MTMEDIAINFO_H
#define MEDIASTATET_MTMEDIAINFO_H
#include <QObject>
#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <QCoreApplication.h>

#include "Netease_Music_info.h"
#include "FileBasicInformation.h"
#include "StartWithSystem.h"
#include "qhotkey.h"

#include "AudioSource.h"

class MtMediaInfo : public QObject{
    Q_OBJECT

public:
    Netease_Music_info * neteaseMusicInfo = nullptr;
    FileBasicInformation * fileBasicInfo = nullptr;
    StartWithSystem * startWithSystem = nullptr;

private:
    QHotkey * hotkey1 = nullptr;
    QHotkey * hotkey2 = nullptr;
    QHotkey * hotkey3 = nullptr;

public:
    MtMediaInfo(QObject * parent = nullptr);
    ~MtMediaInfo();

signals:
    void music_info_got(QString music_name);
    void player_info_got(QString player_name);

    void ne_file_time_got(QString temp_time);

    void autostart_status(bool value);

    void hot_key_activated(int value);

    void got_mouse_cursor(int x, int y, float dpi);

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
    void NE_file_time();

private:
    std::string NE_path_get();
    //获取程序执行路径
    std::string AppPath_get();
};

#endif //MEDIASTATET_MTMEDIAINFO_H
