//
// Created by Txwh on 2021/8/28.
//
#include "../include/FileBasicInformation.h"

int64_t FileBasicInformation::get_modificationTime(const char *FilePath) {
    if (stat(FilePath, &result) == 0){
        auto mod_time = result.st_mtime;
        return mod_time;
    }
    return -1;
}
