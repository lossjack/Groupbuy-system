#include <iostream>


#include "application.h"
#include "widget.h"

extern "C"{
    #include <sys/types.h>          /* See NOTES */
    #include <sys/socket.h>
    #include <unistd.h>
    #include <arpa/inet.h> //AF_INET设置网络信息专属结构体需要的头文件
    #include <string.h>
    #include <netdb.h>
}

using namespace std;


int main()
{
    // int sock_fd = socket(AF_INET,SOCK_STREAM,0);
	// if(sock_fd == -1)
	// {
	// 	perror("socket fail");
	// }
	// printf("网络套接字申请成功[%d]\n",sock_fd);

	// //2、直接connect()连接服务器
	// struct sockaddr_in netinfo;//用来存放IPV4网络信息结构体
	// netinfo.sin_family = AF_INET;
	// netinfo.sin_port = htons(45454);//对方服务器进程的端口号
	// netinfo.sin_addr.s_addr   = inet_addr("192.168.9.47");
	// if(-1 == connect(sock_fd,(struct sockaddr *)&netinfo,sizeof(netinfo)))
	// {
	// 	perror("connect err");
    //     printf("连接服务器失败\n");
	// }else{
    //     printf("连接服务器成功\n");
    // }
	
    Application app;//实例化一个管理类的对象

    return app.exec();
}
