/*
 * ultrasound.c
 *
 * created: 2023-03-28
 *  author: Yang
 *  module: 超声波(使用CX20106芯片进行测距)  硬件连接---P1插UART1
 */
#include "ultrasound.h"


extern pwm_cfg_t pwm2_cfg;

//初始化结构体
ULTRASOUND_TypeDef Ultrasound_Data =
{
    .Ultrasound_last_distance = 0,
    .Ultrasound_Over_Flag = 0,
    .Ultrasound_distance = 0.0,
    .vULTRASOUND_init = &vULTRASOUND_init,
    .vULTRASOUND_get_distance_function = &vULTRASOUND_get_distance_function
};



/*
功能：初始化
*/
void vULTRASOUND_init(void)
{
    gpio_enable(CX_TRIG,DIR_OUT);   //输出模式
    gpio_enable(CX_ECHO,DIR_IN);   //输入模式
    ls1x_install_gpio_isr(CX_ECHO,INT_TRIG_EDGE_DOWN,vULTRASOUND_IRQhandler,NULL);    //下降沿触发 gpio 中断
    ls1x_enable_gpio_interrupt(CX_ECHO);   //使能中断
    gpio_write(CX_TRIG,RESET);  //发送引脚默认设置为低电平
}

/*
功能：中断服务函数
*/
void vULTRASOUND_IRQhandler(int IRQn,void *param)
{
    My_pwm_Data.PWM2_Start_Flag = 0;    //关闭定时器计数
    Ultrasound_Data.Ultrasound_distance = My_pwm_Data.PWM2_Time_count*1.7/10/1.2;//（1.2为定时器补偿）/1.2
    My_pwm_Data.PWM2_Time_count = 0;    //定时器计数清0
}

/*
功能：超声波测距函数
不能在这直接LCD显示否则导致屏幕卡死
*/
float vULTRASOUND_get_distance_function(void)
{
    uint8_t i=0;
    char arr[50] = {0};
    //if(Ultrasound_Data.Ultrasound_Over_Flag)
    //{
        for(i=0; i<4; i++)
        {
            gpio_write(CX_TRIG,SET);
            delay_us(12);
            gpio_write(CX_TRIG,RESET);
            delay_us(12);
        }
      //  ls1x_pwm_timer_start(devPWM2,(void *)&pwm2_cfg);    //打开定时器(会卡死)
        My_pwm_Data.PWM2_Start_Flag = 1;    //开启PWM2定时器计数
        delay_ms(100);

        if(Ultrasound_Data.Ultrasound_distance >= 2000)
        {
            Ultrasound_Data.Ultrasound_distance = 2000;
        }
        if(Ultrasound_Data.Ultrasound_distance <= 0)
        {
            Ultrasound_Data.Ultrasound_distance = Ultrasound_Data.Ultrasound_last_distance;
        }
        snprintf(arr,sizeof(arr), "距离:%.1fcm   ", Ultrasound_Data.Ultrasound_distance);
        GuiRowText(0,0+400,400, FONT_LEFT,(uint8_t*)arr);
        Ultrasound_Data.Ultrasound_last_distance = Ultrasound_Data.Ultrasound_distance;
        Ultrasound_Data.Ultrasound_Over_Flag = 0;
        return Ultrasound_Data.Ultrasound_distance;
    //}
    return 0;
}



