#ifndef FOODWIDGET_H
#define FOODWIDGET_H


#include <iostream>
#include <string>
#include <list>

#include "dir.h"

#include "singledish.h"

#include "bmp.h"

class FoodWidget
{
public:
    FoodWidget(const char*dirName = NULL);
    FoodWidget();

    void show();
    void prevIndex();
    void nextIndex();

    std::list<SingleDish>::iterator getFoodList(){
        std::list<SingleDish>::iterator it = this->m_List.begin();
        return it;
    }

    int& getFoodIndex(){
        return m_index;
    }
    
    //每个菜品 都是 SingleDish类的对象  ---用链表进行存储
    std::list<SingleDish>  m_List;
private:
    //当前的索引页
    int m_index;
};


// 定义一个函数来进行string到char的转换
char* strtochar(std::string str);
#endif // FOODWIDGET_H
