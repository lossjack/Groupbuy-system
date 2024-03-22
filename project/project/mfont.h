#ifndef __MFONT_H
#define __MFONT_H

extern "C"{
    #include "font.h"
};

class MFont{
public:
    MFont(unsigned int*lcd_p);
    void show(int fontSize,int bWidth,int bHeight,int bRed,int bGreen,int bBlue,char*text,int fontRed,int fontGreen,int fontBlue,int posX,int posY);
    void show(int fontSize,int bWidth,int bHeight,int bRed,int bGreen,int bBlue,unsigned char *text,int fontRed,int fontGreen,int fontBlue,int posX,int posY);

private:
    unsigned int *m_lcd_p;
};


#endif 