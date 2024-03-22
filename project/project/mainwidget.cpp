#include "mainwidget.h"
#include "foodwidget.h"
#include "singledish.h"
#include <cstring>
#include "application.h"
extern "C"{
    #include "mfont.h"
}



MainWidget::MainWidget(const char *bmpName,string tableNum):
    Widget(bmpName),
    m_oneWidget("./res/one"),
    m_twoWidget("./res/two"),
    m_threeWidget("./res/three"),
    m_fourWidget("./res/four"),
    m_fiveWidget("./res/five")
{
    /*从登录界面传来桌号*/
    this->tableNum = tableNum;
}

void MainWidget::exec(int sock_fd)
{
    Bmp bmp(m_bmpName,m_lcd_p);
    bmp.show();

    //默认显示 店长推荐
    m_curBar = Bar_One;
    m_oneWidget.show();
    this->order_index = 0;
    // std::list<SingleDish>::iterator it;
    while (1) {
        int x,y;
        Touch touch;
        touch.wait(x,y);

        if(x>0 && x<240 && y>0 && y<480)//购物车 栏
        {
            /*呼叫服务员*/
            if(x>0 && x<200 &&y>0 && y< 50){
                string data = "桌号["+tableNum+"]:正在呼叫服务，请尽快处理...";
                /*发送消息给服务器*/
                std::cout<<data<<std::endl;
                write(sock_fd, strtochar(data), strlen(strtochar(data)));
            }

            /*翻页<操作*/
            if(x>15 && x<50 && y>390 && y<430){
                if(this->order_index>0){
                    this->order_index--;
                }
                MFont m(Lcd::instance()->addr());
                m.show(25,10,25,255,255,255,strtochar(to_string(order_index)),0,0,0,110,390);
                showCar();
            }

            /*翻页>操作*/
            if(x>170 && x<200 && y>390 && y<430){
                cout<<"orderInfoList.size()/5="<<orderDataList.size()/5<<endl;
                cout<<"orderInfoList.size()="<<orderDataList.size()<<endl;
                if(this->order_index < (orderDataList.size()/5)){
                    this->order_index++;
                    cout<<"order_index="<<order_index<<endl;
                }
                MFont m(Lcd::instance()->addr());
                m.show(25,10,25,255,255,255,strtochar(to_string(order_index)),0,0,0,110,390);
                showCar();
            }

            /*购物车减法*/
            if(x>160&&x<200&&y>50&&y<430){
                materialChangeCar(x,y);
                switch (m_curBar) {
                case Bar_One:
                    m_oneWidget.show();
                    break;
                case Bar_Two:
                    m_twoWidget.show();
                    break;
                case Bar_Three:
                    m_threeWidget.show();
                    break;
                case Bar_Four:
                    m_fourWidget.show();
                    break;
                case Bar_Five:
                    m_fiveWidget.show();
                    break;
                }
            }

            /*下单*/
            if(x>160&&x<220&&y>430&&y<480){
                if(orderDataList.size()==0){
                    cout<<"no order!!"<<endl;
                    continue;
                }
                //打印订单
                cout<<"orderInformation:"<<orderInformation<<endl;
                /*发送消息给服务器*/
                write(sock_fd, strtochar(orderInformation), strlen(strtochar(orderInformation)));

                string result = "下单成功";
                string comfirm = "确认";
                //打印提示
                MFont m(m_lcd_p);
                m.show(80,300,80,255,255,255,strtochar(result),0,0,0,250,200);
                m.show(50,100,50,255,255,255,strtochar(comfirm),0,0,0,690,400);

                while(1){
                    int x,y;
                    Touch touch;
                    touch.wait(x,y);
                    //如果点击的是确定,那么退出这个死循环
                    if(x>690 & x<790 && y>400 && y<450){
                        std::cout<<"客户已确认"<<std::endl;
                        close(sock_fd);
                        break;     
                    } 
                } 
                //返回主界面
                Application app;
                app.exec();
            }
        }
        else if(x>240 && x<800 && y>0 && y<480)// 右侧菜单 栏
        {
            // 上方的  功能按钮  -- 店长推荐 特色小炒  铁板煲  小吃   酒水
            if(x>270 && x<350 && y>0 && y<150) //店长推荐
            {
                std::cout<<"1111"<<std::endl;
                m_oneWidget.show();
                m_curBar = Bar_One;
            }
            else if(x>370 && x<470 && y>0 && y<150) //特色小炒
            {
                std::cout<<"2222"<<std::endl;
                m_twoWidget.show();
                m_curBar = Bar_Two;
            }
            else if(x>490 && x<590 && y>0 && y<150) // 铁板煲
            {
                std::cout<<"3333"<<std::endl;
                m_threeWidget.show();
                m_curBar = Bar_Three;
            }
            else if(x>620 && x<680 && y>0 && y<150) // 小吃
            {
                std::cout<<"4444"<<std::endl;
                m_fourWidget.show();
                m_curBar = Bar_Four;
            }
            else if(x>710 && x<760 && y>0 && y<150) // 酒水
            {
                std::cout<<"5555"<<std::endl;
                m_fiveWidget.show();
                m_curBar = Bar_Five;
            }

            //上一页
            if(x>240 && x<510 && y>440 && y<480)
            {
                std::cout<<"prev:"<<m_curBar<<std::endl;

                switch (m_curBar) {
                        case Bar_One:
                            m_oneWidget.prevIndex();
                            break;
                        case Bar_Two:
                            m_twoWidget.prevIndex();
                            break;
                        case Bar_Three:
                            m_threeWidget.prevIndex();
                            break;
                        case Bar_Four:
                            m_fourWidget.prevIndex();
                            break;
                        case Bar_Five:
                            m_fiveWidget.prevIndex();
                            break;
                }
            }
            //下一页
            if(x>520 && x<790 && y>440 && y<480)
            {
                std::cout<<"next:"<<m_curBar<<std::endl;

                switch (m_curBar) {
                        case Bar_One:
                            m_oneWidget.nextIndex();
                            break;
                        case Bar_Two:
                            m_twoWidget.nextIndex();
                            break;
                        case Bar_Three:
                            m_threeWidget.nextIndex();
                            break;
                        case Bar_Four:
                            m_fourWidget.nextIndex();
                            break;
                        case Bar_Five:
                            m_fiveWidget.nextIndex();
                            break;
                }
            }

            std::list<SingleDish>::iterator it;
            int index=0;
            int num1=0;
            int num2=0;
            int num3=0;
            int num4=0;
            int num5=0;
            switch (m_curBar) {
                case Bar_One:
                    /*获取foodlist的链表*/
                    it = m_oneWidget.getFoodList();
                    index = m_oneWidget.getFoodIndex();

                    num1 = materialChange(it,index,x,y,m_oneWidget.m_List.size());
                    if(num1 == 1){
                        /*更新订单信息*/
                        countOrder();
                        m_oneWidget.show();
                    }
                    
                    break;
                case Bar_Two:
                    it = m_twoWidget.getFoodList();
                    index = m_twoWidget.getFoodIndex();
                    num2 = materialChange(it,index,x,y,m_twoWidget.m_List.size());
                    if(num2 == 1){
                        /*更新订单信息*/
                        countOrder();
                        m_twoWidget.show();
                    }
                    break;
                case Bar_Three:
                    it = m_threeWidget.getFoodList();
                    index = m_threeWidget.getFoodIndex();
                    num3 = materialChange(it,index,x,y,m_threeWidget.m_List.size());
                    if(num3 == 1){
                        /*更新订单信息*/
                        countOrder();
                        m_threeWidget.show();
                    }
                    break;
                case Bar_Four:
                    it = m_fourWidget.getFoodList();
                    index = m_fourWidget.getFoodIndex();
                    num4 =materialChange(it,index,x,y,m_fourWidget.m_List.size());
                    if(num4==1){
                        /*更新订单信息*/
                        countOrder();
                        m_fourWidget.show();
                    }
                    break;
                case Bar_Five:
                    it = m_fiveWidget.getFoodList();
                    index = m_fiveWidget.getFoodIndex();
                    num5 = materialChange(it,index,x,y,m_fiveWidget.m_List.size());
                    if(num5==1){
                        /*更新订单信息*/
                        countOrder();
                        m_fiveWidget.show();
                    }
                    break;
            }
        }
    }
}


int MainWidget::materialChange(std::list<SingleDish>::iterator it,int index,int x,int y,int size){
    int num = 0;
    /*图一的+号操作*/
    if(x>380 && x<420 && y>200 && y<230){
        if((index*6+1)<=size){
            for(int i=0;i<index*6;i++){
                it++;
            }
            it->m_count++;
            num=1;
        }
    }

    /*图一的-号操作*/
    if(x>330 && x<370 && y>200 && y<230){
        if((index*6+1)<=size){
            for(int i=0;i<index*6;i++){
                it++;
            }
            if(it->m_count>0){
                it->m_count--;
            }
            num=1;
        }
        
    }

    /*图二的+号操作*/
    if(x>560 && x<590 && y>200 && y<230){
        cout<<"278-index="<<index*6+1<<",size = "<<size<<endl;
        if((index*6+2)<=size){
            for(int i=0;i<index*6+1;i++){
                it++;
            }
            it->m_count++;
            num=1;
        }
    }

    /*图二的-号操作*/
    if(x>520 && x<550 && y>200 && y<230){
        cout<<"278-index="<<index*6+1<<",size = "<<size<<endl;
        if((index*6+2)<=size){
            for(int i=0;i<index*6+1;i++){
                it++;
            }
            if(it->m_count>0){
                it->m_count--;
            }
            num=1;
        }
    }

    /*图三的+号操作*/
    if(x>760 && x<790 && y>200 && y<230){
        if((index*6+3)<=size){
            for(int i=0;i<index*6+2;i++){
                it++;
            }
            it->m_count++;
            num=1;
        }
    }

    /*图三的-号操作*/
    if(x>720 && x<750 && y>200 && y<230){
        if((index*6+3)<=size){
            for(int i=0;i<index*6+2;i++){
                it++;
            }
            if(it->m_count>0){
                it->m_count--;
            }
            num=1;
        }
        
    }

    /*图四的+号操作*/
    if(x>380 && x<420 && y>360 && y<410){
        if((index*6+4)<=size){
            for(int i=0;i<index*6+3;i++){
                it++;
            }
            it->m_count++;
            num=1;
        }
    }

    /*图四的-号操作*/
    if(x>330 && x<370 && y>360 && y<410){
        if((index*6+4)<=size){
           for(int i=0;i<index*6+3;i++){
                it++;
            }
            if(it->m_count>0){
                it->m_count--;
            }
            num=1;
        }
    }
    
    /*图五的+号操作*/
    if(x>560 && x<590 && y>360 && y<410){
        if((index*6+5)<=size){
            for(int i=0;i<index*6+4;i++){
                it++;
            }
            it->m_count++;
            num=1;
        }
    }

    /*图五的-号操作*/
    if(x>500 && x<550 && y>360 && y<410){
        if((index*6+5)<=size){
            for(int i=0;i<index*6+4;i++){
                it++;
            }
            if(it->m_count>0){
                it->m_count--;
            }
            num=1;
        }
    }

    /*图六的+号操作*/
    if(x>760 && x<790 && y>360 && y<410){
        if((index*6+6)<=size){
            for(int i=0;i<index*6+5;i++){
                it++;
            }
            it->m_count++;
            num=1;
        }
    }

    /*图六的-号操作*/
    if(x>700 && x<750 && y>360 && y<410){
        if((index*6+6)<=size){
            for(int i=0;i<index*6+5;i++){
                it++;
            }
            if(it->m_count>0){
                it->m_count--;
            }
            num=1;
        }
    }
    return num;
}


void MainWidget::materialChangeCar(int x,int y){
    std::list<string>::iterator it = orderDataList.begin();
    /*购物车减法*/
    if(x>160&&x<195){  
        /*第一个框*/
        if(y>75&&y<120){
            cout<<"1111111111111111111111"<<endl;
            if(orderDataList.size()>0){
                for(int i=0;i<order_index*5;i++){
                    it++;
                }
                findOrderByName(*it);
                countOrder();
            }
        }

        /*第二个框*/
        if(y>135&&y<180){
            cout<<"222222222222222222222"<<endl;
            if(orderDataList.size()>1){
               for(int i=0;i<order_index*5+1;i++){
                    it++;
                }
                findOrderByName(*it);
                countOrder(); 
            }
        }

        /*第三个框*/
        if(y>195&&y<240){
            cout<<"33333333333333333333"<<endl;
            if(orderDataList.size()>2){
                for(int i=0;i<order_index*5+2;i++){
                    it++;
                }
                findOrderByName(*it);
                countOrder();
            }   
        }

        /*第四个框*/
        if(y>255&&y<310){
            cout<<"444444444444444444444"<<endl;
            if(orderDataList.size()>3){
                for(int i=0;i<order_index*5+3;i++){
                    it++;
                }
                findOrderByName(*it);
                countOrder();
            }
        }

        /*第五个框*/
        if(y>320&&y<360){
            cout<<"555555555555555555555"<<endl;
            if(orderDataList.size()>4){
                for(int i=0;i<order_index*5+4;i++){
                    it++;
                }
                findOrderByName(*it);
                countOrder();
            }
        }
    }
}


void MainWidget::countOrder(){
    std::list<string>::iterator it ;
    std::list<SingleDish>::iterator it1 ;
    std::list<SingleDish>::iterator it2 ;
    std::list<SingleDish>::iterator it3 ;
    std::list<SingleDish>::iterator it4 ;
    std::list<SingleDish>::iterator it5 ;

    Bmp bmp("./res/whiteboard.bmp");
    bmp.show(15,60);

    orderDataList.clear();
    order_money = 0;
    int count_order_num = 0;

    /*初始化订单详情*/
    orderInformation ="\n["+tableNum+"]\n";

    for(it1 = m_oneWidget.m_List.begin();it1!=m_oneWidget.m_List.end();it1++){
        if(it1->m_count>0){
            string order = it1->m_name+string("*")+to_string(it1->m_count)+string("=")+to_string(stoi(it1->m_price)*it1->m_count);
            order_money += stoi(it1->m_price)*it1->m_count;
            count_order_num++;
            orderDataList.push_back(order);
            orderInformation = orderInformation+"---"+order+"\n";
        }
    }

    for(it2 = m_twoWidget.m_List.begin();it2!=m_twoWidget.m_List.end();it2++){
        if(it2->m_count>0){
            string order = it2->m_name+string("*")+to_string(it2->m_count)+string("=")+to_string(stoi(it2->m_price)*it2->m_count);
            order_money += stoi(it2->m_price)*it2->m_count;
            count_order_num++;
            orderDataList.push_back(order);
            orderInformation = orderInformation+"---"+order+"\n";
        }
    }

    for(it3 = m_threeWidget.m_List.begin();it3!=m_threeWidget.m_List.end();it3++){
        if(it3->m_count>0){
            string order = it3->m_name+string("*")+to_string(it3->m_count)+string("=")+to_string(stoi(it3->m_price)*it3->m_count);
            order_money += stoi(it3->m_price)*it3->m_count;
            count_order_num++;
            orderDataList.push_back(order);
            orderInformation = orderInformation+"---"+order+"\n";
        }
    }

    for(it4 = m_fourWidget.m_List.begin();it4!=m_fourWidget.m_List.end();it4++){
        if(it4->m_count>0){
            string order = it4->m_name+string("*")+to_string(it4->m_count)+string("=")+to_string(stoi(it4->m_price)*it4->m_count);
            order_money += stoi(it4->m_price)*it4->m_count;
            count_order_num++;
            orderDataList.push_back(order);
            orderInformation = orderInformation+"---"+order+"\n";
        }
    }

    for(it5 = m_fiveWidget.m_List.begin();it5!=m_fiveWidget.m_List.end();it5++){
        if(it5->m_count>0){
            string order = it5->m_name+string("*")+to_string(it5->m_count)+string("=")+to_string(stoi(it5->m_price)*it5->m_count);
            order_money += stoi(it5->m_price)*it5->m_count;
            count_order_num++;
            orderDataList.push_back(order);
            orderInformation = orderInformation+"---"+order+"\n";
        }
    }
    //生成订单
    orderInformation = orderInformation + "total:"+ to_string(order_money);
    showCar();
}


//购物车数据展示
void MainWidget::showCar()
{
    Bmp bmp("./res/whiteboard.bmp");
    bmp.show(15,60);

    MFont m(Lcd::instance()->addr());
    m.show(25,50,25,95,70,70,strtochar(to_string(order_money)),255,255,255,70,443);

    //菜图片的Y位置
    int i;
    std::list<string>::iterator it;
    for(it=orderDataList.begin(),i=0; it!=orderDataList.end(); it++,i++)
    {
        if(order_index*5 == i) 
        {
            //位置1 --盒子图
            Bmp bmp1("./res/leftpriceframe.bmp");
            bmp1.show(15,60);
            //菜名
            MFont m(Lcd::instance()->addr());
            m.show(20,150,25,255,255,255,strtochar(*it),0,0,0,20,77);

            it++;
            if(it!=orderDataList.end()){
                //位置2 --盒子图
                Bmp bmp2("./res/leftpriceframe.bmp");
                bmp2.show(15,60+64);
                m.show(20,150,25,255,255,255,strtochar(*it),0,0,0,20,77+64);
            }else{
                break;
            }

            it++;
            if(it!=orderDataList.end()){
                //位置3 --盒子图
                Bmp bmp3("./res/leftpriceframe.bmp");
                bmp3.show(15,60+64*2);
                m.show(20,150,25,255,255,255,strtochar(*it),0,0,0,20,77+64*2);
            }else{
                break;
            }

            it++;
            if(it!=orderDataList.end()){
                //位置4 --盒子图
                Bmp bmp4("./res/leftpriceframe.bmp");
                bmp4.show(15,60+64*3);
                m.show(20,150,25,255,255,255,strtochar(*it),0,0,0,20,77+64*3);
            }else{
                break;
            }

            it++;
            if(it!=orderDataList.end()){
                //位置5 --盒子图
                Bmp bmp4("./res/leftpriceframe.bmp");
                bmp4.show(15,60+64*4);
                m.show(20,150,25,255,255,255,strtochar(*it),0,0,0,20,77+64*4);
            }else{
                break;
            }
            break;
        }
    }
}


void MainWidget::findOrderByName(std::string order){
    /*获取该字字符串"*"前的内容"*/
    int np5 = order.find_first_of('*');
    string orderName = order.substr(0, np5);
    cout << "orderName:" << orderName << endl;

    std::list<SingleDish>::iterator it1 ;
    std::list<SingleDish>::iterator it2 ;
    std::list<SingleDish>::iterator it3 ;
    std::list<SingleDish>::iterator it4 ;
    std::list<SingleDish>::iterator it5 ;

    for(it1 = m_oneWidget.m_List.begin();it1!=m_oneWidget.m_List.end();it1++){
        cout<<"it1->m_count = "<<it1->m_count<<endl;
        if(it1->m_name == orderName){
            if(it1->m_count>0){
                it1->m_count--;
            }
            cout<<"it1->m_count = "<<it1->m_count<<endl;
            break;
        }
    }

    for(it2 = m_twoWidget.m_List.begin();it2!=m_twoWidget.m_List.end();it2++){
        cout<<"it2->m_count = "<<it2->m_count<<endl;
        if(it2->m_name == orderName){
            if(it2->m_count>0){
                it2->m_count--;
            }
            cout<<"it2->m_count = "<<it2->m_count<<endl;
            break;
        }
    }

    for(it3 = m_threeWidget.m_List.begin();it3!=m_threeWidget.m_List.end();it3++){
        cout<<"it3->m_count = "<<it3->m_count<<endl;
        if(it3->m_name == orderName){
            if(it3->m_count>0){
                it3->m_count--;
            }
            cout<<"it3->m_count = "<<it3->m_count<<endl;
            break;
        }
    }

    for(it4 = m_fourWidget.m_List.begin();it4!=m_fourWidget.m_List.end();it4++){
        cout<<"it4->m_count = "<<it4->m_count<<endl;
        if(it4->m_name == orderName){
            if(it4->m_count>0){
                it4->m_count--;
            }
            cout<<"it4->m_count = "<<it4->m_count<<endl;
            break;
        }
    }

    for(it5 = m_fiveWidget.m_List.begin();it5!=m_fiveWidget.m_List.end();it5++){
        cout<<"it5->m_count = "<<it5->m_count<<endl;
        if(it5->m_name == orderName){
            if(it5->m_count>0){
                it5->m_count--;
            }
            cout<<"it5->m_count = "<<it5->m_count<<endl;
            break;
        }
    }
}