#ifndef TOUCH_H
#define TOUCH_H


#include <iostream>


#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <sys/mman.h>
#include <linux/input.h>//触摸屏头文件

class Touch
{

public:
    //板子的类型
    typedef enum{
        BOARD_TYPE_GEC6818_BLACK, //黑色板子
        BOARD_TYPE_GEC6818_BLUE,//蓝色板子
    }BOARDTYPE;


    Touch(BOARDTYPE type = BOARD_TYPE_GEC6818_BLACK,const char*deviceName = "/dev/input/event0");

    void wait(int &x,int &y);
private:
    int m_x;
    int m_y;
    char m_deviceName[256];
    BOARDTYPE m_type;
};

#endif // TOUCH_H
