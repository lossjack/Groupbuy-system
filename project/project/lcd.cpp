#include "lcd.h"

Lcd*Lcd::m_instance = NULL;

Lcd::Lcd(const char*deviceName )
{
    fd = open(deviceName,O_RDWR);
    if(fd==-1)
    {
        perror("open lcd error");
        return;
    }
    //内存映射
    lcd_p =  reinterpret_cast<unsigned int *>(mmap(NULL, 800*480*4,PROT_READ|PROT_WRITE , MAP_SHARED, fd, 0))  ;
    if(lcd_p == MAP_FAILED)
    {
        perror("mmap error");
    }
}

Lcd::~Lcd()
{
    close(fd);
    munmap(lcd_p,800*480*4);
}

Lcd *Lcd::instance()
{
    if(m_instance == NULL)
    {
        m_instance = new Lcd;
    }

    return m_instance;
}

unsigned int*Lcd::addr()
{
    return lcd_p;
}
