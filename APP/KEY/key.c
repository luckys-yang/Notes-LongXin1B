/*
 * key.c
 *
 * created: 2023-03-23
 *  author: Yang
 *  module: 按键
 */

#include "key.h"

static uint8_t Key_Up,Key_Down,Key_Value;
uint32_t Key_longtime = 0;

//初始化结构体
KEY_TypeDef Key_Data =
{
    .Key1_Down_Long_Flag = 0,
    .Key2_Down_Long_Flag = 0,
    .Key3_Down_Long_Flag = 0,
    .Key4_Down_Long_Flag = 0,
    .Key1_Down_Flag = 0,
    .Key2_Down_Flag = 0,
    .Key3_Down_Flag = 0,
    .Key4_Down_Flag = 0,
    .vKEY_init = &vKEY_init,
    .ucKEY_sub = &ucKEY_sub,
    .vKEY_detection = &vKEY_detection,
    .vKEY_function = &vKEY_function
};

//按键初始化
void vKEY_init(void)
{
    gpio_enable(S1,DIR_IN);
    gpio_enable(S2,DIR_IN);
    gpio_enable(S3,DIR_IN);
    gpio_enable(S4,DIR_IN);
}

//按键检测子程序
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


extern bool Led_run_Flag;   //LED呼吸灯运行标志位

//按键检测
void vKEY_detection(void)
{
    static uint8_t Key_Old;

    Key_Value = Key_Data.ucKEY_sub();
    Key_Up = ~Key_Value & (Key_Old^Key_Value);
    Key_Down = Key_Value & (Key_Old^Key_Value);
    Key_Old = Key_Value;

    if(Key_Down)
    {
        Key_longtime = 0;
    }

    if(Key_longtime < 10)
    {
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
                    //Led_run_Flag = !Led_run_Flag;
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
    else    //长按
    {
        switch(Key_Value)
        {
            case 1:
                {
                    Key_Data.Key1_Down_Long_Flag = 1;
                    break;
                }
            case 2:
                {
                    Key_Data.Key2_Down_Long_Flag = 1;
                    break;
                }
            case 3:
                {
                    Key_Data.Key3_Down_Long_Flag = 1;
                    break;
                }
            case 4:
                {
                    Key_Data.Key4_Down_Long_Flag = 1;
                    break;
                }
                default:break;
        }
    }

}

extern uint8_t threshold;

uint8_t i = 0;

//按键功能执行
void vKEY_function(void)
{
    /*短按*/
    if(Key_Data.Key1_Down_Flag)
    {
        Key_Data.Key1_Down_Flag = 0;
    }
    if(Key_Data.Key2_Down_Flag)
    {
        Key_Data.Key2_Down_Flag = 0;
    }
    if(Key_Data.Key3_Down_Flag)
    {
        Key_Data.Key3_Down_Flag = 0;
    }
    if(Key_Data.Key4_Down_Flag)
    {
        Key_Data.Key4_Down_Flag = 0;
    }
    /*长按*/
    if(Key_Data.Key1_Down_Long_Flag)
    {
        Key_Data.Key1_Down_Long_Flag = 0;
    }
    if(Key_Data.Key2_Down_Long_Flag)
    {
        Key_Data.Key2_Down_Long_Flag = 0;
    }
    if(Key_Data.Key3_Down_Long_Flag)
    {
        Key_Data.Key3_Down_Long_Flag = 0;
    }
    if(Key_Data.Key4_Down_Long_Flag)
    {
        Key_Data.Key4_Down_Long_Flag = 0;
    }
}


