/*
破龙芯，支持国产！！！
*/
#include "all.h"
#include "pic.h"    //图片数组存放

#include "lkdGui.h"
#define TEST_DEBUG 1    //测试
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 700



/*USER FUNCTION BEGIN*/



void Hardware_Init(void);
/*USER FUNCTION END*/

//800*480--横屏的触摸屏 需要开启XPT2046_DRV
//480*800--竖屏的触摸屏(用不了)
char LCD_display_mode[] = LCD_800x480;

#if TEST_DEBUG
char test_arr[30];

#endif
    static uint16_t cnt = 0;
    static uint8_t dir = 1;

int main(void)
{
#if 0
    ls1x_drv_init();            		/* Initialize device drivers */
    install_3th_libraries();      		/* Install 3th libraies */
#endif

    Hardware_Init();    //硬件初始化
    for (;;)
    {
        Key_Data.vKEY_function();
        //XiaoChuangData.vUART4_rx_data_function();
        //XiaoChuangData.vXIAOCHUANG_state_function();
        //Task_while();
        //Lcd_Data.vLCD_display_function();
        //Hmc5883l_Data.vHMC5883L_direction_function();
        //Ultrasound_Data.vULTRASOUND_get_distance_function();
        //My_uart_Data.vMY_UART5_receive_data_function();
        //myRtcData.vMY_RTC_get_time_function();
    }

    return 0;
}

/*
功能：硬件初始化
*/
void Hardware_Init(void)
{
    TaskData.TASK_LCD_TIME = get_clock_ticks()+450;
    Lcd_Data.vLCD_init();   //LCD初始化
    Led_Data.vLED_init();   //LED初始化
    Key_Data.vKEY_init();   //按键初始化
    Buzzer_Data.vBUZZER_init(); //蜂鸣器初始化
    Smg_Data.vSMG_init();   //数码管初始化
    XiaoChuangData.vUART4_init();  //小创初始化
    Tim_Data.vTIM_rtc0_init();  //定时器0初始化
    Lm35_Data.vLM35_init(); //温度传感器初始化
    Resistor_Data.vRESISTOR_init(); //加热电阻初始化
    Fan_Data.vFAN_init();   //风扇初始化
    Bh1750_Data.BH1750_init();  //光度传感器初始化
    Hmc5883l_Data.vHMC5883L_init(); //电子罗盘初始化
    Motor_Data.vMOTOR_init();   //直流电机初始化
    My_pwm_Data.vMY_PWM2_time_init();    //PWM2定时器初始化(超声波用到)
    Ultrasound_Data.vULTRASOUND_init(); //超声波初始化
    My_uart_Data.vMY_UART5_init();  //串口5初始化
    myRtcData.vMY_RTC_init();   //RTC实时时钟初始化
}

