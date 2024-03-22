/*
文件功能：服务器处理客户端的登录请求的源文件

*/

#include "Login_solv.h"

//注册的相关操作
int Register_Calib(const char *buf)
{
    unsigned short ID = *(unsigned short *)buf;

    for(int i=0;i<count;i++)
    {
        if (users[i].ID == ID)
        {
            printf("用户ID已存在\n");
            return -1;//用户名已经存在
        }
        else 
        {
            memcpy(&users[count].ID,&ID,sizeof(ID));//将用户ID存入
            strcpy(users[count].password,buf+2);//将密码存入
            count++;//人数加1
        }
        
        save_users();            

        return 0;// 成功创建
    }

}


//将用户信息保存到文件users.txt中
void save_users()
{
    FILE *fd = fopen("./users.txt","w+");//读写模式打开
    if (fd == NULL)
    {
        perror("fopan fail");
        while (1);
    }
    
    char buf1[5];
    char buf2[8];

    for (int i = 0; i < count; i++)
    {
        
        sprintf(buf1,"%hd",users[i].ID);
        strcat(buf1,"\n");
        printf("%s\n",buf1);
        fprintf(fd,"%s",buf1);
        
        strcpy(buf2,users[i].password);
        strcat(buf2,"\n");
        printf("%s\n",buf2);
        fprintf(fd,"%s",buf2);
        

    }
    printf("count:%d\n",count);
    fclose(fd);
}


/*
函数功能：根据传入的字符集合，获取其中密码及用户ID,并从本地的用户信息
    文件/数据库中查找比对
参数1：字符集合首地址
返回值：
    成功0
    失败-1：无此用户ID
    失败-2：密码错误
*/
int Login_Calib(const char *buff)
{
    //这里应该从指定的数据库文件或普通文件读取的。这里为了测试
    //将用户信息固定在一个结构体数组中
    unsigned short ID = *(unsigned short *)buff;

    for(int i=0;i<count;i++)
    {
        //先判断是否有该用户
        if(users[i].ID == ID)
        {
            //找到了再判断密码
            if(strcmp(users[i].password,buff+2)==0)   
            {
                return 0;//匹配
            }
            else
            {
                return -2;//密码匹配失败
            }
        }
    }
    
    return -1;//无此用户
}




