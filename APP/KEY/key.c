/*
 * key.c
 *
 * created: 2023-03-23
 *  author: Yang
 *  module: ����
 */

#include "key.h"

static uint8_t Key_Up,Key_Down,Key_Value;
uint32_t Key_longtime = 0;

//��ʼ���ṹ��
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


extern bool Led_run_Flag;   //LED���������б�־λ
uint8_t key1_short_menu_task_state = 0;
uint8_t key1_long_enter_flag = 0;  //����1����ȷ�ϼ�(���뵱ǰѡ�������)
uint8_t key2_long_quit_flag = 0;  //����2�����˳���(�˳���ǰ����ִ�е�����ص��˵�ҳ)
uint8_t Menu_display_flag = 1;  //�˵���ʾ(�ϵ�Ĭ����ʾ)
//�������
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
            case 1: //����1�̰������˵���(����1,2...�������ϵ�Ĭ��0)
                {
                    if(Menu_display_flag)   //����ֻ�ڲ˵�ҳ����Ч
                    {
                        Key_Data.Key1_Down_Flag = 1;
                        key1_short_menu_task_state+=1;    //����++
                        if(key1_short_menu_task_state >= 20)
                        {
                            key1_short_menu_task_state = 20;
                        }
                    }
                    break;
                }
            case 2:  //����2�̰������˵���(����1,2...�ݼ����ϵ�Ĭ��0)
                {
                    if(Menu_display_flag)   //����ֻ�ڲ˵�ҳ����Ч
                    {
                        Key_Data.Key2_Down_Flag = 1;
                        key1_short_menu_task_state-=1;    //����--
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
    else    //����
    {
        switch(Key_Value)
        {
            case 1: //��������
                {
                    if(Menu_display_flag && (key1_short_menu_task_state!= 0))   //����ֻ�ڲ˵�ҳ����Ч������Ϊ0
                    {
                        Key_Data.Key1_Down_Long_Flag = 1;
                        Menu_display_flag = 0;  //�رղ˵�
                        key1_long_enter_flag = 1;   //������־λ
                    }
                    break;
                }
            case 2: //�˳�����
                {
                    if(!Menu_display_flag)   //����ֻ�ڷǲ˵�ҳ����Ч
                    {
                        Key_Data.Key2_Down_Long_Flag = 1;
                        TaskData.Now_task_state = 0;    //�������
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

//��������ִ��
void vKEY_function(void)
{
    static uint8_t key_num = 0;

    /*�̰�*/
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
    /*����*/
    if(Key_Data.Key1_Down_Long_Flag)
    {
        Key_Data.Key1_Down_Long_Flag = 0;
        if(key1_long_enter_flag)
        {
            key1_long_enter_flag = 0;
            GuiClearScreen(CBLACK);  //����
            fb_cons_clear();    //����
            TaskData.Now_task_state = key1_short_menu_task_state;   //��ǰ����Ϊѡ�������
        }
    }
    if(Key_Data.Key2_Down_Long_Flag)
    {
        Key_Data.Key2_Down_Long_Flag = 0;
        if(key2_long_quit_flag)
        {
            key2_long_quit_flag = 0;
            GuiClearScreen(CBLACK);  //����
            fb_cons_clear();    //����
            Menu_display_flag = 1;  //��ʾ�˵�
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
���ܣ����˵�
*/

void vKEY_menu_display(void)
{
    char display_menu_arr[50] = {0};
    if(Menu_display_flag)
    {
        GuiRowText(0,0+10,480,FONT_LEFT,"�̰���K1����+   K2����-");
        GuiRowText(0,0+50,480,FONT_LEFT,"������K1�������� K2�˳�����");
        GuiRowText(0,0+200,480,FONT_LEFT,"==============================");
        GuiRowText(0+170,0+240,400,FONT_LEFT,"�����˵�");
        snprintf(display_menu_arr,sizeof(display_menu_arr),"��ѡ������%d ",key1_short_menu_task_state);
        GuiRowText(0+100,0+280,480,FONT_LEFT,display_menu_arr);
    }
}

