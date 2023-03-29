#ifndef _ULTRASOUND_H
#define _ULTRASOUND_H
#include "all.h"

//管脚定义
#define CX_TRIG 51  //发射端
#define CX_ECHO 50  //接收端(注意ECHO重名不能用)

typedef struct
{
    float Ultrasound_last_distance; //上一次距离
    bool Ultrasound_Over_Flag;  //超声波完成标志位
    float Ultrasound_distance;  //距离
    void (*vULTRASOUND_init)(void);
    float (*vULTRASOUND_get_distance_function)(void);
}ULTRASOUND_TypeDef;

extern ULTRASOUND_TypeDef Ultrasound_Data;

void vULTRASOUND_init(void);
void vULTRASOUND_IRQhandler(int IRQn,void *param);
float vULTRASOUND_get_distance_function(void);
#endif
