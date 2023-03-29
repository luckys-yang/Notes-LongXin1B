/*
 * my_pwm.c
 *
 * created: 2023-03-28
 *  author: Yang
 *  module: PWM
 */

#include "my_pwm.h"

//初始化结构体
MY_PWM_TypeDef My_pwm_Data =
{
    .PWM2_Start_Flag = 0,
    .PWM2_Time_count = 0,
    .vMY_PWM2_time_init = &vMY_PWM2_time_init
};

pwm_cfg_t pwm2_cfg;
/*
功能：PWM2当做定时器初始化(超声波需要用到)
*/
void vMY_PWM2_time_init(void)
{
    pwm2_cfg.hi_ns = 5000;  //高电平脉冲宽度(ns)定时器模式仅用hi_ns
    pwm2_cfg.lo_ns = NULL;  //低电平脉冲宽度(ns)定时器模式没用
    pwm2_cfg.mode = PWM_CONTINUE_TIMER; //脉冲持续产生
    pwm2_cfg.cb = pwmtimer_callback;    //定时器中断回调函数
    pwm2_cfg.isr = NULL;    //工作在定时器模式
    
    ls1x_pwm_init(devPWM2,NULL);    //PWM初始化
    ls1x_pwm_open(devPWM2,(void *)&pwm2_cfg);   //PWM打开
}

/*
功能：中断回调函数
*/
void pwmtimer_callback(void *pwm, int *stopit)
{
    if(My_pwm_Data.PWM2_Start_Flag)
    {
        My_pwm_Data.PWM2_Time_count++;
    }
}




