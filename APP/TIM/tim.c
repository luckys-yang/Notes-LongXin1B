/*
 * tim.c
 *
 * created: 2023-03-24
 *  author: Yang
 *  module: ��ʱ��
 */

#include "tim.h"


//�ṹ���ʼ��
TIM_TypeDef Tim_Data =
{
    .vTIM_rtc0_init = &vTIM_rtc0_init
};

//RTC������ʱ��ģʽ(��ʱ1ms)
void vTIM_rtc0_init(void)
{
    ls1x_rtc_init(NULL,NULL);   //��ʼ��

    //����RTC��ʱ�жϹ���
    rtc_cfg_t rtc;
    rtc.cb = rtctimer_callback;	//��ʱ���жϻص�����
    rtc.isr = NULL;	//�жϷ�����
    rtc.interval_ms = 1;	//��ʱ��ʱ����(ms)
    rtc.trig_datetime = NULL;	//����toymatch������
    //������ʱ��0
    ls1x_rtc_timer_start(DEVICE_RTCMATCH0,&rtc);
}

uint8_t led_flag = 0;
/*��ʾ����ͼ��־λ*/
extern bool LM35_Over_Flag;
extern bool BH1750_Over_Flag;
extern bool Lcd_display1_flag; //����LCDˢ��
extern uint32_t Key_longtime;   //������������
//��ʱ���ص�����
void rtctimer_callback(int device, unsigned match, int *stop)
{
    static uint16_t Time_1s = 0;
    static uint16_t Time_500ms = 0;
    static uint16_t Time_300ms = 0;
    static uint8_t Time_200ms = 0;
    static uint8_t Time_150ms = 0;
    static uint8_t Time_120ms = 0;
    static uint8_t Time_100ms = 0;
    static uint8_t Time_50ms = 0;
    static uint8_t Time_20ms = 0;
    static uint8_t Time_10ms = 0;
    
    if(DEVICE_RTCMATCH0 == device)
    {
        Time_10ms++;
        Time_20ms++;
        Time_50ms++;
        Time_100ms++;
        Time_200ms++;
        Time_120ms++;
        Time_150ms++;
        Time_300ms++;
        Time_500ms++;
        Time_1s++;
        
        if(10 == Time_10ms) //10ms���ڽ��ռ��
        {
            Time_10ms = 0;
            //My_uart_Data.UART5_Over_Flag = 1;
        }
        if(20 == Time_20ms) //20ms�������
        {
            Time_20ms = 0;
            Key_Data.vKEY_detection();
        }
        if(50 == Time_50ms) //50msС���ش����
        {
            Time_50ms = 0;
            XiaoChuangData.vXIAOCHUANG_order_parse();
        }
        if(100 == Time_100ms) //
        {
            Time_100ms = 0;
            Key_longtime++;
            
        }
        if(120 == Time_120ms)   //120ms��ȡһ�ι��ֵ
        {
            Time_120ms = 0;
            Bh1750_Data.vBH1750_whole_get_data();
            Lcd_Data.Lcd_Display3_Flag = 1;
            //BH1750_Over_Flag = 1;   //����ͼ��ȴ�����ˢ�±�־λ
        }
        if(150 == Time_150ms)   //150ms�ɼ�һ�ε������̽Ƕ�
        {
            Time_150ms = 0;
            //Hmc5883l_Data.Hmc5883l_Over_Flag = 1;
        }
        if(200 == Time_200ms)   //200ms����һ��RTCʵʱʱ��
        {
            Time_200ms = 0;
            //myRtcData.MY_RTC_over_Flag = 1;
        }
        if(300 == Time_300ms)
        {
            Time_300ms = 0;
            //Ultrasound_Data.Ultrasound_Over_Flag = 1;
        }
        if(500 == Time_500ms)   //500ms��ȡһ���¶�
        {
            Time_500ms = 0;
            Lm35_Data.fLM35_get_temperature();
            Lcd_Data.Lcd_Display1_Flag = 1;
            LM35_Over_Flag = 1; //����ͼ�¶�ˢ�±�־λ
            //led_flag = !led_flag;
            //Led_Data.vLED_control(Led_Data.Green_Led,led_flag); //led��������
        }
        if(1000 == Time_1s) //1s����һ�ε��ת��
        {
            Time_1s = 0;
            //Motor_Data.vMOTOR_calculate_minute_speed();
            //Lcd_Data.Lcd_Display2_Flag = 1;
        }
    }
}

