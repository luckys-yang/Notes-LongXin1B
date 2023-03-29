#ifndef _FAN_H
#define _FAN_H
#include "all.h"

//∂®“Âπ‹Ω≈
#define FAN_PIN 36

typedef struct
{
    void (*vFAN_init)(void);
    void (*vFAN_control)(uint8_t);
    void (*vFAN_set_speed)(uint8_t);
}FAN_TypeDef;

extern FAN_TypeDef Fan_Data;

void vFAN_init(void);
void vFAN_control(uint8_t swch);
void vFAN_set_speed(uint8_t speed);
#endif



