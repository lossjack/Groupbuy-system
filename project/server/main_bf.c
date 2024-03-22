// #include <stdio.h>
// #include <sys/types.h>          /* See NOTES */
// #include <sys/socket.h>
// #include <unistd.h>
// #include <arpa/inet.h> //AF_INET设置网络信息专属结构体需要的头文件
// #include <pthread.h>
// #include <string.h>
// #include "protocol.h"
// #include "down_up.h"
// #include "chatroom_ser.h"

// void *client_ser(void *arg)
// {
//     unsigned char recvbuffer[1024];
//     int client_fd = (int)arg;
//     int ret ;
//     struct sockaddr_in netpeerinfo;
//     datagram_t Requstinfo; //定义一个用于存放客户端发送过来请求帧数据的结构体变量

//     pthread_detach(pthread_self());

//     //在当前线程获取对应客户端网络信息
//     socklen_t len = sizeof(netpeerinfo);
//     getpeername(client_fd,(struct sockaddr *)&netpeerinfo,&len);

//     while(1)
//     {
//         memset(recvbuffer,0,sizeof(recvbuffer));
//         memset(&Requstinfo,0,sizeof(Requstinfo));
//         //等待接收客户端各类请求 及做出对应处理
//         ret = read(client_fd,recvbuffer,sizeof(recvbuffer));
//         if(ret == -1)
//         {
//             perror("客户端read失败");
//             continue;
//         }
//         else if(ret >0)
//         {
//             //收到正常的消息  先解包 获取请求类型 再跳转到指定的功能函数处理
//             int ret = INCP_GetInfo(recvbuffer,&Requstinfo);
//             if(ret == 0)
//             {
//                 //一切正常  根据请求类型处理这些消息  并在处理完成后给客户端发送对应应答包
//                 switch(Requstinfo.REQ_Type)
//                 {
//                     case PROT_LOGIN:
//                         //用户ID校验及密码校验及返回结果
//                         ret = Login_Calib(Requstinfo.REG_MSGBuff);
                        
//                         //测试  实际需要按下面2行注释发送给客户端应答包
//                         if(ret == 0)
//                         {
//                             write(client_fd,"Login success!",strlen("Login success!"));
//                         }
//                         else if(ret == -1)
//                         {
//                             write(client_fd,"No this User!",strlen("No this User!"));    
//                         }
//                         else if(ret == -2)
//                         {
//                             write(client_fd,"Passwd is Err!",strlen("Passwd is Err!"));    
//                         }
//                         //根据结果更新服务器中，记录的这些已连接服务器的客户端的信息状态==一般链表记录
                        
//                         //发送当前服务器已注册的项目群组列表给客户端---这个列表附加再应答包数据帧中
//                         break;
                        
//                     case PROT_REGIS:
//                         ret = Register_Calib(Requstinfo.REG_MSGBuff);
//                         if (ret == 0)
//                         {
//                             write(client_fd,"cread success!",strlen("cread success!"));
//                         }
//                         if (ret == -1)
//                         {
//                             write(client_fd,"user ID existed",strlen("user ID existed"));
//                         }

//                         break;

//                     case PROT_CREAT:
//                         ret = Create_Calib(Requstinfo.REG_MSGBuff);
//                         if (ret == 0)
//                         {
//                             write(client_fd, "create success!",strlen("create success!"));
//                         }
//                         if (ret == -1)
//                         {
//                             write(client_fd, "roomid exist!",strlen("roomid exist!"));
//                         }
                        
//                         break;
//                     case PROT_APPLY:
//                         ret = Join_Calib(Requstinfo.REG_MSGBuff);
//                         if (ret == 0)
//                         {
//                             write(client_fd, "join success!",strlen("join success!"));
//                         }
//                         if (ret == -1)
//                         {
//                             write(client_fd, "password err!",strlen("password err!"));
//                         }
//                         if (ret == -2)
//                         {
//                             write(client_fd, "chatroomId err!",strlen("chatroomId err!"));
//                         }
//                         if (ret == -3)
//                         {
//                             write(client_fd, "application rejected!",strlen("application rejected!"));
//                         }
                        
                        
//                         break;
//                     case PROT_FDMLD:                      
//                         ret = Down_Calib(client_fd,Requstinfo.REG_MSGBuff);                       
//                         break;

//                     case PROT_FUPLD:
//                         ret = Up_Calib(client_fd,Requstinfo.REG_MSGBuff);
//                         break;
                    
//                     case PROT_MSGSE:

                        

//                         break;
//                 }
//             }
//             else
//             {
//                 //根据异常情况给客户端发送应答包
//                 switch(ret)
//                 {
//                     case -1://数据包头问题
//                     printf("数据包头问题\n");
//                         break;
//                     case -2://数据包尾问题
//                     printf("数据包尾问题\n");
//                         break;
//                     case -3://数据校验问题
//                     printf("数据效验问题\n");
//                         break;
//                     default:
//                         ;
//                 }
//             }
//         }
//         else if(ret == 0)
//         {
//             printf("客户端%s:%d断开连接\n",inet_ntoa(netpeerinfo.sin_addr),ntohs(netpeerinfo.sin_port));
//             close(client_fd);
//             pthread_exit(NULL);
//         }
//     }
// }



// int main()
// {
//     pthread_t tid;
//     struct sockaddr_in netinfo;//用来存放IPV4网络信息结构体

//     //1、创建套接字
//     int sock_fd = socket(AF_INET,SOCK_STREAM,0);
//     if(sock_fd == -1)
//     {
//         perror("socket fail");
//         while(1);
//     }
//     printf("网络套接字申请成功[%d]\n",sock_fd);

//     int val=1;
//     if(-1 == setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,&val,4))//设置服务器的IP地址和端口号可
//     {
//         perror("setsockopt err");
//         while(1);
//     }
//     printf("设置套接字属性成功\n");

//     //3、绑定
//     netinfo.sin_family = AF_INET;
//     netinfo.sin_port   = htons(45454);//0~65535  
//     netinfo.sin_addr.s_addr   = htonl(INADDR_ANY);//inet_addr("192.168.60.2");//ubuntu可以一个网卡及IP
//     if(-1 == bind(sock_fd,(struct sockaddr *)&netinfo,sizeof(netinfo)))
//     {
//         perror("bind err");
//         while(1);
//     }
//     printf("服务器设置自己的网络信息成功\n");


//     //4、设置监听
//     listen(sock_fd,2);

//     //4、accpet()
//     struct sockaddr_in clientinfo;
//     socklen_t addrlen=sizeof(clientinfo);//!!!!!!!!
//     while(1)
//     {
//         int client_fd = accept(sock_fd,(struct sockaddr *)&clientinfo,&addrlen);
//         if(client_fd == -1)
//         {
//             perror("accept fail");
//         }

//         printf("有新客户端，客户端IP:%s,端口号：%d\n",inet_ntoa(clientinfo.sin_addr),ntohs(clientinfo.sin_port));
//         pthread_create(&tid,NULL,client_ser,(void *)client_fd);

//     }


//     close(sock_fd);//关闭该套接字 （释放内核中申请资源）
// }

