#ifndef WIDGET_H
#define WIDGET_H

#include <cstring>
#include "lcd.h"
#include "bmp.h"
#include "touch.h"
//设计一个界面基类
class Widget
{
public:
    Widget(const char*bmpName,unsigned int *lcd_p = Lcd::instance()->addr());

    //显示
    void exec();
    void show();

protected:
    char m_bmpName[256];
    unsigned int *m_lcd_p;
};

#endif // WIDGET_H
