#ifndef _LCD_H
#define _LCD_H
#include "all.h"

typedef struct
{
    bool Lcd_open_Flag; //打开显示LCD标志位
    uint32_t Lcd_cl_color[8];    //清屏颜色(32位)
    uint16_t Lcd_cid_color[9];   //字体颜色(16位)
    bool Lcd_Display8_Flag;  //LCD刷新【8】标志位
    bool Lcd_Display7_Flag;  //LCD刷新【7】标志位
    bool Lcd_Display6_Flag;  //LCD刷新【6】标志位
    bool Lcd_Display5_Flag;  //LCD刷新【5】标志位
    bool Lcd_Display4_Flag;  //LCD刷新【4】标志位
    bool Lcd_Display3_Flag;  //LCD刷新【3】标志位
    bool Lcd_Display2_Flag;  //LCD刷新【2】标志位
    bool Lcd_Display1_Flag;  //LCD刷新【1】标志位
    void (*vLCD_set_bgcolor)(unsigned,unsigned);
    void (*display_pic)(unsigned int,unsigned int,unsigned int,unsigned int,unsigned char*);
    void (*vLCD_display_function)(void);
    void (*vLCD_init)(void);
    void (*vLCD_set_fgcolor)(unsigned,unsigned);
    void (*vLCD_display_text)(uint16_t,uint16_t,char*);
    void (*vLCD_disaplay_color_text)(uint16_t,uint16_t,char*,unsigned);
    void (*vLCD_display_gb2312_char)(uint16_t,uint16_t,char*);
    void (*vLCD_gui_display_graphics)(uint8_t,uint8_t);
    void (*vLCD_gui_equilateral_triangle)(lkdCoord, lkdCoord, lkdCoord, lkdColour);
    void (*vLCD_gui_circle)(lkdCoord,lkdCoord,lkdCoord,lkdColour);
    void (*vLCD_gui_pentagram)(lkdCoord,lkdCoord,lkdCoord,lkdColour);
    
}LCD_TypeDef;

extern LCD_TypeDef Lcd_Data;
extern char Lcd_xiaochuang_identify_display_str[15];


void vLCD_init(void);//初始化
void vLCD_set_bgcolor(unsigned color_cidx, unsigned color_cl);//设置背景颜色
void display_pic(unsigned int xpos,unsigned int ypos,unsigned int x1,unsigned int y1,unsigned char *ptrs);//图片显示
void vLCD_display_function(void);//显示函数
void vLCD_set_fgcolor(unsigned color_cidx, unsigned color_cl);//设置字体颜色
void vLCD_display_text(uint16_t x1,uint16_t y1,char* str1);//指定坐标显示字符串
void vLCD_disaplay_color_text(uint16_t x1,uint16_t y1,char* str1,unsigned color_cidx);//指定坐标颜色显示字符串
void vLCD_display_gb2312_char(uint16_t x1,uint16_t y1,char *str1);//指定坐标显示一个汉字
void vLCD_gui_display_graphics(uint8_t graphics_id,uint8_t wire_color); //画矩形、正方形
void vLCD_gui_equilateral_triangle(lkdCoord x, lkdCoord y, lkdCoord r, lkdColour color);//画等边三角形
void vLCD_gui_circle(lkdCoord x, lkdCoord y, lkdCoord r, lkdColour color);  //画圆
void vLCD_gui_pentagram(lkdCoord x, lkdCoord y, lkdCoord size, lkdColour color);    //画五角星
#endif

