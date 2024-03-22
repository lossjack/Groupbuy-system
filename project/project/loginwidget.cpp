#include "loginwidget.h"
#include "mfont.h"
#include "foodwidget.h"


LoginWidget::LoginWidget(const char *bmpName):Widget(bmpName)
{

}

void LoginWidget::exec()
{
    this->tableNumber = "";
    Bmp bmp(m_bmpName,m_lcd_p);
    bmp.show();
    MFont m(m_lcd_p);
    m.show(40,260,60,255,255,255,strtochar(this->tableNumber),0,0,0,50,330);

    while(1){
        int x,y;
        Touch touch;
        touch.wait(x,y);
        //数字1
        if (x>410 && x<510 && y>90 && y<170){
            std::cout<<"1"<<std::endl;
            this->tableNumber = this->tableNumber+"1";
            m.show(40,260,60,255,255,255,strtochar(this->tableNumber),0,0,0,50,330);
        }
        //数字2
        if (x>540 && x<640 && y>90 && y<170){
            std::cout<<"2"<<std::endl;
            this->tableNumber = this->tableNumber+"2";
            m.show(40,260,60,255,255,255,strtochar(this->tableNumber),0,0,0,50,330);
        }
        //数字3
        if (x>670 && x<790 && y>90 && y<170){
            std::cout<<"3"<<std::endl;
            this->tableNumber = this->tableNumber+"3";
            m.show(40,260,60,255,255,255,strtochar(this->tableNumber),0,0,0,50,330);
        }
        //数字4
        if (x>410 && x<510 && y>200 && y<280){
            std::cout<<"4"<<std::endl;
            this->tableNumber = this->tableNumber+"4";
            m.show(40,260,60,255,255,255,strtochar(this->tableNumber),0,0,0,50,330);
        }
        //数字5
        if (x>540 && x<640 && y>200 && y<280){
            std::cout<<"5"<<std::endl;
            this->tableNumber = this->tableNumber+"5";
            m.show(40,260,60,255,255,255,strtochar(this->tableNumber),0,0,0,50,330);
        }
        //数字6
        if (x>670 && x<790 && y>200 && y<280){
            std::cout<<"6"<<std::endl;
            this->tableNumber = this->tableNumber+"6";
            m.show(40,260,60,255,255,255,strtochar(this->tableNumber),0,0,0,50,330);
        }
        //数字7
        if (x>410 && x<510 && y>290 && y<350){
            std::cout<<"7"<<std::endl;
            this->tableNumber = this->tableNumber+"7";
            m.show(40,260,60,255,255,255,strtochar(this->tableNumber),0,0,0,50,330);
        }
        //数字8
        if (x>540 && x<640 && y>290 && y<350){
            std::cout<<"8"<<std::endl;
            this->tableNumber = this->tableNumber+"8";
            m.show(40,260,60,255,255,255,strtochar(this->tableNumber),0,0,0,50,330);
        }
        //数字9
        if (x>670 && x<790 && y>290 && y<350){
            std::cout<<"9"<<std::endl;
            this->tableNumber = this->tableNumber+"9";
            m.show(40,260,60,255,255,255,strtochar(this->tableNumber),0,0,0,50,330);
        }
        //数字0
        if (x>540 && x<640 && y>370 && y<430){
            std::cout<<"0"<<std::endl;
            this->tableNumber = this->tableNumber+"0";
            m.show(40,260,60,255,255,255,strtochar(this->tableNumber),0,0,0,50,330);
        }
        /*取消*/
        if(x>670 && x<790 && y>370 && y<430){
            std::cout<<"cancel"<<std::endl;
            this->tableNumber = "";
            m.show(40,260,60,255,255,255,strtochar(this->tableNumber),0,0,0,50,330);
        }
        
        //如果点击的是确定,那么退出这个死循环
        if(x>410 & x<510 && y>380 && y<450){
            if(this->tableNumber != ""){
                break;
            }
            std::cout<<"please choose the table number!!"<<std::endl;
        }  
    }
}


/**/
void LoginPassWord(){

}