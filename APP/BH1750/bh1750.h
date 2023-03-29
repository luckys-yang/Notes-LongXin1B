#ifndef _BH1750_H
#define _BH1750_H
#include "all.h"


#define BH1750_ADDR 0x23    //Ĭ�ϵ�ַ 0100 011
#define BH1750_ON   0x01    //�ȴ���������
#define BH1750_CON  0x10    //��1 lx �ֱ��ʿ�ʼ��������ʱ��ͨ��Ϊ 120 ����
#define BH1750_ONE  0x20    //�� 1 lx �ֱ��ʿ�ʼ��������ʱ��ͨ��Ϊ 120 ����������Զ�����Ϊ����ģʽ
#define BH1750_RSET 0x07    //��λ���ݼĴ���ֵ��λ����

typedef struct
{
    float Bh1750_value; //���չ��ֵ(��λlx)
    uint8_t BH1750_Read_Buff[2];    //�洢��ȡ�Ĵ��ϳɵĹ���ֵ2�ֽ�
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


