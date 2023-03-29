/*
 * motor.c
 *
 * created: 2023-03-27
 *  author: Yang
 *  module: ֱ�����  Ӳ�����ӣ�P2��������Ͻ�P5  P5��������Ͻ�P2(�������������PWMΪGP7101�ķ������������PWM����Խ�ߣ�����ٶ�Խ��)
 */

#include "motor.h"


//�ṹ���ʼ��
MOTOR_TypeDef Motor_Data =
{
    .Now_RPM = 0.0,
    .Motor_IRQ_count = 0,
    .vMOTOR_init = &vMOTOR_init,
    .vMOTOR_control = &vMOTOR_control,
    .vMOTOR_set_speed = &vMOTOR_set_speed,
    .vMOTOR_calculate_minute_speed = &vMOTOR_calculate_minute_speed
};

/*
���ܣ���ʼ��
*/
void vMOTOR_init(void)
{
    ls1x_install_gpio_isr(MOTOR_PIN, INT_TRIG_EDGE_DOWN, vMOTOR_IRQhandler,NULL);  // �½��ش���
    ls1x_enable_gpio_interrupt(MOTOR_PIN);  //ʹ���ж�
    set_lcd_brightness(100);  //Ĭ�Ϲر�
}

/*
���ܣ�����ֱ���������
������SET--�� RESET--��
*/
void vMOTOR_control(uint8_t swch)
{
    if(SET == swch)
    {
        set_lcd_brightness(0);
    }
    else
    {
        set_lcd_brightness(100);
    }
}

/*
���ܣ�ֱ������ٶ�
������(0~50)ֵԽ��Խ��
*/
void vMOTOR_set_speed(uint8_t speed)
{
    set_lcd_brightness(speed);
}

/*
���ܣ�����ÿ����ת��
*/
void vMOTOR_calculate_minute_speed(void)
{
    Motor_Data.Now_RPM = (float)(Motor_Data.Motor_IRQ_count*60) /(7*30); //���ٱ�30  ������һȦ7������
}


/*
���ܣ��жϷ�����
*/
void vMOTOR_IRQhandler(int IRQn,void *param)
{
    Motor_Data.Motor_IRQ_count++;   //����������
    return;
}
