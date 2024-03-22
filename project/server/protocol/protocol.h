#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include <stdlib.h>
#include <string.h>


enum 
{
    PROT_LOGIN=0, //登录请求
    PROT_REGIS,   //注册新账号请求
    PROT_CREAT,   //创建群组请求
    PROT_APPLY,   //申请入群请求
    PROT_MSGSE,   //消息发送请求
    PROT_FUPLD,   //文件上传请求
    PROT_FDMLD    //文件下载请求
};

//用于解包后存放数据的结构体类型---全部包含
typedef struct 
{
    unsigned char REQ_Type;//请求类型
    unsigned int  REQ_Len ;//整包长度
    unsigned int  REQ_MSGLen;//消息实体长度
    char          REG_MSGBuff[1024];//存放消息实体
    unsigned char REG_CALIB;//校验数据
}datagram_t;


int INCP_Login(unsigned char *buffer,char *id,char *passw);
int INCP_Register(unsigned char *buffer,char *nickname,char *passw);



int INCP_GetInfo(unsigned char *buffer,datagram_t *info);

#endif
