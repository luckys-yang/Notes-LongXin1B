#ifndef _LCD_H
#define _LCD_H
#include "all.h"

typedef struct
{
    uint32_t Lcd_cl_color[8];    //������ɫ(32λ)
    uint16_t Lcd_cid_color[9];   //������ɫ(16λ)
    bool Lcd_Display8_Flag;  //LCDˢ�¡�8����־λ
    bool Lcd_Display7_Flag;  //LCDˢ�¡�7����־λ
    bool Lcd_Display6_Flag;  //LCDˢ�¡�6����־λ
    bool Lcd_Display5_Flag;  //LCDˢ�¡�5����־λ
    bool Lcd_Display4_Flag;  //LCDˢ�¡�4����־λ
    bool Lcd_Display3_Flag;  //LCDˢ�¡�3����־λ
    bool Lcd_Display2_Flag;  //LCDˢ�¡�2����־λ
    bool Lcd_Display1_Flag;  //LCDˢ�¡�1����־λ
    void (*vLCD_set_bgcolor)(unsigned,unsigned);
    void (*display_pic)(unsigned int,unsigned int,unsigned int,unsigned int,unsigned char*);
    void (*vLCD_display_function)(void);
    void (*vLCD_init)(void);
    void (*vLCD_set_fgcolor)(unsigned,unsigned);
    void (*vLCD_display_text)(uint16_t,uint16_t,char*);
    void (*vLCD_disaplay_color_text)(uint16_t,uint16_t,char*,unsigned);
    void (*vLCD_display_gb2312_char)(uint16_t,uint16_t,char*);
    
}LCD_TypeDef;

extern LCD_TypeDef Lcd_Data;
extern char Lcd_xiaochuang_identify_display_str[15];


void vLCD_init(void);//��ʼ��
void vLCD_set_bgcolor(unsigned color_cidx, unsigned color_cl);//���ñ�����ɫ
void display_pic(unsigned int xpos,unsigned int ypos,unsigned int x1,unsigned int y1,unsigned char *ptrs);//ͼƬ��ʾ
void vLCD_display_function(void);//��ʾ����
void vLCD_set_fgcolor(unsigned color_cidx, unsigned color_cl);//����������ɫ
void vLCD_display_text(uint16_t x1,uint16_t y1,char* str1);//ָ��������ʾ�ַ���
void vLCD_disaplay_color_text(uint16_t x1,uint16_t y1,char* str1,unsigned color_cidx);//ָ��������ɫ��ʾ�ַ���
void vLCD_display_gb2312_char(uint16_t x1,uint16_t y1,char *str1);//ָ��������ʾһ������
#endif

