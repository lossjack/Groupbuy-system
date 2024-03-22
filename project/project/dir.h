#ifndef DIR_H
#define DIR_H

#include <list>
#include <string>

#include <sys/types.h>
 #include <dirent.h>
#include <cstdio>
#include <errno.h>
#include <string.h>
#include <iostream>

class Dir
{
public:
    Dir();
    //dirName 你要遍历的目录名    suffix 文件过滤器   --也就是筛选 后缀名
    static std::list<std::string> enterInfoList(const char*dirName,const char*suffix = NULL);
};

#endif // DIR_H
