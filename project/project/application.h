#ifndef APPLICATION_H
#define APPLICATION_H

#include "lcd.h"
#include "loginwidget.h"
#include "mainwidget.h"


// 应用 程序管理类 ---管理整个程序
class Application
{
public:
    Application();
    int sock_fd;
    int exec();
};

#endif // APPLICATION_H
