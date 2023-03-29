/*
 * all.c
 *
 * created: 2023-03-23
 *  author: Yang
 *  module: ������
 */

#include "all.h"

/*SYS FUNCTION BEGIN*/
//ls1x_uart_write(uart, buf, size, arg);�����ַ���
//��ȡ��ǰʱ��(��λms)
extern unsigned int get_clock_ticks(void);
//��ӡ�����ڿ���̨(��Ҫ����MCUͨ�ſ���)
extern int printk(const char* format, ...);
//LCD����
extern void fb_cons_clear(void);
//������(������ˢ����Ҫ�仯�����ݣ��������ʾ�ı�����һ��)
extern void fb_fillrect(int x1, int y1, int x2, int y2, unsigned coloridx);
//����ı�
extern void fb_textout(int x, int y, char *str);

/*SYS FUNCTION END*/

/*GUI FUNCTION BEGIN*/

//д�����ı�(һ��Y���40 �����480 ֻ����ʾ15������)
extern void GuiRowText(lkdCoord x, lkdCoord y,uint16_t wide, FontFlag flag,uint8_t *str);
//����CWHITLE(��ɫ) CBLACK(��ɫ)
//#define GuiClearScreen(color) GuiFillRect(0, 0, GUIXMAX - 1,GUIXMAX - 1,color);

/*GUI FUNCTION END*/


//����1.1
void Task_1_1(void)
{
    Led_Data.vLED_control(Led_Data.Red_Led,SET);    //��
    delay_ms(1000); //��ʱ1s
    Led_Data.vLED_control(Led_Data.Red_Led,RESET);
    Led_Data.vLED_control(Led_Data.Green_Led,SET);    //��
    delay_ms(1000); //��ʱ1s
    Led_Data.vLED_control(Led_Data.Green_Led,RESET);
    Led_Data.vLED_control(Led_Data.Blue_Led,SET);    //��
    delay_ms(1000); //��ʱ1s
    Led_Data.vLED_control(Led_Data.Blue_Led,RESET);
}

//����2
void vSMG_test(void)
{
    uint16_t count = 5;
    uint8_t temp = 0;   //��������
    uint32_t ms_count1 = get_clock_ticks()+1000;  //��ȡ��ǰʱ��+1000
    uint32_t ms_count2 = 0; //500ms
    uint8_t num = 3;
    bool flag = 1;
    while(count > 0)
    {
        // ÿ��1000������ʱ����ˢ����ʾ
        if(get_clock_ticks() > ms_count1)
        {
            ms_count1=get_clock_ticks()+1000;
            count--;
        }
        //�����1��ʾ
        Smg_Data.vHC595_send_data(0x40);    //'-'
        Smg_Data.vSMG_choose(0);
        delay_ms(1);
        //�����2��ʾ
        temp = Display[count / 10 % 10];
        Smg_Data.vHC595_send_data(temp);
        Smg_Data.vSMG_choose(1);
        delay_ms(1);
        //�����3��ʾ
        temp = Display[count % 10];
        Smg_Data.vHC595_send_data(temp);
        Smg_Data.vSMG_choose(2);
        delay_ms(1);
        //�����4��ʾ
        Smg_Data.vHC595_send_data(0x40);    //'-'
        Smg_Data.vSMG_choose(3);
        delay_ms(1);
    }
    ms_count2 = get_clock_ticks()+500;
    while(num > 0)
    {
        if(flag)
        {
            Smg_Data.vHC595_send_data(0x40);    //'-'
            Smg_Data.vSMG_choose(0);
            delay_ms(1);
            //�����2��ʾ
            Smg_Data.vHC595_send_data(Display[15]);
            Smg_Data.vSMG_choose(1);
            delay_ms(1);
            //�����3��ʾ
            Smg_Data.vHC595_send_data(Display[15]);
            Smg_Data.vSMG_choose(2);
            delay_ms(1);
            //�����4��ʾ
            Smg_Data.vHC595_send_data(0x40);    //'-'
            Smg_Data.vSMG_choose(3);
            delay_ms(1);
            Led_Data.vLED_control(Led_Data.Red_Led,SET);
            Buzzer_Data.vBUZZER_control(SET);
            if(get_clock_ticks() > ms_count2)
            {
                ms_count2 = get_clock_ticks()+500;
                flag = !flag;
            }
        }
        else
        {
            Smg_Data.vHC595_send_data(0x00);
            Smg_Data.vSMG_choose(0);
            delay_ms(1);
            //�����2��ʾ
            Smg_Data.vHC595_send_data(0x00);
            Smg_Data.vSMG_choose(1);
            delay_ms(1);
            //�����3��ʾ
            Smg_Data.vHC595_send_data(0x00);
            Smg_Data.vSMG_choose(2);
            delay_ms(1);
            //�����4��ʾ
            Smg_Data.vHC595_send_data(0x00);
            Smg_Data.vSMG_choose(3);
            delay_ms(1);
            Led_Data.vLED_control(Led_Data.Red_Led,RESET);
            Buzzer_Data.vBUZZER_control(RESET);
            if(get_clock_ticks() > ms_count2)
            {
                ms_count2 = get_clock_ticks()+500;
                flag = !flag;
                num--;
            }
        }
    }

}
extern const unsigned char gImage_111[320000];
//����3
void Task_3(void)
{
    Lcd_Data.vLCD_set_bgcolor(cidxBLACK,clRED); //��
    delay_ms(1000);
    Lcd_Data.vLCD_set_bgcolor(cidxBLACK,clGREEN); //��
    delay_ms(1000);
    Lcd_Data.vLCD_set_bgcolor(cidxBLACK,clBLUE); //��
    delay_ms(1000);
    fb_cons_clear();    //����
    GuiRowText(0,100,480,FONT_LEFT,(uint8_t*)"ϲӭ��ʮ����Զ�����ߡ�");
    GuiRowText(0,140,480,FONT_LEFT,(uint8_t*)"�ܽ�������");
    //fb_textout(0,200,"ϲӭ��ʮ����Զ�����ߡ��ܽ�������");
    delay_ms(4000);
    fb_cons_clear();//����
    Lcd_Data.display_pic(50,50,400,400,(uint8_t*)gImage_111);  //��ʾͼƬ
}

uint8_t threshold = 33; //��ֵҪ����+-2

//����5(����ʱ���ж���)
void Task_5(void)
{

    if(Lm35_Data.Lm35_temp <= (threshold - 1))//��ǰ�¶�С����ֵ+-1
    {
        Fan_Data.vFAN_control(0);
        Fan_Data.vFAN_set_speed(0);
        Resistor_Data.vRESISTOR_control(SET);   //���ȴ�
        Led_Data.vLED_control(Led_Data.Green_Led,RESET);
        Led_Data.vLED_control(Led_Data.Red_Led,SET);
    }
    if(Lm35_Data.Lm35_temp >= (threshold + 1))//��ǰ�¶ȴ�����ֵ+-1
    {
        Resistor_Data.vRESISTOR_control(RESET);   //���ȹر�
        Fan_Data.vFAN_control(1);
        Fan_Data.vFAN_set_speed(100);
        Led_Data.vLED_control(Led_Data.Red_Led,RESET);
        Led_Data.vLED_control(Led_Data.Green_Led,SET);

    }
}

bool Task_7_Flag = 0;

//����
void Task_7(void)
{
    if(Ultrasound_Data.Ultrasound_distance >= 20)
    {
        Motor_Data.vMOTOR_set_speed(0); //���ת��
    }
    else if(Ultrasound_Data.Ultrasound_distance >= 10 && Ultrasound_Data.Ultrasound_distance < 20)
    {
        if(Ultrasound_Data.Ultrasound_distance <= 11)
        {
            Motor_Data.vMOTOR_set_speed(4);
        }
        else if(Ultrasound_Data.Ultrasound_distance <= 12)
        {
            Motor_Data.vMOTOR_set_speed(8);
        }
        else if(Ultrasound_Data.Ultrasound_distance <= 13)
        {
            Motor_Data.vMOTOR_set_speed(12);
        }
        else if(Ultrasound_Data.Ultrasound_distance <= 14)
        {
            Motor_Data.vMOTOR_set_speed(16);
        }
        else if(Ultrasound_Data.Ultrasound_distance <= 15)
        {
            Motor_Data.vMOTOR_set_speed(20);
        }
        else if(Ultrasound_Data.Ultrasound_distance <= 16)
        {
            Motor_Data.vMOTOR_set_speed(24);
        }
        else if(Ultrasound_Data.Ultrasound_distance <= 17)
        {
            Motor_Data.vMOTOR_set_speed(28);
        }
        else if(Ultrasound_Data.Ultrasound_distance <= 18)
        {
            Motor_Data.vMOTOR_set_speed(32);
        }
        else if(Ultrasound_Data.Ultrasound_distance <= 19)
        {
            Motor_Data.vMOTOR_set_speed(36);
        }

    }
    else if(Ultrasound_Data.Ultrasound_distance < 10)
    {
        Motor_Data.vMOTOR_set_speed(50); //ֹͣ
    }
    delay_ms(500);
    delay_ms(500);
}

