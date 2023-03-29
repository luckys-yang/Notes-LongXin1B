#ifndef _MY_UART_H
#define _MY_UART_H
#include "all.h"

//���յ���󳤶�
#define UART5_RX_MAX_LEN 50

typedef struct
{
    bool UART5_Over_Flag;   //ʱ��Ƭ���б�־λ
    char Uart5_rx_buff[UART5_RX_MAX_LEN];   //��������
    uint8_t Uart5_rx_len;   //���ճ���
    void (*vMY_UART5_init)(void);
    void (*vMY_UART5_receive_data_function)(void);
    void (*vMY_UART5_run_function)(void);
}MY_UART_TypeDef;

extern MY_UART_TypeDef My_uart_Data;


void vMY_UART5_init(void);
void vMY_UART5_receive_data_function(void);
void vMY_UART5_run_function(void);
#endif


