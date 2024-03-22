#include "touch.h"


Touch::Touch(BOARDTYPE type ,const char*deviceName )
{
    strcpy(m_deviceName,deviceName);
    m_type = type;
}

void Touch::wait(int &rx, int &ry)
{
    int tsfd = open(m_deviceName,O_RDWR);
    if(tsfd == -1)
    {
        printf("open /dev/input/event0 error\n");
        return ;
    }

    while(1)
    {
        struct input_event info;

        //3）读取触摸屏数据
        read(tsfd,&info,sizeof(struct input_event));


        //判断当前发生的是触摸屏事件,接着判断触发的是X轴事件
        if(info.type == EV_ABS && info.code == ABS_X)
        {
            rx = info.value;
            m_x = info.value;
        }
        //判断当前发生的是触摸屏事件,接着判断触发的是Y轴事件
        if(info.type == EV_ABS && info.code == ABS_Y)
        {
            ry = info.value;
            m_y = info.value;
        }

        //松开的时候，才进行打印  type:1 code:330 value:0
        if(info.type == EV_KEY && info.code == BTN_TOUCH &&  info.value == 0)
        {

            //如果你的板子是黑色的，那么需要进行坐标转换(1024,600) ---(800,480)
            if(m_type == BOARD_TYPE_GEC6818_BLACK)
            {
                rx = (rx *1.0)/1024 * 800 ;
                ry = (ry *1.0)/600  * 480 ;

                m_x = rx;
                m_y = ry;
            }

            std::cout<<"x:"<<rx<<" y:"<<ry<<std::endl;

            break;
        }
    }

    //5）关闭触摸屏文件
    close(tsfd);
}
