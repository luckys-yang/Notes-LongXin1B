#ifndef _MY_PWM_H
#define _MY_PWM_H
#include "all.h"

typedef struct
{
    bool PWM2_Start_Flag;   //PWM中断开启标志位
    uint32_t PWM2_Time_count;  //中断里计数
    void (*vMY_PWM2_time_init)(void);
}MY_PWM_TypeDef;

extern MY_PWM_TypeDef My_pwm_Data;

void vMY_PWM2_time_init(void);
void pwmtimer_callback(void *pwm, int *stopit);
#endif


