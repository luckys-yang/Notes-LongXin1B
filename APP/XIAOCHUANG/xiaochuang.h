#ifndef _XIAOCHUANG_H
#define _XIAOCHUANG_H
#include "all.h"

//����ܽ�
#define USART4_GPIO 58
#define UART4_RX_MAX_LEN 30 //������󳤶�

typedef struct
{
    bool UART4_Rx_Over_Flag;    //������Ч������ɱ�־λ
    uint8_t Rx_Data[8]; //��Ч���ݻ���
    char UART4_RX_BUFF[UART4_RX_MAX_LEN];   //�������ݴ洢����
    uint8_t XiaoChuang_return_state;    //С���ش�״̬(���ڷֱ治ͬ�ش�0~255)
    void (*vUART4_init)(void);
    void (*vXIAOCHUANG_order_parse)(void);
    void (*vXIAOCHUANG_state_function)(void);
    void (*vXIAOCHUANG_play_specify_content)(int);
} XIAOCHUANG_TypeDef;

extern XIAOCHUANG_TypeDef XiaoChuangData;

void vUART4_init(void);
void vUART4_IRQhandler(int IRQn,void* param);
void vXIAOCHUANG_order_parse(void);
void vXIAOCHUANG_state_function(void);
void vXIAOCHUANG_play_specify_content(int id);
#endif


