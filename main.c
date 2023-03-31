/*
����о��֧�ֹ���������
*/
#include "all.h"
#include "pic.h"    //ͼƬ������

#include "lkdGui.h"
#define TEST_DEBUG 1    //����
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 700



/*USER FUNCTION BEGIN*/



void Hardware_Init(void);
/*USER FUNCTION END*/

//800*480--�����Ĵ����� ��Ҫ����XPT2046_DRV
//480*800--�����Ĵ�����(�ò���)
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

    Hardware_Init();    //Ӳ����ʼ��
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
���ܣ�Ӳ����ʼ��
*/
void Hardware_Init(void)
{
    TaskData.TASK_LCD_TIME = get_clock_ticks()+450;
    Lcd_Data.vLCD_init();   //LCD��ʼ��
    Led_Data.vLED_init();   //LED��ʼ��
    Key_Data.vKEY_init();   //������ʼ��
    Buzzer_Data.vBUZZER_init(); //��������ʼ��
    Smg_Data.vSMG_init();   //����ܳ�ʼ��
    XiaoChuangData.vUART4_init();  //С����ʼ��
    Tim_Data.vTIM_rtc0_init();  //��ʱ��0��ʼ��
    Lm35_Data.vLM35_init(); //�¶ȴ�������ʼ��
    Resistor_Data.vRESISTOR_init(); //���ȵ����ʼ��
    Fan_Data.vFAN_init();   //���ȳ�ʼ��
    Bh1750_Data.BH1750_init();  //��ȴ�������ʼ��
    Hmc5883l_Data.vHMC5883L_init(); //�������̳�ʼ��
    Motor_Data.vMOTOR_init();   //ֱ�������ʼ��
    My_pwm_Data.vMY_PWM2_time_init();    //PWM2��ʱ����ʼ��(�������õ�)
    Ultrasound_Data.vULTRASOUND_init(); //��������ʼ��
    My_uart_Data.vMY_UART5_init();  //����5��ʼ��
    myRtcData.vMY_RTC_init();   //RTCʵʱʱ�ӳ�ʼ��
}

