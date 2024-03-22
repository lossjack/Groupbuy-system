#include "widget.h"


Widget::Widget(const char *bmpName,unsigned int *lcd_p)
{
    strcpy(m_bmpName,bmpName);
    m_lcd_p = lcd_p;
}

void Widget::exec()
{
    // 背景 图片的显示
    Bmp bmp(m_bmpName,m_lcd_p);
    bmp.show();
}

void Widget::show()
{

}
