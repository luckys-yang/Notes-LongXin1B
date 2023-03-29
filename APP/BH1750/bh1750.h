#ifndef _BH1750_H
#define _BH1750_H
#include "all.h"


#define BH1750_ADDR 0x23    //默认地址 0100 011
#define BH1750_ON   0x01    //等待测量命令
#define BH1750_CON  0x10    //以1 lx 分辨率开始测量测量时间通常为 120 毫秒
#define BH1750_ONE  0x20    //以 1 lx 分辨率开始测量测量时间通常为 120 毫秒测量后自动设置为掉电模式
#define BH1750_RSET 0x07    //复位数据寄存器值复位命令

typedef struct
{
    float Bh1750_value; //最终光度值(单位lx)
    uint8_t BH1750_Read_Buff[2];    //存储读取的待合成的光照值2字节
    void (*BH1750_init)(void);
    void (*vBH1750_Cmd_Write)(uint8_t);
    void (*vBH1750_start)(void);
    void (*vBH1750_read)(void);
    float (*vBH1750_convert_data)(void);
    void (*vBH1750_whole_get_data)(void);
}BH1750_TypeDef;

extern BH1750_TypeDef Bh1750_Data;

void BH1750_init(void);
void vBH1750_Cmd_Write(uint8_t cmd);
void vBH1750_start(void);
void vBH1750_read(void);
float vBH1750_convert_data(void);
void vBH1750_whole_get_data(void);
#endif


