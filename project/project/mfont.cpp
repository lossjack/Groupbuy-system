#include "mfont.h"

MFont::MFont(unsigned int*lcd_p)
{
    m_lcd_p = lcd_p;
}


void MFont::show(int fontSize,int bWidth,int bHeight,int bRed,int bGreen,int bBlue,char*text,int fontRed,int fontGreen,int fontBlue,int posX,int posY)
{
	//打开字体	
    font *f = fontLoad(const_cast<char*>("/usr/share/fonts/DroidSansFallback.ttf") );
	  
	//字体大小的设置
	fontSetSize(f,fontSize);
	
	
	//创建一个画板（点阵图）-输入框
	bitmap *bm = createBitmapWithInit(bWidth,bHeight,4,getColor(0,bRed,bGreen,bBlue)); //也可使用createBitmapWithInit函数，改变画板颜色
	//bitmap *bm = createBitmap(288, 100, 4);
	
	
	//将字体写到点阵图上
	fontPrint(f,bm,0,0,text,getColor(0,fontRed,fontGreen,fontBlue),0);
	
	//把字体框输出到LCD屏幕上
	show_font_to_lcd(m_lcd_p,posX,posY,bm);

	//关闭字体，关闭画板
	fontUnload(f);
	destroyBitmap(bm);
}
void MFont::show(int fontSize,int bWidth,int bHeight,int bRed,int bGreen,int bBlue,unsigned char *text,int fontRed,int fontGreen,int fontBlue,int posX,int posY)
{
    show( fontSize, bWidth, bHeight, bRed, bGreen, bBlue,(char*)text, fontRed, fontGreen, fontBlue, posX, posY);
}
