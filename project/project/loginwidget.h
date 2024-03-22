#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <string>
#include "widget.h"

class LoginWidget:public Widget
{
public:
    LoginWidget(const char*bmpName);
    std::string tableNumber;
    //显示
    void exec();
};

#endif // LOGINWIDGET_H
