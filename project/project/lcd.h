#ifndef LCD_H
#define LCD_H

#include <unistd.h>
#include <sys/mman.h> //linux 下的接口
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
 #include <stdio.h>



//源文件 与 头文件之间切换  F4
class Lcd
{
    Lcd(const char*deviceName = "/dev/fb0");
public:
    ~Lcd();

    static Lcd*instance();

    unsigned int* addr();

private:
    int fd;
    unsigned int *lcd_p;

    static Lcd*m_instance;
};



#endif // LCD_H
