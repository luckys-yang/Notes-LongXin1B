#ifndef _LED_H
#define _LED_H
#include "all.h"

//¹Ü½Å¶¨Òå
#define LED1 34 //ºì
#define LED2 37 //ÂÌ
#define LED3 35 //À¶


typedef struct
{
    uint8_t Red_Led;
    uint8_t Green_Led;
    uint8_t Blue_Led;
    void (*vLED_init)(void);
    void (*vLED_control)(uint8_t,uint8_t);
}LED_TypeDef;

extern LED_TypeDef Led_Data;


void vLED_init(void);
void vLED_control(uint8_t led_color,uint8_t swch);
#endif
