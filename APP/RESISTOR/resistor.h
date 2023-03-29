#ifndef _RESISTOR_H
#define _RESISTOR_H
#include "all.h"

//∂®“Âπ‹Ω≈
#define RESISTOR_PIN 38

typedef struct
{
    void (*vRESISTOR_init)(void);
    void (*vRESISTOR_control)(uint8_t);
}RESISTOR_TypeDef;

extern RESISTOR_TypeDef Resistor_Data;

void vRESISTOR_init(void);
void vRESISTOR_control(uint8_t swch);
#endif

