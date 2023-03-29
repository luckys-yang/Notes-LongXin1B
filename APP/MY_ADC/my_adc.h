#ifndef _MY_ADC_H
#define _MY_ADC_H
#include "all.h"

typedef struct
{
    bool Adc_Over_Flag; //ADC采集完成标志位
    float Adc1_value;   //ADC1
    float Adc2_value;   //ADC2
    float Adc3_value;   //ADC3
    float Adc4_value;   //ADC4
    void (*vMY_ADC_get_value)(void);
}MY_ADC_TypeDef;

extern MY_ADC_TypeDef myAdcData;

void vMY_ADC_get_value(void);
#endif



