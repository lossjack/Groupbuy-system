/*
文件功能：服务器处理客户端的登录请求的源文件对应头文件
*/

#ifndef __LOGIN_SOLV_H
#define __LOGIN_SOLV_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
// #include "generic.h"

// //测试用
// struct IDPWS
// {
//     unsigned short ID;
//     char passw[7];
// };

// //预设3个用户 用于登录测试
// struct IDPWS testUser[100]={{1,"123456"},{2,"kkkddd"},{152,"kdm123"}};

struct user
{
    unsigned short ID;
    char password[7];
};

struct user users[100] = {{1,"123456"},{2,"kkkddd"},{152,"kdm123"}};
int count = 3;


int Register_Calib(const char *buf);

void save_users();

int  Login_Calib(const char *buff);

#endif
