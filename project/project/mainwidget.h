#ifndef MAINWIDGET_H
#define MAINWIDGET_H


#include "widget.h"
#include "shopcarwidget.h"
#include "foodwidget.h"
#include <map>

class MainWidget:public Widget
{
public:
    typedef enum MenuBar{
        Bar_One,
        Bar_Two,
        Bar_Three,
        Bar_Four,
        Bar_Five,
    }MenuBar;

    /*桌号*/
    string tableNum;

    /*订单详情信息*/
    string orderInformation;

    MainWidget(const char*bmpName,string tableNum);

    void exec(int sock_fd);

    /*修改菜品数量*/
    int materialChange(std::list<SingleDish>::iterator it,int index,int pos_x,int pos_y,int size);

    /*修改菜品数量-购物车修改*/
    void materialChangeCar(int x,int y);

    /*计算更新订单信息，并展示刷新购物车，包含void showcar()*/
    void countOrder();

    /*订单信息的链表(设计有缺陷)*/
    std::list<string> orderDataList;

    /*订单信息的链表(new)*/
    std::list<SingleDish> orderInfoList;

    /*查找购物车减号选中对象*/
    void findOrderByName(std::string orderName);

    /*全部订单的金额*/
    int order_money;

    /*订单页面的下标*/
    int order_index;

    /*用于购物车数据展示*/
    void showCar();

private:
    //显示购物车
    ShopCarWidget m_car;

    //店长推荐  食物类的对象
    FoodWidget m_oneWidget;
    //特色小炒  食物类的对象
    FoodWidget m_twoWidget;
    //铁板煲  食物类的对象
    FoodWidget m_threeWidget;
    //小吃  食物类的对象
    FoodWidget m_fourWidget;
    //酒水  食物类的对象
    FoodWidget m_fiveWidget;

    //标志位--  当前点击的 菜单栏
    MenuBar m_curBar;
};


#endif