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
    .vLED_control = &vLED_control,
    .vLED_breathing_light = &vLED_breathing_light
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

bool Led_run_Flag = 0;  //LED���������б�־λ

/*
���ܣ�������
�������ĸ���ɫ�ĵ�
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


