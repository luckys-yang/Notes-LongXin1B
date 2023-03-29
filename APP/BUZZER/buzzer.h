#ifndef _BUZZER_H
#define _BUZZER_H
#include "all.h"

//π‹Ω≈∂®“Â
#define BUZZER 46

typedef struct
{
    void (*vBUZZER_init)(void);
    void (*vBUZZER_control)(uint8_t);
}BUZZER_TypeDef;

extern BUZZER_TypeDef Buzzer_Data;

void vBUZZER_init(void);
void vBUZZER_control(uint8_t swch);
#endif

