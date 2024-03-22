#include "dir.h"

Dir::Dir()
{

}

std::list<std::string> Dir::enterInfoList(const char *dirName, const char *suffix) //.c  .h  .txt  .bmp
{
    std::list<std::string> list;

     DIR *fp = opendir(dirName);
     if(fp==NULL){
         fprintf(stdout,"%s %s\n",dirName,strerror(errno));
         return list;
     }
     while (1) {
          struct dirent *info = readdir(fp);
          if(info==NULL){
              break;
          }
          //std::cout<<info->d_name<<std::endl;
          //去除.  和..
          if(info->d_name[0] == '.')
              continue;
          //如果是 后缀为.bmp的文件  2014.bmp   1.bmp  zhang3.bmp
          //201.bmp.txt
          int len = strlen(info->d_name);

          if(suffix !=NULL)
          {
              if(strstr(info->d_name,suffix) != NULL)
              {
                  char name[256] = {0};
                  sprintf(name,"%s/%s",dirName,info->d_name);

                  std::cout<<name<<std::endl;

                  //插入到链表中
                  list.push_back(name);
              }
          }
          else{
              char name[256] = {0};
              sprintf(name,"%s/%s",dirName,info->d_name);

              std::cout<<"name:"<<name<<std::endl;

              //插入到链表中
              list.push_back(name);
          }
     }


     closedir(fp);

     return list;
}
