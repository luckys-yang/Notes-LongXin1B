#ifndef _KEY_H
#define _KEY_H
#include "all.h"

//按键
#define S1 56
#define S2 57
#define S3 40
#define S4 41
//读取电平
#define KEY1 gpio_read(S1)
#define KEY2 gpio_read(S2)
#define KEY3 gpio_read(S3)
#define KEY4 gpio_read(S4)

typedef struct
{
    bool Key1_Down_Long_Flag;
    bool Key2_Down_Long_Flag;
    bool Key3_Down_Long_Flag;
    bool Key4_Down_Long_Flag;
    bool Key1_Down_Flag;
    bool Key2_Down_Flag;
    bool Key3_Down_Flag;
    bool Key4_Down_Flag;
    void (*vKEY_init)(void);
    uint8_t (*ucKEY_sub)(void);
    void (*vKEY_detection)(void);
    void (*vKEY_function)(void);
}KEY_TypeDef;

extern KEY_TypeDef Key_Data;

void vKEY_init(void);
uint8_t ucKEY_sub(void);
void vKEY_detection(void);
void vKEY_function(void);
#endif

