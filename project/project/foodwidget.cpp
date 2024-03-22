#include "foodwidget.h"
#include "mfont.h"
#include "widget.h"
#include "loginwidget.h"
#include "cstring"
#include "mainwidget.h"

using namespace std;


// 定义一个函数来进行string到char的转换
char* strtochar(std::string str){
    const char *p=str.data();
    char* temp =new char[strlen(p)+1];
    strcpy(temp,p);
    return temp;
}

// 定义一个函数来进行int到char的转换
char* intToChar(int temp) {
    std::string temp_str = std::to_string(temp);
    return strtochar(temp_str);
}

FoodWidget::FoodWidget(){
    
}

FoodWidget::FoodWidget(const char *dirName)
{
    m_index = 0;

    std::list<std::string> foodList = Dir::enterInfoList(dirName,".bmp");

    for(std::list<std::string>::iterator it=foodList.begin(); it!=foodList.end(); it++)
    {
        //std::cout<<*it<<std::endl;
        //插入到链表中
        m_List.push_back(SingleDish(*it));
    }

    for(std::list<SingleDish>::iterator it=m_List.begin(); it!=m_List.end(); it++)
    {
        std::cout<<it->m_name<<"\t"<<it->m_price<<std::endl;
    }

    std::cout<<std::endl;
}

void FoodWidget::show()
{
    //盒子的宽度和高度
    int boxWidth = 170;
    int boxHeight = 160;

    //盒子边框的宽度
    int borderWidth = 5;

    //显示的起始位置
    int startPosX = 255;
    int startPosY = 70;

    //水平和垂直间距
    int spaceX = 10;
    int spaceY = 15;

    std::list<SingleDish>::iterator it;

    //菜图片的Y位置
    int i;
    for(it=m_List.begin(),i=0; it!=m_List.end(); it++,i++)
    {
        // std::cout<<"this is count:"<<it->m_count<<"\t"<<it->m_price<<std::endl;
        //找到对应页的6个数据
        // 第几页    对应链表的数据
        //第0页   0 1 2 3 4 5
        //第1页   6 7 8 9 10 11
        if(m_index*6 == i) 
        {
            //位置1 --盒子图
            Bmp bmp1("./res/frame.bmp");
            bmp1.show(startPosX,startPosY);
            //菜图片
            Bmp bmp11(it->m_picName.data());
            bmp11.show(startPosX+borderWidth,100);

            //菜名
            MFont m(Lcd::instance()->addr());

            m.show(22,100,22,255,255,255,strtochar((it->m_name).data()),0,0,0,320,77);
            //菜价格
            m.show(22,30,22,255,255,255,strtochar((it->m_price).data()),0,0,0,320,203);
            //菜数量
            m.show(22,12,22,255,255,255,intToChar(it->m_count),0,0,0,380,203);

            //位置2
            it++;
            Bmp bmp2("./res/frame.bmp");
            bmp2.show(startPosX+boxWidth+spaceX,startPosY);
            if(it!=m_List.end()){
                //菜图片
                Bmp bmp22(it->m_picName.data());
                bmp22.show(startPosX+boxWidth+spaceX+borderWidth,100);

                //菜名
                m.show(22,100,22,255,255,255,strtochar((it->m_name).data()),0,0,0,500,77);
                //菜价格
                m.show(22,30,22,255,255,255,strtochar((it->m_price).data()),0,0,0,500,203);
                //菜数量
                m.show(22,12,22,255,255,255,intToChar(it->m_count),0,0,0,560,203);
            }else{
                Bmp bmp2("./res/frame.bmp");
                bmp2.show(startPosX+boxWidth+spaceX,startPosY);
                Bmp bmp3("./res/frame.bmp");
                bmp3.show(startPosX+boxWidth*2+spaceX*2,startPosY);
                Bmp bmp4("./res/frame.bmp");
                bmp4.show(startPosX,startPosY+boxHeight+spaceY);
                Bmp bmp5("./res/frame.bmp");
                bmp5.show(startPosX+boxWidth+spaceX,startPosY+boxHeight+spaceY);
                Bmp bmp6("./res/frame.bmp");
                bmp6.show(startPosX+boxWidth*2+spaceX*2,startPosY+boxHeight+spaceY);
                break;
            }

            //位置3
            it++;
            Bmp bmp3("./res/frame.bmp");
            bmp3.show(startPosX+boxWidth*2+spaceX*2,startPosY);

            if(it!=m_List.end()){
                //菜图片
                Bmp bmp33(it->m_picName.data());
                bmp33.show(startPosX+boxWidth*2+spaceX*2+borderWidth,100);
                //菜名
                m.show(22,100,22,255,255,255,strtochar((it->m_name).data()),0,0,0,680,77);
                //菜价格
                m.show(22,30,22,255,255,255,strtochar((it->m_price).data()),0,0,0,680,203);
                //菜数量
                m.show(22,12,22,255,255,255,intToChar(it->m_count),0,0,0,740,203);
            }else{
                Bmp bmp3("./res/frame.bmp");
                bmp3.show(startPosX+boxWidth*2+spaceX*2,startPosY);
                Bmp bmp4("./res/frame.bmp");
                bmp4.show(startPosX,startPosY+boxHeight+spaceY);
                Bmp bmp5("./res/frame.bmp");
                bmp5.show(startPosX+boxWidth+spaceX,startPosY+boxHeight+spaceY);
                Bmp bmp6("./res/frame.bmp");
                bmp6.show(startPosX+boxWidth*2+spaceX*2,startPosY+boxHeight+spaceY);
                break;
            }

            //位置4
            it++;
            Bmp bmp4("./res/frame.bmp");
            bmp4.show(startPosX,startPosY+boxHeight+spaceY);

            if(it!=m_List.end()){
                //菜图片
                Bmp bmp44(it->m_picName.data());
                bmp44.show(startPosX+borderWidth,280);

                m.show(22,100,22,255,255,255,strtochar((it->m_name).data()),0,0,0,320,250);
                //菜价格
                m.show(22,30,22,255,255,255,strtochar((it->m_price).data()),0,0,0,320,379);
                //菜数量
                m.show(22,12,22,255,255,255,intToChar(it->m_count),0,0,0,380,379);
            }else{
                Bmp bmp4("./res/frame.bmp");
                bmp4.show(startPosX,startPosY+boxHeight+spaceY);
                Bmp bmp5("./res/frame.bmp");
                bmp5.show(startPosX+boxWidth+spaceX,startPosY+boxHeight+spaceY);
                Bmp bmp6("./res/frame.bmp");
                bmp6.show(startPosX+boxWidth*2+spaceX*2,startPosY+boxHeight+spaceY);
                break;
            }

            //位置5
            it++;
            Bmp bmp5("./res/frame.bmp");
            bmp5.show(startPosX+boxWidth+spaceX,startPosY+boxHeight+spaceY);

            if(it!=m_List.end()){
                //菜图片
                Bmp bmp55(it->m_picName.data());
                bmp55.show(startPosX+boxWidth+spaceX+borderWidth,280);
                m.show(22,100,22,255,255,255,strtochar((it->m_name).data()),0,0,0,500,250);
                //菜价格
                m.show(22,30,22,255,255,255,strtochar((it->m_price).data()),0,0,0,500,379);
                //菜数量
                m.show(22,12,22,255,255,255,intToChar(it->m_count),0,0,0,560,379);
            }else{
                Bmp bmp5("./res/frame.bmp");
                bmp5.show(startPosX+boxWidth+spaceX,startPosY+boxHeight+spaceY);
                Bmp bmp6("./res/frame.bmp");
                bmp6.show(startPosX+boxWidth*2+spaceX*2,startPosY+boxHeight+spaceY);
                break;
            }

            //位置6
            it++;
            Bmp bmp6("./res/frame.bmp");
            bmp6.show(startPosX+boxWidth*2+spaceX*2,startPosY+boxHeight+spaceY);

            if(it!=m_List.end()){
                //菜图片
                Bmp bmp66(it->m_picName.data());
                bmp66.show(startPosX+boxWidth*2+spaceX*2+borderWidth,280);
                //菜名
                m.show(22,100,22,255,255,255,strtochar((it->m_name).data()),0,0,0,680,250);
                //菜价格
                m.show(22,30,22,255,255,255,strtochar((it->m_price).data()),0,0,0,680,379);
                //菜数量
                m.show(22,12,22,255,255,255,intToChar(it->m_count),0,0,0,740,379);
            }else{
                Bmp bmp6("./res/frame.bmp");
                bmp6.show(startPosX+boxWidth*2+spaceX*2,startPosY+boxHeight+spaceY);
                break;
            }
            break;
        }
    }
}

void FoodWidget::prevIndex()
{
    if(this->m_index > 0)
        this->m_index--;
    FoodWidget::show();
}

void FoodWidget::nextIndex()
{
    if(this->m_index <(m_List.size()/6))
        this->m_index++;
    FoodWidget::show();
}