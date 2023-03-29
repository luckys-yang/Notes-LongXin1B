#ifndef _MOTOR_H
#define _MOTOR_H
#include "all.h"

//���Ŷ���
#define MOTOR_PIN 53    //��������

typedef struct
{
    float Now_RPM;    //��ǰת��
    volatile uint32_t Motor_IRQ_count;   //(������)�жϴ���
    void (*vMOTOR_init)(void);
    void (*vMOTOR_control)(uint8_t);
    void (*vMOTOR_set_speed)(uint8_t);
    void (*vMOTOR_calculate_minute_speed)(void);
    
}MOTOR_TypeDef;

extern MOTOR_TypeDef Motor_Data;

void vMOTOR_init(void);
void vMOTOR_IRQhandler(int IRQn,void *param);
void vMOTOR_control(uint8_t swch);
void vMOTOR_set_speed(uint8_t speed);
void vMOTOR_calculate_minute_speed(void);
#endif


//PWM--ÿ����ת��
//0 ---370
//20	��
//5---350
//40
//10---310
//50
//15---260
//50
//20---210
//40
//25---170
//50
//30---120
//40
//35---80
//50
//40---30
//20
//42---10
//10
//43---0
