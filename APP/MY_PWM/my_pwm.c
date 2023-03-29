/*
 * my_pwm.c
 *
 * created: 2023-03-28
 *  author: Yang
 *  module: PWM
 */

#include "my_pwm.h"

//��ʼ���ṹ��
MY_PWM_TypeDef My_pwm_Data =
{
    .PWM2_Start_Flag = 0,
    .PWM2_Time_count = 0,
    .vMY_PWM2_time_init = &vMY_PWM2_time_init
};

pwm_cfg_t pwm2_cfg;
/*
���ܣ�PWM2������ʱ����ʼ��(��������Ҫ�õ�)
*/
void vMY_PWM2_time_init(void)
{
    pwm2_cfg.hi_ns = 5000;  //�ߵ�ƽ������(ns)��ʱ��ģʽ����hi_ns
    pwm2_cfg.lo_ns = NULL;  //�͵�ƽ������(ns)��ʱ��ģʽû��
    pwm2_cfg.mode = PWM_CONTINUE_TIMER; //�����������
    pwm2_cfg.cb = pwmtimer_callback;    //��ʱ���жϻص�����
    pwm2_cfg.isr = NULL;    //�����ڶ�ʱ��ģʽ
    
    ls1x_pwm_init(devPWM2,NULL);    //PWM��ʼ��
    ls1x_pwm_open(devPWM2,(void *)&pwm2_cfg);   //PWM��
}

/*
���ܣ��жϻص�����
*/
void pwmtimer_callback(void *pwm, int *stopit)
{
    if(My_pwm_Data.PWM2_Start_Flag)
    {
        My_pwm_Data.PWM2_Time_count++;
    }
}




