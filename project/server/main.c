#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h> //AF_INET设置网络信息专属结构体需要的头文件
#include <pthread.h>
#include <string.h>
#include "protocol.h"
#include "down_up.h"
#include "chatroom_ser.h"

void *client_ser(void *arg)
{
    unsigned char recvbuffer[1024];
    int client_fd = (int)arg;
    int ret ;
    struct sockaddr_in netpeerinfo;
    datagram_t Requstinfo; //定义一个用于存放客户端发送过来请求帧数据的结构体变量

    pthread_detach(pthread_self());

    //在当前线程获取对应客户端网络信息
    socklen_t len = sizeof(netpeerinfo);
    getpeername(client_fd,(struct sockaddr *)&netpeerinfo,&len);

    char Rbuf[512]={0};
    while(1)
    {
        memset(Rbuf,0,sizeof(Rbuf));
        /*读取消息*/
        ret = read(client_fd,Rbuf,sizeof(Rbuf));
        if(ret != 0){
            printf("读到客户端消息%s\n",Rbuf);
        }
    }
}



int main()
{
    pthread_t tid;
    struct sockaddr_in netinfo;//用来存放IPV4网络信息结构体

    //1、创建套接字
    int sock_fd = socket(AF_INET,SOCK_STREAM,0);
    if(sock_fd == -1)
    {
        perror("socket fail");
        while(1);
    }
    printf("网络套接字申请成功[%d]\n",sock_fd);

    int val=1;
    if(-1 == setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,&val,4))//设置服务器的IP地址和端口号可
    {
        perror("setsockopt err");
        while(1);
    }
    printf("设置套接字属性成功\n");

    //3、绑定
    netinfo.sin_family = AF_INET;
    netinfo.sin_port   = htons(45454);//0~65535  
    netinfo.sin_addr.s_addr   = htonl(INADDR_ANY);//inet_addr("192.168.60.2");//ubuntu可以一个网卡及IP
    if(-1 == bind(sock_fd,(struct sockaddr *)&netinfo,sizeof(netinfo)))
    {
        perror("bind err");
        while(1);
    }
    printf("服务器设置自己的网络信息成功\n");


    //4、设置监听
    listen(sock_fd,2);

    //4、accpet()
    struct sockaddr_in clientinfo;
    socklen_t addrlen=sizeof(clientinfo);//!!!!!!!!
    while(1)
    {
        int client_fd = accept(sock_fd,(struct sockaddr *)&clientinfo,&addrlen);
        if(client_fd == -1)
        {
            perror("accept fail");
        }

        printf("有新客户端，客户端IP:%s,端口号：%d\n",inet_ntoa(clientinfo.sin_addr),ntohs(clientinfo.sin_port));
        pthread_create(&tid,NULL,client_ser,(void *)client_fd);

    }


    close(sock_fd);//关闭该套接字 （释放内核中申请资源）
}

