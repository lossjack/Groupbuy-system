#include "singledish.h"


SingleDish::SingleDish(std::string picName)
{
    m_picName = picName; //菜图片名  ./res/one/蛋肉炒饭-12.bmp

    int startPos = picName.find_last_of('/')+1;
    int endPos = picName.find('-');
    m_name = picName.substr(startPos,endPos-startPos); //菜名   蛋肉炒饭

    //stod --交叉编译器 不支持这个函数
    m_price = picName.substr(endPos+1,picName.find_last_of('.')-endPos-1); //菜价格  12

    m_count = 0;
}
