//
// Created by Txwh on 2022/1/12.
//

#ifndef MEDIASTATET_STARTWITHSYSTEM_H
#define MEDIASTATET_STARTWITHSYSTEM_H

#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <stringapiset.h>

class StartWithSystem {
private:
    HKEY hkey;

public:
    std::string programme_full_path;

    //PCWCHAR 是 WCHAR的指针，这里是为了防止内存泄露而不用new
    //所以选择新建非指针变量
    WCHAR name_w[512];
    WCHAR path_w[512];

public:
    StartWithSystem();

    /**
     * @brief: string 转 LPCWSTR
     * @param: 被转换string
     * @param: 存储WCHAR的变量
     * @note:  PCWCHAR是WCHAR的指针
     *  **/
    void stringToLPCWSTR(const std::string &converse_str, PCWCHAR out);

    /**
     * @brief: 获取当前程序运行的绝对路径
     * @return: 返回绝对路径
     * **/
    std::string get_programme_path();

    /**
     * @brief: 添加开机自启项目
     * @param: 开机项目的名称
     * @param: 开机项目的绝对路径
     **/
    bool start_with_system(const std::string &name, const std::string &full_path);

    /**
     * @brief: 检测给定程序名称是否在注册表中
     * @param: 开机项目名称
     * @param: 开机项目的绝对路径
     **/
    bool sws_statue(const std::string &name, const std::string &full_path);

    /**
     * @brief: 移除开机自启项
     * @param: 开机项目的名称
     * **/
    bool remove_sws(const std::string &name);

    /**
     * @brief: 用来设置当前工作目录，解决自动启动导致的工作目录不对的问题
     * @param: 开机项目的绝对路径
    **/
     void SetWorkDirectory(std::string & full_path);
};

#endif //MEDIASTATET_STARTWITHSYSTEM_H
