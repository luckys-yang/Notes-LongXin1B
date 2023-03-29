/*
 * buzzer.c
 *
 * created: 2023-03-24
 *  author: Yang
 *  module: 蜂鸣器
 */
 
#include "buzzer.h"

//结构体初始化
BUZZER_TypeDef Buzzer_Data =
{
    .vBUZZER_init = &vBUZZER_init,
    .vBUZZER_control = &vBUZZER_control
};


//蜂鸣器初始化
void vBUZZER_init(void)
{
    gpio_enable(BUZZER,DIR_OUT);    //输出
    gpio_write(BUZZER,RESET);   //关闭
}

//开启\关闭蜂鸣器
//参数：SET--开 RESET--关
void vBUZZER_control(uint8_t swch)
{
    if(SET == swch)
    {
        gpio_write(BUZZER,SET);
    }
    else
    {
        gpio_write(BUZZER,RESET);
    }
}


