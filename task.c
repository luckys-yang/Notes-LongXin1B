/*
 * task.c
 *
 * created: 2023-04-01
 *  author: ����
 */
#include "task.h"

TASK_TypeDef TaskData =
{
    .Now_task_state = 0,
    .vTASK_one = &vTASK_one,
    .vTASK_two = &vTASK_two,
    .vTASK_three = &vTASK_three,
    .vTASK_four = &vTASK_four,
    .vTASK_five = &vTASK_five,
    .vTASK_six = &vTASK_six,
    .vTASK_seven = &vTASK_seven,
    .vTASK_eight = &vTASK_eight,
    .vTASK_nine = &vTASK_nine,
    .vTASK_ten = &vTASK_ten,
    .vTASK_all = &vTASK_all
};


/*����1*/
void vTASK_one(void)
{
    if(1 == TaskData.Now_task_state)
    {
        static key1_temp_flag = 0;
        while(TaskData.Now_task_state != 0)
        {
            if(Key_Data.Key3_Down_Flag)
            {
                Key_Data.Key3_Down_Flag = 0;
                key1_temp_flag = !key1_temp_flag;
            }
            if(key1_temp_flag)  //�� �� ��ѭ��
            {
                Led_Data.vLED_control(Led_Data.Blue_Led,SET);
                delay_ms(700);
                Led_Data.vLED_control(Led_Data.Blue_Led,RESET);
                Led_Data.vLED_control(Led_Data.Red_Led,SET);
                delay_ms(700);
                Led_Data.vLED_control(Led_Data.Red_Led,RESET);
                Led_Data.vLED_control(Led_Data.Green_Led,SET);
                delay_ms(700);
                Led_Data.vLED_control(Led_Data.Green_Led,RESET);
            }

            if(Key_Data.Key4_Down_Flag) //������
            {
                Key_Data.Key4_Down_Flag = 0;
                Led_Data.vLED_control(Led_Data.Blue_Led,RESET);
                Led_Data.vLED_control(Led_Data.Green_Led,RESET);
                Led_Data.vLED_control(Led_Data.Red_Led,RESET);

                Led_Data.vLED_breathing_light(Led_Data.Red_Led);    //������
                Led_Data.vLED_control(Led_Data.Red_Led,SET);
                delay_ms(700);
                Led_Data.vLED_control(Led_Data.Red_Led,RESET);
                delay_ms(700);
                Led_Data.vLED_control(Led_Data.Red_Led,SET);
                delay_ms(700);
                Led_Data.vLED_control(Led_Data.Red_Led,RESET);
            }

        }
    }
}

/*����2*/
void vTASK_two(void)
{
    if(2 == TaskData.Now_task_state)
    {
        while(TaskData.Now_task_state != 0)
        {
            static uint8_t key1_temp_flag = 0;

            if(Key_Data.Key3_Down_Flag)
            {
                Key_Data.Key3_Down_Flag = 0;
                key1_temp_flag = !key1_temp_flag;
            }
            if(key1_temp_flag)
            {
                Buzzer_Data.vBUZZER_control(SET);
            }
            else
            {
                Buzzer_Data.vBUZZER_control(RESET);
            }
        }
    }
}

/*����3*/
void vTASK_three(void)
{
    if(3 == TaskData.Now_task_state)
    {
        while(TaskData.Now_task_state != 0) //ѭ����ʾ2023 0402
        {
            static uint8_t key_flag1 = 0;
            static uint8_t key_flag2 = 0;

            if(Key_Data.Key3_Down_Flag) //����3
            {
                Key_Data.Key3_Down_Flag = 0;
                //1
                uint16_t count1 = 0;
                uint32_t ms_count1 = get_clock_ticks()+2000;  //��ȡ��ǰʱ��+2000 2s
                bool flag1 = 1;
                while(count1 < 4)
                {
                    // ÿ��2000������ʱ����ˢ����ʾ
                    if(get_clock_ticks() > ms_count1)
                    {
                        ms_count1=get_clock_ticks()+2000;
                        flag1 = !flag1;   //ȡ��
                        count1++;
                    }
                    if(flag1)
                    {
                        Smg_Data.vSMG_display("2023");
                    }
                    else
                    {
                        Smg_Data.vSMG_display("0402");
                    }
                }
                Smg_Data.vSMG_off();    //�����ȫ��
            }
            if(Key_Data.Key4_Down_Flag)
            {
                Key_Data.Key4_Down_Flag = 0;
                key_flag1 = !key_flag1;
            }
            if(key_flag1)
            {
                char dis_arr1[30];
                static uint16_t sum = 0;
                static uint8_t num1 = 0;
                static uint8_t num2 = 0;
                static uint8_t num3 = 0;
                static uint8_t num4 = 0;

                sum = Lm35_Data.Lm35_temp*100;  //ȡ��
                num1 = sum/1000;    //ȡ��4λ
                num2 = sum%1000/100;    //ȡ��3λ
                num3 = sum%1000%100/10; //ȡ��2λ
                num3 = sum%1000%100%10; //ȡ��1λ

                //�����1��ʾ
                Smg_Data.vHC595_send_data(Display[num1]);
                Smg_Data.vSMG_choose(0);
                delay_ms(1);
                //�����2��ʾ+С����
                Smg_Data.vHC595_send_data(Display_1[num2]);
                Smg_Data.vSMG_choose(1);
                delay_ms(1);
                //�����3��ʾ
                Smg_Data.vHC595_send_data(Display[num3]);
                Smg_Data.vSMG_choose(2);
                delay_ms(1);
                //�����4��ʾ
                Smg_Data.vHC595_send_data(Display[num4]);
                Smg_Data.vSMG_choose(3);
                delay_ms(1);

                Lm35_Data.vLM35_run_function(); //�����¶�ִ�ж�Ӧ����
            }
            if(Key_Data.Key4_Down_Long_Flag)    //����4������ǰ�¶ȼ�10ģ��С��20��
            {
                Key_Data.Key4_Down_Long_Flag = 0;
                Lm35_Data.Lm35_temp = Lm35_Data.Lm35_temp - 10;
            }
        }
        Buzzer_Data.vBUZZER_control(RESET); //������ͣ

    }
}

/*����4*/
void vTASK_four(void)
{
    if(4 == TaskData.Now_task_state)
    {
        while(TaskData.Now_task_state != 0)
        {
            static uint8_t key_flag2 = 0;
            char dis_arr3[40];
            if(Key_Data.Key3_Down_Flag) //����3
            {
                Key_Data.Key3_Down_Flag = 0;
                key_flag2 = !key_flag2;

            }
            if(key_flag2) //����3
            {
                snprintf(dis_arr3,sizeof(dis_arr3),"��ǿ�ȣ�%.0flx    ",Bh1750_Data.Bh1750_value);   //��ʾ��ȱ���0λС��������ռ����������ʾ����
                GuiRowText(0,0+500,400, FONT_LEFT,(uint8_t*)dis_arr3);
                Bh1750_Data.vBH1750_run_function(); //���ݹ��ִ�ж�Ӧ����
            }
        }
    }
}

/*����5--��������*/
void vTASK_five(void)
{
    if(5 == TaskData.Now_task_state)
    {
        while(TaskData.Now_task_state != 0)
        {
            if(Key_Data.Key3_Down_Flag)
            {
                Key_Data.Key3_Down_Flag = 0;
                XiaoChuangData.vXIAOCHUANG_play_specify_content(4); //���ܣ�֧��ǿ��ս��
            }
            if(Key_Data.Key4_Down_Flag)
            {
                Key_Data.Key4_Down_Flag = 0;
                XiaoChuangData.vXIAOCHUANG_send_rouse();    //���ͻ���
            }
            XiaoChuangData.vUART4_rx_data_function();
            XiaoChuangData.vXIAOCHUANG_state_function();
        }
    }
}

/*����6--LCD��ʾ*/
void vTASK_six(void)
{
    if(6 == TaskData.Now_task_state)
    {
        while(TaskData.Now_task_state != 0)
        {
            if(Key_Data.Key3_Down_Flag)
            {
                Key_Data.Key3_Down_Flag = 0;
                GuiRowText(0,0+500,480, FONT_LEFT,(uint8_t*)"�����ٽ̣�������ѧ");
                fb_drawrect(300,200,500,250,Lcd_Data.Lcd_cid_color[4]);  //��ɫ���ο�200 X 50
                Lcd_Data.vLCD_gui_pentagram(60,200,50,CBLACK);  //�����
            }
        }
    }
}

/*����7*/
void vTASK_seven(void)
{
    if(7 == TaskData.Now_task_state)
    {
        Coord_init();   //��ʼ��
        while(TaskData.Now_task_state != 0)
        {
            Coord_display_date();   //UIͼ
        }
    }
}

/*����8*/
void vTASK_eight(void)
{
    if(8 == TaskData.Now_task_state)
    {
        while(TaskData.Now_task_state != 0)
        {

        }
    }
}

/*����9*/
void vTASK_nine(void)
{
    if(9 == TaskData.Now_task_state)
    {
        while(TaskData.Now_task_state != 0)
        {

        }
    }
}

/*����10*/
void vTASK_ten(void)
{
    if(10 == TaskData.Now_task_state)
    {
        while(TaskData.Now_task_state != 0)
        {

        }
    }
}

/*������(ѭ���ﰴ������)*/
void vTASK_all(void)
{
    vTASK_one();
    vTASK_two();
    vTASK_three();
    vTASK_four();
    vTASK_five();
    vTASK_six();
    vTASK_seven();
    //vTASK_eight();
    //vTASK_nine();
    //vTASK_ten();
}

