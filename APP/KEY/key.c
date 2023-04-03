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
    .vKEY_function = &vKEY_function,
    .vKEY_menu_display = &vKEY_menu_display
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
uint8_t key1_short_menu_task_state = 0;
uint8_t key1_long_enter_flag = 0;  //按键1长按确认键(进入当前选择的任务)
uint8_t key2_long_quit_flag = 0;  //按键2长按退出键(退出当前正在执行的任务回到菜单页)
uint8_t Menu_display_flag = 1;  //菜单显示(上电默认显示)
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
            case 1: //按键1短按当做菜单加(任务1,2...递增，上电默认0)
                {
                    if(Menu_display_flag)   //按键只在菜单页面生效
                    {
                        Key_Data.Key1_Down_Flag = 1;
                        key1_short_menu_task_state+=1;    //任务++
                        if(key1_short_menu_task_state >= 20)
                        {
                            key1_short_menu_task_state = 20;
                        }
                    }
                    break;
                }
            case 2:  //按键2短按当做菜单减(任务1,2...递减，上电默认0)
                {
                    if(Menu_display_flag)   //按键只在菜单页面生效
                    {
                        Key_Data.Key2_Down_Flag = 1;
                        key1_short_menu_task_state-=1;    //任务--
                        if(key1_short_menu_task_state <= 1)
                        {
                            key1_short_menu_task_state = 1;
                        }
                    }
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
            case 1: //进入任务
                {
                    if(Menu_display_flag && (key1_short_menu_task_state!= 0))   //按键只在菜单页面生效且任务不为0
                    {
                        Key_Data.Key1_Down_Long_Flag = 1;
                        Menu_display_flag = 0;  //关闭菜单
                        key1_long_enter_flag = 1;   //长按标志位
                    }
                    break;
                }
            case 2: //退出任务
                {
                    if(!Menu_display_flag)   //按键只在非菜单页面生效
                    {
                        Key_Data.Key2_Down_Long_Flag = 1;
                        TaskData.Now_task_state = 0;    //任务结束
                        key2_long_quit_flag = 1;
                    }
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
            default:
                break;
        }
    }

}

extern uint8_t threshold;

uint8_t i = 0;

//按键功能执行
void vKEY_function(void)
{
    static uint8_t key_num = 0;

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
        if(key1_long_enter_flag)
        {
            key1_long_enter_flag = 0;
            GuiClearScreen(CBLACK);  //清屏
            fb_cons_clear();    //清屏
            TaskData.Now_task_state = key1_short_menu_task_state;   //当前任务为选择的任务
        }
    }
    if(Key_Data.Key2_Down_Long_Flag)
    {
        Key_Data.Key2_Down_Long_Flag = 0;
        if(key2_long_quit_flag)
        {
            key2_long_quit_flag = 0;
            GuiClearScreen(CBLACK);  //清屏
            fb_cons_clear();    //清屏
            Menu_display_flag = 1;  //显示菜单
        }
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

/*
功能：主菜单
*/

void vKEY_menu_display(void)
{
    char display_menu_arr[50] = {0};
    if(Menu_display_flag)
    {
        GuiRowText(0,0+10,480,FONT_LEFT,"短按：K1任务+   K2任务-");
        GuiRowText(0,0+50,480,FONT_LEFT,"长按：K1进入任务 K2退出任务");
        GuiRowText(0,0+200,480,FONT_LEFT,"==============================");
        GuiRowText(0+170,0+240,400,FONT_LEFT,"任务★菜单");
        snprintf(display_menu_arr,sizeof(display_menu_arr),"∴选择任务：%d ",key1_short_menu_task_state);
        GuiRowText(0+100,0+280,480,FONT_LEFT,display_menu_arr);
    }
}

