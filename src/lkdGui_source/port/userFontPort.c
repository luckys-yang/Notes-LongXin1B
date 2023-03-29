/**
  * @file   userFontPort.c
  * @author  guoweilkd
  * @version V0.0.0
  * @date    2018/04/18
  * @brief  lkdGui���������ӿڣ�����ֲ����亯���ľ������ݡ�
  */

#include "lkdGui.h"



/**
  *@brief ��ȡ������ģ
  *@param  code1,code2 ���ֱ���[H,L]
  *@param  pBuff ��ģbuff
  *@retval 0
  */
static uint8_t GetDfontData(uint8_t code1, uint8_t code2,uint8_t *pBuff)
{
    /* ����û����� */
    extern uint8_t GetFontGb2312_32_32(uint8_t codeH, uint8_t codeL, uint8_t *pBuff);;
    GetFontGb2312_32_32(code1, code2, pBuff);
    return 0;
}

/**
  *@brief ��ȡASCII��ģ
  *@param  code1, ����
  *@param  pBuff ��ģbuff
  *@retval 0
  */
static uint8_t GetSfontData(uint8_t code1, uint8_t *pBuff)
{
    /* ����û����� */
    uint8_t GetFontASCII_16_32(uint8_t code1, uint8_t *pBuff);
    GetFontASCII_16_32(code1,pBuff);
    return 0;
}



/* Ĭ���������ʵ�� */
lkdFont defaultFont;
/**
  *@brief �����ʼ��
  *@param  None
  *@retval None
  */
void defaultFontInit(void)
{
    /* ��������Ҫ������Ӧ���޸� */

    /* ��buff�Ĵ�С�������ģ��С���� */
    static uint8_t dataBuff[128*8];

    defaultFont.name = "GB2312[32*32]";
    defaultFont.dhigh = 32;
    defaultFont.dwide = 32;
    defaultFont.shigh = 32;
    defaultFont.swide = 16;
    defaultFont.pZmBuff = dataBuff;
    defaultFont.getDfont = GetDfontData;
    defaultFont.getSfont = GetSfontData;

    /* ����ΪϵͳĬ������ */
    GuiFontSet(&defaultFont);
    GuiSetbackcolor(CWHITLE);
    GuiSetForecolor(CBLACK);
}
