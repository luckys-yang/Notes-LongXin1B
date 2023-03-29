#ifndef _XIAOCHUANG_H
#define _XIAOCHUANG_H
#include "all.h"

//定义管脚
#define USART4_GPIO 58
#define UART4_RX_MAX_LEN 30 //接收最大长度

typedef struct
{
    bool UART4_Rx_Over_Flag;    //接收有效数据完成标志位
    uint8_t Rx_Data[8]; //有效数据缓存
    char UART4_RX_BUFF[UART4_RX_MAX_LEN];   //接收数据存储数组
    uint8_t XiaoChuang_return_state;    //小创回传状态(用于分辨不同回传0~255)
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


