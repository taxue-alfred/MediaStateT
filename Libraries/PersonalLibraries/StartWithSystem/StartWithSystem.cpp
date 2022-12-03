//
// Created by Txwh on 2022/1/12.
//

#include "include/StartWithSystem.h"

StartWithSystem::StartWithSystem() {
    hkey = NULL;
    programme_full_path = get_programme_path();
    //string转LPCWSTR
    stringToLPCWSTR("MediaStateT", name_w);
    stringToLPCWSTR(programme_full_path, path_w);
    SetWorkDirectory(programme_full_path);
}

std::string StartWithSystem::get_programme_path() {
    TCHAR buffer[512] = {0};
    GetModuleFileName(nullptr, buffer, sizeof(buffer));
    //TCHAR转string
    //参考：https://www.cnblogs.com/staring-hxs/archive/2013/01/24/2874690.html
    UINT len = wcslen(buffer)*2;
    char *buf = (char *)malloc(len);
    UINT i = wcstombs(buf,buffer,len);
    std::string full_path = buf;
    return full_path;
}

void StartWithSystem::stringToLPCWSTR(const std::string &converse_str, PCWCHAR out) {
    // 参考：https://blog.csdn.net/wangshubo1989/article/details/50274103
    wchar_t * buffer = new wchar_t[converse_str.size()+1];
    MultiByteToWideChar(CP_ACP, 0, converse_str.c_str(),
                        converse_str.size(), buffer,
                        converse_str.size() * sizeof(wchar_t));
    buffer[converse_str.size()] = 0;
    //宽字符一个字体两个字节
    memcpy((void *)out, (void *)buffer, (converse_str.size()+1)*sizeof(wchar_t));
    delete [] buffer;
}

bool StartWithSystem::start_with_system(const std::string &name, const std::string &full_path) {
    if (name_w == NULL){
        //string转LPCWSTR
        stringToLPCWSTR(name, name_w);
        std::cout << "hello";
        stringToLPCWSTR(full_path, path_w);
    }

    //打开启动项
    if (RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hkey) == ERROR_SUCCESS){
        //判断注册表项目是否存在
        TCHAR strDir[MAX_PATH] = {};
        DWORD nLength = MAX_PATH;
        // If the function succeeds, the return value is ERROR_SUCCESS.
        // 函数解释：https://docs.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-reggetvaluea
        long result = RegGetValue(hkey, nullptr, name_w, RRF_RT_REG_SZ, 0, strDir, &nLength);

        //注册表已经存在
        if (result != ERROR_SUCCESS) {
            //添加一个Key
            RegSetValueEx(hkey, name_w, 0, REG_SZ, (LPBYTE)path_w,
                          (strlen(full_path.c_str()) + 1) * sizeof(TCHAR));
            //关闭注册表
            RegCloseKey(hkey);
            return true;
        }else{
            std::cout << "StartWithSystem: Have been created!" << std::endl;
            return false;
        }
    }
    else{
        std::cout << "StartWithSystem: Can`t open the Reg!" << std::endl;
        return false;
    }
}

bool StartWithSystem::sws_statue(const std::string &name, const std::string &full_path) {

    if (name_w == NULL){
        //string转LPCWSTR
        stringToLPCWSTR(name, name_w);
        stringToLPCWSTR(full_path, path_w);
    }

    if (RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
                     0, KEY_ALL_ACCESS, &hkey) == ERROR_SUCCESS){

        //判断注册表项目是否存在
        TCHAR strDir[MAX_PATH] = {};
        DWORD nLength = MAX_PATH;
        // If the function succeeds, the return value is ERROR_SUCCESS.
        long result = RegGetValue(hkey, nullptr, name_w, RRF_RT_REG_SZ, 0, strDir, &nLength);

        //注册表已经存在
        if (result != ERROR_SUCCESS) {
            return false;
        }else{
            return true;
        }
    }
    else{
        std::cout << "StartWithSystem: Can`t open the Reg!" << std::endl;
        return false;
    }
}

bool StartWithSystem::remove_sws(const std::string &name) {
    if (name_w == NULL){
        //string转LPCWSTR
        stringToLPCWSTR(name, name_w);
    }
    if (RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hkey) == ERROR_SUCCESS){
        RegDeleteValue(hkey, name_w);
        RegCloseKey(hkey);
        return true;
    }else{
        return false;
    }
}

void StartWithSystem::SetWorkDirectory(std::string & full_path) {
    //参考：https://www.cxyzjd.com/article/qq_42987442/108831931
    std::string workpath_c = full_path;
    //删除最后的xxx.exe
    std::string work_path = workpath_c.substr(0, workpath_c.find_last_of('\\'));
    //设置工作目录
    SetCurrentDirectoryA(work_path.c_str());
}