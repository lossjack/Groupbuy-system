#include "protocol.h"


///////////////////////////////各类型请求的数据帧打包函数/////////////////////////////////////////

/*
函数功能：内部函数，用于做数据的校验累加
*/
static unsigned char __INCP_Calibrate(unsigned char *buf,int len)
{
    unsigned int sum=0;
    for(int i=0;i<len;i++)
    {
        sum+=buf[i];
    }

    return (unsigned char)sum;
}


/*
函数功能:将客户端登录输入的ID及密码打包
参数1：存放打包后数据的容器  需要用户在函数外自定义
参数2：指定输入ID的纯数字字符串
参数3：指定输入的密码串
返回值：成功：返回整包数据帧长度
       失败：基本无  不过严谨的话可以检查传入的3个指针是否为NULL
*/
int INCP_Login(unsigned char *buffer,char *id,char *passw)
{
    /*************固定部分-包头***************/
    //起始标志2Byte
    buffer[0] = 0x89;
    buffer[1] = 0x98;

    //包长度 4Byte
    *(unsigned int *)(&buffer[2]) = 18;

    //请求类型 1Byte
    buffer[6] = PROT_LOGIN;

    /***************可变部分******************/
    //将id纯数字字符串转为 2Byte
    *(unsigned short *)(&buffer[7]) = atoi(id);

    //密码 6Byte
    memcpy((void *)(&buffer[9]),(void *)passw,6);


    /*************固定部分-包尾***************/
    //校验 将本字节前所有字节数据累加 取低八位
    buffer[15] = __INCP_Calibrate(buffer+7,8);

    //结束标志
    buffer[16] = 0xAE;
    buffer[17] = 0xEA;

    return 18;
}

/*
函数功能:将客户端注册账号的请求数据打包
参数1：存放打包后数据的容器  需要用户在函数外自定义
参数2：指定输入昵称  昵称长度最大16Byte
参数3：指定输入的密码串
返回值：成功：返回整包数据帧长度
       失败：基本无  不过严谨的话可以检查传入的3个指针是否为NULL
*/
int INCP_Register(unsigned char *buffer,char *nickname,char *passw)
{
    /*************固定部分-包头***************/
    //起始标志2Byte
    buffer[0] = 0x89;
    buffer[1] = 0x98;

    //包长度 4Byte
    *(unsigned int *)(&buffer[2]) = 18;

    //请求类型 1Byte
    buffer[6] = PROT_REGIS;

    /***************可变部分******************/
    //将昵称存放数据帧缓存中
    memcpy((void *)(&buffer[7]),(void *)nickname,16);

    //密码 6Byte
    memcpy((void *)(&buffer[23]),(void *)passw,6);


    /*************固定部分-包尾***************/
    //校验 将   消息正文  所有字节数据累加 取低八位
    buffer[29] = __INCP_Calibrate(buffer+7,22);

    //结束标志
    buffer[30] = 0xAE;
    buffer[31] = 0xEA;

    return 32;
}


//发送消息请求打包




////////////////////////////////////各类型请求的数据帧的解包函数//////////////////////////////////////

/*
函数功能:获取数据包的各部分内容
参数1：存放收到数据的容器  需要用户在函数外自定义
参数2：传入一个结构体变量地址，用于存放从整帧消息中提取的各项关键信息
    如：请求类型、整包大小、消息正文大小、消息正文内容、校验字节数据 后续可自己拓展
返回值：成功：0
       失败：
            -1：包头异常
            -2：包尾异常
            -3：校验异常
*/
int INCP_GetInfo(unsigned char *buffer,datagram_t *info)
{
    /*************判断固定部分-包头***************/
    //起始标志2Byte 
    if(buffer[0] == 0x89 && buffer[1] == 0x98)
    {
        info->REQ_Len = *((unsigned int *)(buffer+2));//提取整包长度 Byte
        info->REQ_MSGLen = info->REQ_Len-10;//消息正文长度获取 因为固定包头包尾长度为10---后续有拓展内容再修改
        info->REQ_Type   = buffer[6];//请求类型获取
        info->REG_CALIB  = buffer[info->REQ_Len-3];//获取校验字节数据
        
        //包尾标志判断2Byte
        if(buffer[info->REQ_Len-1] == 0xEA &&  buffer[info->REQ_Len-2]==0xAE)
        {
            //数据包尾正常，提取消息正文
            memcpy(info->REG_MSGBuff,buffer+7,info->REQ_MSGLen);
            
            //服务器检查消息正文是否异常--校验对比
            if(__INCP_Calibrate(info->REG_MSGBuff,info->REQ_MSGLen) != info->REG_CALIB)
            {
                //校验成功
                return -3;
            }
        }
        else
        {
            //数据包尾标志异常
            return -2;
        }
    }   
    else
    {
        //数据包头标志异常
        return -1;
    }
    return 0;
}





//应答包打包函数



//应答包解包函数




