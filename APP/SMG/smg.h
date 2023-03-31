#ifndef _SMG_H
#define _SMG_H
#include "all.h"

//管脚定义
#define SMG_SI 39
#define SMG_RCK 48
#define SMG_SCK 49
#define SMG_COM1 45
#define SMG_COM2 44
#define SMG_COM3 43
#define SMG_COM4 42

#define  HC595_SI(val)  gpio_write(SMG_SI,val) //控制595芯片串行输入（Serial Input）管脚的电平
#define  HC595_RCK(val) gpio_write(SMG_RCK,val) //控制595芯片锁存（Latch）管脚的电平
#define  HC595_SCK(val) gpio_write(SMG_SCK,val) //控制595芯片串行时钟（Serial Clock）管脚的电平

typedef struct
{
    void (*vSMG_init)(void);
    void (*vHC595_send_data)(uint8_t);
    void (*vSMG_choose)(uint8_t);
    void (*vSMG_countdown)(uint16_t);
    void (*vSMG_display)(uint8_t*);
    void (*vSMG_off)(void);
    
}SMG_TypeDef;

extern SMG_TypeDef Smg_Data;
extern unsigned char Display[16];
extern unsigned char Display_1[];


void vSMG_init(void);
void vHC595_send_data(uint8_t dat);
void vSMG_choose(uint8_t index);
void vSMG_countdown(uint16_t init_value);
void vSMG_display(uint8_t *str);
void vSMG_off(void);
#endif

