#include "bmp.h"


Bmp::Bmp(const char *fileName,unsigned int *lcd_p)
{
    memset(m_fileName,0,sizeof(m_fileName));
    memcpy(m_fileName,fileName,strlen(fileName));
    m_lcd_p = lcd_p;

    //获取图片的宽度和高度 和 大小
    int bmpfd = open(fileName,O_RDONLY);
    if(bmpfd == -1)
    {
        printf("fileName:%s\n",fileName);
        perror("open bmpfile error");//perror将错误的原因打印出来
        return ;
    }

    //读取bmp图片的文件头 + 信息头数据
    BITMAPFILEHEADER fileHead;
    BITMAPINFOHEADER infoHead;

    read(bmpfd,&fileHead,14);//读取14个字节
    read(bmpfd,&infoHead,40);//读取40个字节

    m_width = infoHead.biWidth;
    m_height= infoHead.biHeight;
    m_size =  infoHead.biSize;

    close(bmpfd);
}
int Bmp::width(Bmp::BITMAPINFOHEADER *head)
{
    //printf("Width:%d\n",head->biWidth);//图像的宽度
    return head->biWidth;
}

int Bmp::height(Bmp::BITMAPINFOHEADER *head)
{
    //printf("Height:%d\n",head->biHeight);//图像的高度
    return head->biHeight;
}

int Bmp::size(Bmp::BITMAPINFOHEADER *head)
{
   // printf("fileSize:%d\n",head->biSizeImage+54);//文件的大小
    return head->biSizeImage+54;
}

int Bmp::show(int posX, int posY)
{
    int bmpfd = open(m_fileName,O_RDONLY);
    if(bmpfd == -1)
    {
        printf("m_fileName:%s\n",m_fileName);
        perror("open bmpfile error");//perror将错误的原因打印出来
        return -1;
    }

    //读取bmp图片的文件头 + 信息头数据
    BITMAPFILEHEADER fileHead;
    BITMAPINFOHEADER infoHead;

    read(bmpfd,&fileHead,14);//读取14个字节
    read(bmpfd,&infoHead,40);//读取40个字节

    int w = width(&infoHead);
    int h = height(&infoHead);

    char bmpbuf[w*h*3];
    int tempbuf[w*h];
    int i,j;


    //bmp 图片 一个 像素 点  3个字节  BGR
    read(bmpfd,bmpbuf,w*h*3);

    //颜色值顺序  BGR--ARGB
    for(i=0,j=0; i<w*h; i++,j+=3)
    {
        tempbuf[i] = 0x00<<24|bmpbuf[j+2]<<16|bmpbuf[j+1]<<8|bmpbuf[j]<<0;
    }

    //上下颠倒
    for(j=0; j<h; j++)
    {
        for(i=0; i<w; i++)
        {
            m_lcd_p[(j+posY)*800+i+posX] = tempbuf[(h-1-j)*w+i];
        }
    }

    close(bmpfd);
}
Bmp::~Bmp()
{

}
