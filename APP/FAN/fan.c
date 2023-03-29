/*
 * fan.c
 *
 * created: 2023-03-26
 *  author: Yang
 *  module: 风扇 硬件连接：插板子左侧FAN
 */
#include "fan.h"

//初始化结构体
FAN_TypeDef Fan_Data =
{
    .vFAN_init = &vFAN_init,
    .vFAN_control = &vFAN_control,
    .vFAN_set_speed = &vFAN_set_speed
};


/*
功能：初始化
*/
void vFAN_init(void)
{
    gpio_enable(FAN_PIN,DIR_OUT);//输出
    Fan_Data.vFAN_control(RESET);//默认关闭
    Fan_Data.vFAN_set_speed(0); //速度0
}

/*
功能：控制风扇
参数:SET--开 RESET--关
*/
void vFAN_control(uint8_t swch)
{
    if(SET == swch)
    {
        gpio_write(FAN_PIN,SET);
    }
    else
    {
        gpio_write(FAN_PIN,RESET);
    }
}

/*
功能：风扇转速控制
参数：速度(0~100)
*/
void vFAN_set_speed(uint8_t speed)
{
    set_lcd_brightness(speed);
}


