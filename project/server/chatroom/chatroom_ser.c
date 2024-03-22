#include "chatroom_ser.h"

//存放群聊信息的结构体
struct chatroom
{
    unsigned short chat_id;//群聊名称
    char chat_password[7];//群聊密码
    unsigned short chat_userid[30];//群聊内用户名称
    int chat_usernum[30];//群聊内最大人数
};

struct chatroom chatrooms[100] = {{1,"123456",123}};

int chatroom_count = 1;//记录聊天室的数量
int user_count = 1;//记录群聊内用户人数

int Join_Calib(const char *buf)
{
    //获取申请加入的用户名称
    unsigned short ID = *(unsigned short *)buf;

    //获取申请加入的群聊名称
    unsigned short Chat_ID = *(unsigned short *)(buf+2);

    printf("用户：[%d] 申请加入群聊是否同意申请[Y/N] :",ID);
    char Y_N [10];
    scanf("%s",Y_N);
    if (strcmp(Y_N,"Y") == 0)
    {
        printf("同意申请\n");
    }
    else
    {
        printf("拒绝申请\n");
        return -3;
    }
    // printf("user id:%hd\n",ID);
    // printf("room id:%hd\n",Chat_ID);
    // printf("room pass:%s\n",buf+4);

    for (int i = 0; i < chatroom_count; i++)
    {
        printf("user1 id:%hu\n",chatrooms[i].chat_userid[user_count-1]);
        //查询是否有这个群聊
        if (chatrooms[i].chat_id == Chat_ID)
        {
            //对比输入的密码是否正确
            if (strcmp(chatrooms[i].chat_password,buf+4) == 0)
            {
                user_count++;
                memcpy(&chatrooms[i].chat_userid[user_count],&ID,sizeof(ID));//将用户ID添加
                printf("user2 id:%hu\n",chatrooms[i].chat_userid[user_count]);
                return 0;//申请成功
            }
            else
            {
                return -1;//群密码输入错误
            }           
        
        }
        return -2;//没有这个群聊
    }


}

int Create_Calib(const char *buf)
{
    //获取申请创建的用户名称
    unsigned short ID = *(unsigned short *)buf;

    //获取申请创建的群聊名称
    unsigned short Chat_ID = *(unsigned short *)(buf+2);

    //获取群聊密码
    char pass[10];
    bzero(pass,sizeof(pass));
    strncpy(pass,buf+4,6);

    printf("user id:%hd\n",ID);
    printf("room id:%hd\n",Chat_ID);
    printf("room pass:%s\n",pass);

    for (int i = 0; i < chatroom_count; i++)
    {
        //判断群名是否已经存在
        if (chatrooms[i].chat_id == Chat_ID)
        {
            return -1;//群名已经存在
        }
        else
        {
            memcpy(&chatrooms[i].chat_id,&Chat_ID,sizeof(Chat_ID));//将群名存入
            strcpy(chatrooms[i].chat_password,pass);//将密码存入
            memcpy(&chatrooms[i].chat_userid,&ID,sizeof(ID));//将创建群聊用户加入群聊
            user_count++;
        }
    }
    chatroom_count++;
    
    printf("room num:%d\n",chatroom_count);
    //创建文件夹
    char path [30] = "./roomdate/";//初始的文件路径

    //将用户传来的文件名接在后面
    strcat(path,buf+10);
    printf("%s\n",path);

    int ret = mkdir(path,0755);

    if (ret == -1)
    {
        perror("mkdir err");
    }
    
    return 0;//成功创建群聊
}