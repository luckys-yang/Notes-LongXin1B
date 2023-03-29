/*
 * key.c
 *
 * created: 2023-03-23
 *  author: Yang
 *  module: ����
 */
 
#include "key.h"

static uint8_t Key_Up,Key_Down,Key_Value;


//��ʼ���ṹ��
KEY_TypeDef Key_Data =
{
    .Key1_Down_Flag = 0,
    .Key2_Down_Flag = 0,
    .Key3_Down_Flag = 0,
    .Key4_Down_Flag = 0,
    .vKEY_init = &vKEY_init,
    .ucKEY_sub = &ucKEY_sub,
    .vKEY_detection = &vKEY_detection,
    .vKEY_function = &vKEY_function
};

//������ʼ��
void vKEY_init(void)
{
    gpio_enable(S1,DIR_IN);
    gpio_enable(S2,DIR_IN);
    gpio_enable(S3,DIR_IN);
    gpio_enable(S4,DIR_IN);
}

//��������ӳ���
uint8_t ucKEY_sub(void)
{
    if((!KEY1) || (!KEY2) || (!KEY3) || (!KEY4))
    {
        if(!KEY1)
        {
            return 1;
        }
        if(!KEY2)
        {
            return 2;
        }
        if(!KEY3)
        {
            return 3;
        }
        if(!KEY4)
        {
            return 4;
        }
    }
    return 0;
}

//�������
void vKEY_detection(void)
{
    static uint8_t Key_Old;
    
    Key_Value = Key_Data.ucKEY_sub();
    Key_Up = ~Key_Value & (Key_Old^Key_Value);
    Key_Down = Key_Value & (Key_Old^Key_Value);
    Key_Old = Key_Value;
    
    switch(Key_Up)
    {
        case 1:
            {
                Key_Data.Key1_Down_Flag = 1;
                break;
            }
        case 2:
            {
                Key_Data.Key2_Down_Flag = 1;
                break;
            }
        case 3:
            {
                Key_Data.Key3_Down_Flag = 1;
                break;
            }
        case 4:
            {
                Key_Data.Key4_Down_Flag = 1;
                break;
            }
            default:
                break;
    }
}

extern uint8_t threshold;

uint8_t i = 0;

//��������ִ��
void vKEY_function(void)
{
    if(Key_Data.Key1_Down_Flag)
    {
        Key_Data.Key1_Down_Flag = 0;
        set_lcd_brightness(100);
    }
    if(Key_Data.Key2_Down_Flag)
    {
        Key_Data.Key2_Down_Flag = 0;
        i++;
        vMOTOR_set_speed(i);
        printk("ddd--%d\r\n",i);
    }
    if(Key_Data.Key3_Down_Flag)
    {
        Key_Data.Key3_Down_Flag = 0;
    }
    if(Key_Data.Key4_Down_Flag)
    {
        Key_Data.Key4_Down_Flag = 0;
        vMOTOR_set_speed(0);
    }
}


