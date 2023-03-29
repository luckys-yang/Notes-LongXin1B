/*
 * led.c
 *
 * created: 2023-03-23
 *  author: Yang
 *  module: LED
 */
#include "led.h"

//��ʼ���ṹ��
LED_TypeDef Led_Data =
{
    .Red_Led = LED1,
    .Green_Led =LED2,
    .Blue_Led = LED3,
    .vLED_init = &vLED_init,
    .vLED_control = &vLED_control
};

//LED��ʼ��
void vLED_init(void)
{
    //����GPIOΪ���״̬
    gpio_enable(Led_Data.Blue_Led,DIR_OUT);
    gpio_enable(Led_Data.Green_Led,DIR_OUT);
    gpio_enable(Led_Data.Red_Led,DIR_OUT);
    //�ر�LED
    gpio_write(Led_Data.Blue_Led,RESET);
    gpio_write(Led_Data.Green_Led,RESET);
    gpio_write(Led_Data.Red_Led,RESET);
}

//����/Ϩ���
//����1���Ƶ���ɫ--�죬�̣���(��ɫ��3����ɫ��һ��)
//����2��SET--���� RESET--Ϩ��
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
