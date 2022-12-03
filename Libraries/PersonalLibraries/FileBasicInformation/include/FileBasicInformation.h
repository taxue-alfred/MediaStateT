//
// Created by Txwh on 2021/8/28.
//

#ifndef MEDIASTATE_FILEBASICINFOMATION_H
#define MEDIASTATE_FILEBASICINFOMATION_H

////参考：https://blog.csdn.net/v6543210/article/details/103463787
////st_mtime：https://blog.csdn.net/zhoulaowu/article/details/14157331
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>

#ifndef WIN32
#include <unistd.h>
#endif

#ifdef WIN32
#define stat _stat
#endif

class FileBasicInformation{
private:
    struct stat result;
public:
    //返回从1970.1.1 00：00：00到文件修改时间的秒数（日历时间），否则返回-1
    int64_t get_modificationTime(const char * FilePath);
};

#endif //MEDIASTATE_FILEBASICINFOMATION_H
