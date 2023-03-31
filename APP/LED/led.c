/*
 * led.c
 *
 * created: 2023-03-23
 *  author: Yang
 *  module: LED
 */
#include "led.h"

//初始化结构体
LED_TypeDef Led_Data =
{
    .Red_Led = LED1,
    .Green_Led =LED2,
    .Blue_Led = LED3,
    .vLED_init = &vLED_init,
    .vLED_control = &vLED_control,
    .vLED_breathing_light = &vLED_breathing_light
};

//LED初始化
void vLED_init(void)
{
    //设置GPIO为输出状态
    gpio_enable(Led_Data.Blue_Led,DIR_OUT);
    gpio_enable(Led_Data.Green_Led,DIR_OUT);
    gpio_enable(Led_Data.Red_Led,DIR_OUT);
    //关闭LED
    gpio_write(Led_Data.Blue_Led,RESET);
    gpio_write(Led_Data.Green_Led,RESET);
    gpio_write(Led_Data.Red_Led,RESET);
}

//点亮/熄灭灯
//参数1：灯的颜色--红，绿，蓝(白色则3个颜色混一起)
//参数2：SET--点亮 RESET--熄灭
void vLED_control(uint8_t led_color,uint8_t swch)
{
    if(SET == swch)
    {
        gpio_write(led_color,SET);
    }
    else
    {
        gpio_write(led_color,RESET);
    }
}

bool Led_run_Flag = 0;  //LED呼吸灯运行标志位

/*
功能：呼吸灯
参数：哪个颜色的灯
*/
void vLED_breathing_light(uint8_t color_led)
{
    static uint8_t MENU = 0,flag = 1;
    static uint16_t t = 1,i = 0;
    while(Led_run_Flag)
    {
        for(i=0; i<10; i++)
        {
            Led_Data.vLED_control(color_led,SET);
            delay_us(t);
            Led_Data.vLED_control(color_led,RESET);
            delay_us(601-t);
        }
        if(flag==1)
        {
            t++;
            if(t==600)
                flag=0;
        }
        else if(flag==0)
        {
            t--;
            if(t==1)
                flag=1;
        }
    }
}


