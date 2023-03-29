#ifndef _LM35_H
#define _LM35_H
#include "all.h"

typedef struct
{
    float Lm35_temp;    //读取的温度值
    void (*vLM35_init)(void);
    float (*fLM35_get_temperature)(void);
    
}LM35_TypeDef;


extern LM35_TypeDef Lm35_Data;


void vLM35_init(void);
float fLM35_get_temperature(void);
#endif

