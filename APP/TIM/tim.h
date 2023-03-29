#ifndef _TIM_H
#define _TIM_H
#include "all.h"

typedef struct
{
    void (*vTIM_rtc0_init)(void);
}TIM_TypeDef;

extern TIM_TypeDef Tim_Data;

void vTIM_rtc0_init(void);
void rtctimer_callback(int device, unsigned match, int *stop);
#endif

