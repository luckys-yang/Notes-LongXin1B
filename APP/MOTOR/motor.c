/*
 * motor.c
 *
 * created: 2023-03-27
 *  author: Yang
 *  module: 直流电机  硬件连接：P2插板子右上角P5  P5插板子右上角P2(由于驱动电机的PWM为GP7101的反向输出，所以PWM脉宽越高，电机速度越慢)
 */

#include "motor.h"


//结构体初始化
MOTOR_TypeDef Motor_Data =
{
    .Now_RPM = 0.0,
    .Motor_IRQ_count = 0,
    .vMOTOR_init = &vMOTOR_init,
    .vMOTOR_control = &vMOTOR_control,
    .vMOTOR_set_speed = &vMOTOR_set_speed,
    .vMOTOR_calculate_minute_speed = &vMOTOR_calculate_minute_speed
};

/*
功能：初始化
*/
void vMOTOR_init(void)
{
    ls1x_install_gpio_isr(MOTOR_PIN, INT_TRIG_EDGE_DOWN, vMOTOR_IRQhandler,NULL);  // 下降沿触发
    ls1x_enable_gpio_interrupt(MOTOR_PIN);  //使能中断
    set_lcd_brightness(100);  //默认关闭
}

/*
功能：控制直流电机开关
参数：SET--开 RESET--关
*/
void vMOTOR_control(uint8_t swch)
{
    if(SET == swch)
    {
        set_lcd_brightness(0);
    }
    else
    {
        set_lcd_brightness(100);
    }
}

/*
功能：直流电机速度
参数：(0~50)值越大越慢
*/
void vMOTOR_set_speed(uint8_t speed)
{
    set_lcd_brightness(speed);
}

/*
功能：计算每分钟转速
*/
void vMOTOR_calculate_minute_speed(void)
{
    Motor_Data.Now_RPM = (float)(Motor_Data.Motor_IRQ_count*60) /(7*30); //减速比30  编码器一圈7个脉冲
}


/*
功能：中断服务函数
*/
void vMOTOR_IRQhandler(int IRQn,void *param)
{
    Motor_Data.Motor_IRQ_count++;   //编码器计数
    return;
}
