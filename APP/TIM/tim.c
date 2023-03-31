/*
 * tim.c
 *
 * created: 2023-03-24
 *  author: Yang
 *  module: 定时器
 */

#include "tim.h"


//结构体初始化
TIM_TypeDef Tim_Data =
{
    .vTIM_rtc0_init = &vTIM_rtc0_init
};

//RTC开启定时器模式(定时1ms)
void vTIM_rtc0_init(void)
{
    ls1x_rtc_init(NULL,NULL);   //初始化

    //开启RTC定时中断功能
    rtc_cfg_t rtc;
    rtc.cb = rtctimer_callback;	//定时器中断回调函数
    rtc.isr = NULL;	//中断服务函数
    rtc.interval_ms = 1;	//定时器时间间隔(ms)
    rtc.trig_datetime = NULL;	//用于toymatch的日期
    //开启定时器0
    ls1x_rtc_timer_start(DEVICE_RTCMATCH0,&rtc);
}

uint8_t led_flag = 0;
/*显示曲线图标志位*/
extern bool LM35_Over_Flag;
extern bool BH1750_Over_Flag;
extern bool Lcd_display1_flag; //任务LCD刷新
extern uint32_t Key_longtime;   //按键长按计数
//定时器回调函数
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
        
        if(10 == Time_10ms) //10ms串口接收检测
        {
            Time_10ms = 0;
            //My_uart_Data.UART5_Over_Flag = 1;
        }
        if(20 == Time_20ms) //20ms按键检测
        {
            Time_20ms = 0;
            Key_Data.vKEY_detection();
        }
        if(50 == Time_50ms) //50ms小创回传检测
        {
            Time_50ms = 0;
            XiaoChuangData.vXIAOCHUANG_order_parse();
        }
        if(100 == Time_100ms) //
        {
            Time_100ms = 0;
            Key_longtime++;
            
        }
        if(120 == Time_120ms)   //120ms读取一次光度值
        {
            Time_120ms = 0;
            Bh1750_Data.vBH1750_whole_get_data();
            Lcd_Data.Lcd_Display3_Flag = 1;
            //BH1750_Over_Flag = 1;   //曲线图光度传感器刷新标志位
        }
        if(150 == Time_150ms)   //150ms采集一次电子罗盘角度
        {
            Time_150ms = 0;
            //Hmc5883l_Data.Hmc5883l_Over_Flag = 1;
        }
        if(200 == Time_200ms)   //200ms运行一次RTC实时时钟
        {
            Time_200ms = 0;
            //myRtcData.MY_RTC_over_Flag = 1;
        }
        if(300 == Time_300ms)
        {
            Time_300ms = 0;
            //Ultrasound_Data.Ultrasound_Over_Flag = 1;
        }
        if(500 == Time_500ms)   //500ms获取一次温度
        {
            Time_500ms = 0;
            Lm35_Data.fLM35_get_temperature();
            Lcd_Data.Lcd_Display1_Flag = 1;
            LM35_Over_Flag = 1; //曲线图温度刷新标志位
            //led_flag = !led_flag;
            //Led_Data.vLED_control(Led_Data.Green_Led,led_flag); //led运行正常
        }
        if(1000 == Time_1s) //1s计算一次电机转速
        {
            Time_1s = 0;
            //Motor_Data.vMOTOR_calculate_minute_speed();
            //Lcd_Data.Lcd_Display2_Flag = 1;
        }
    }
}

