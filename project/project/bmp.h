#ifndef BMP_H
#define BMP_H

#include <string.h>

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/mman.h> //内存映射 --linux
#include <stdbool.h>

#include <iostream>


#include "lcd.h"

class Bmp
{
    #define UINT  unsigned short
    #define DWORD unsigned  int
    #define LONG unsigned  int
    #define WORD unsigned short

    #define BMP_WIDTH     800
    #define BMP_HEIGHT     480


    //前面14个字节 文件信息头
    typedef struct tagBITMAPFILEHEADER{
        UINT bfType;  //2
        DWORD bfSize; //DWORD 4
        UINT bfReserved1; //2
        UINT bfReserved2; //2
        DWORD bfOffBits; //DWORD 4
    }BITMAPFILEHEADER;

    //40个字节 位图信息头
    typedef struct tagBITMAPINFOHEADER{ /* bmih */
        DWORD biSize; //DWORD 4  大小
        LONG biWidth; //4  图像的宽度
        LONG biHeight;//4  图像的高度
        WORD biPlanes; //2
        WORD biBitCount;//2 位深    一个像素点占多少个bit位      24位
        DWORD biCompression; //DWORD 4
        DWORD biSizeImage; //DWORD 4
        LONG biXPelsPerMeter;//4
        LONG biYPelsPerMeter;//4
        DWORD biClrUsed; //DWORD 4
        DWORD biClrImportant; //DWORD 4
    }BITMAPINFOHEADER;
public:
    Bmp(const char*fileName,unsigned int*lcd_p = Lcd::instance()->addr());
    ~Bmp();

    int width(BITMAPINFOHEADER *head);//得到bmp图片的宽度
    int height(BITMAPINFOHEADER *head);//得到bmp图片的高度
    int size(BITMAPINFOHEADER *head);//得到bmp图片的大小


    int show(int posX=0,int posY=0);

private:
    unsigned int *m_lcd_p;
    char m_fileName[256];
    int m_width;
    int m_height;
    int m_size;
};

#endif // BMP_H
