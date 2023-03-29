#ifndef _ULTRASOUND_H
#define _ULTRASOUND_H
#include "all.h"

//�ܽŶ���
#define CX_TRIG 51  //�����
#define CX_ECHO 50  //���ն�(ע��ECHO����������)

typedef struct
{
    float Ultrasound_last_distance; //��һ�ξ���
    bool Ultrasound_Over_Flag;  //��������ɱ�־λ
    float Ultrasound_distance;  //����
    void (*vULTRASOUND_init)(void);
    float (*vULTRASOUND_get_distance_function)(void);
}ULTRASOUND_TypeDef;

extern ULTRASOUND_TypeDef Ultrasound_Data;

void vULTRASOUND_init(void);
void vULTRASOUND_IRQhandler(int IRQn,void *param);
float vULTRASOUND_get_distance_function(void);
#endif
