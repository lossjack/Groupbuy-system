#ifndef SINGLEDISH_H
#define SINGLEDISH_H

//字符串类string
#include <string>
#include <iostream>

using namespace std;

// 单个菜品类
class SingleDish
{
public:
    //传递菜图片的路径名  picName  ./res/one/蛋肉炒饭-12.bmp
    SingleDish(std::string picName);
//private:
    std::string m_picName; //菜图片名  ./res/one/蛋肉炒饭-12.bmp
    std::string m_name; //菜名   蛋肉炒饭
    std::string m_price; //菜价格  12
    int m_count ;//用户点的份数
};

#endif // SINGLEDISH_H
