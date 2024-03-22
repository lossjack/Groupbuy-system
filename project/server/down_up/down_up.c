#include "down_up.h"

int Down_Calib(int clientfd,const char *buf)
{
    int fp;//open 函数返回值

    char filename [16] ;
    bzero(filename,sizeof(filename));
    sprintf(filename,"%s",buf);

    printf("client要获取的文件名为：%s\n",filename);

    //以只读的模式打开文件
    fp = open(buf,O_RDONLY);
    if (fp == -1)
    {   
        perror("open fail");
        return -1;//打开文件失败返回-1
    }

    char filedate [512];
    int ret_read = read(fp,filedate,512);//从fp中读取数据放到faildate中

    //将faildate发送回clientfd
    if (write(clientfd,filedate,ret_read) != -1)
    {
        close(fp);
        return 1;
    }

    
    return 0;
}


int Up_Calib(int clientfd,const char *buf)
{

    char filename[16];
    char filedate[512];
    bzero(filename,sizeof(filename));
    bzero(filedate,sizeof(filedate));

    //从buf中把名字和数据分离出来
    strncpy(filename,buf,16);//从第0个开始往后16个字符

    strncpy(filedate,buf+16,512);//从第17位开始往后512个字符
    

    printf("client要上传的文件名为：%s\n",filename);

    //以只写模式打开文件
    int fp = open(filename,O_WRONLY|O_CREAT|O_TRUNC,0644);
    if (fp == -1)
    {
        perror("open fail");
        return -1;
    }

    //将从clientfd发送来的数据放入
    int ret_write = write(fp,filedate,strlen(filedate));
    return 0;
}

