/*
 * lcd.c
 *
 * created: 2023-03-24
 *  author: Yang
 *  module: LCD
 */

#include "lcd.h"

char Lcd_xiaochuang_identify_display_str[15] = {0}; //小创识别后结果打印数据

//初始化结构体数据
LCD_TypeDef Lcd_Data =
{
    /*
    0黑色 1蓝色 2绿色 3青色 4红色 5紫色 6黄色 7白色
    */
    .Lcd_cl_color =
    {
        clBLACK,    
        clBLUE,
        clGREEN,   
        clCYAN, 
        clRED, 
        clVIOLET, 
        clYELLOW,   
        clWHITE 
    },
    /*
    0黑色 1蓝色 2绿色 3青色 4红色 5紫色 6黄色 7白色 8灰色
    */
    .Lcd_cid_color =
    {
        cidxBLACK,  
        cidxBLUE,  
        cidxGREEN,  
        cidxCYAN,   
        cidxRED,    
        cidxVIOLET,
        cidxYELLOW, 
        cidxWHITE, 
        cidxGREY
    },
    .Lcd_Display8_Flag = 0,
    .Lcd_Display7_Flag = 0,
    .Lcd_Display6_Flag = 0,
    .Lcd_Display5_Flag = 0,
    .Lcd_Display4_Flag = 0,
    .Lcd_Display3_Flag = 0,
    .Lcd_Display2_Flag = 0,
    .Lcd_Display1_Flag = 0,
    .vLCD_set_bgcolor = &vLCD_set_bgcolor,
    .display_pic = &display_pic,
    .vLCD_display_function = &vLCD_display_function,
    .vLCD_init = &vLCD_init,
    .vLCD_set_fgcolor = &vLCD_set_fgcolor,
    .vLCD_display_text = &vLCD_display_text,
    .vLCD_disaplay_color_text = &vLCD_disaplay_color_text,
    .vLCD_display_gb2312_char = &vLCD_display_gb2312_char
};

/*
功能：初始化
*/
void vLCD_init(void)
{
    lwmem_initialize(0);    //初始化堆(LCD要)
    defaultFontInit();  //字库初始化
    fb_open();  //初始化并打开LCD显示
    GuiClearScreen(CBLACK);  //清屏
    fb_cons_clear();    //清屏
    Lcd_Data.vLCD_set_fgcolor(Lcd_Data.Lcd_cid_color[2],Lcd_Data.Lcd_cl_color[2]);  //字体颜色
}

/*
功能：设置纯背景颜色
参数1--color_cidx(在ls1x_fb.h386行左右)
参数2--color_cl(在ls1x_fb.h350行左右)
*/
void vLCD_set_bgcolor(unsigned color_cidx, unsigned color_cl)
{
    fb_set_bgcolor(color_cidx,color_cl);
    fb_cons_clear();    //清屏(否则不生效)
}

/*
功能：字体颜色
参数1--color_cidx(在ls1x_fb.h386行左右)
参数2--color_cl(在ls1x_fb.h350行左右)
*/
void vLCD_set_fgcolor(unsigned color_cidx, unsigned color_cl)
{
    fb_set_fgcolor(color_cidx,color_cl);
}

/*
功能：在指定坐标显示字符串
参数1：x(范围0~780)
参数2：Y(范围0~460)
参数3：字符串
*/
void vLCD_display_text(uint16_t x1,uint16_t y1,char* str1)
{
    fb_textout(x1,y1,str1);
}

/*
功能：在指定坐标显示指定颜色的字符串
参数1：x(范围0~780)
参数2：Y(范围0~460)
参数3：字符串
参数4：字体颜色
*/
void vLCD_disaplay_color_text(uint16_t x1,uint16_t y1,char* str1,unsigned color_cidx)
{
    fb_put_string(x1,y1,str1,color_cidx);
}

/*
功能：在指定坐标显示一个汉字
参数1：x(范围0~780)
参数2：Y(范围0~460)
参数3：一个汉字字符串
*/
void vLCD_display_gb2312_char(uint16_t x1,uint16_t y1,char *str1)
{
    fb_draw_gb2312_char(x1,y1,str1);
}



/*
功能：显示图片
参数1：x
参数2：y
参数3：像素
参数4：像素
参数5：显示的数组
*/
void display_pic(unsigned int xpos,unsigned int ypos,unsigned int x1,unsigned int y1,unsigned char *ptrs)
{
    int x, y;
    unsigned char *ptr = ptrs;

    for (y=0; y<y1; y++)
    {
        for (x=0; x<x1; x++)
        {
            unsigned int color;

            color = (*ptr << 8) | *(ptr+1);

            ls1x_draw_rgb565_pixel(x+xpos, y+ypos, color);

            ptr += 2;
        }
    }

    flush_dcache();
}

extern uint8_t threshold;

/*
功能：刷新显示
*/
void vLCD_display_function(void)
{
    char dis_arr1[50] = {0};
    char dis_arr2[50] = {0};
    char dis_arr3[50] = {0};
    char dis_arr4[50] = {0};
    char dis_arr5[50] = {0};
    char dis_arr6[50] = {0};

    //snprintf(dis_arr2,sizeof(dis_arr2),"当前阈值：%d℃",threshold);   //显示温度保留1位小数
    //GuiRowText(0,0+100,400, FONT_LEFT,dis_arr2);
    if(Lcd_Data.Lcd_Display1_Flag)  //显示1
    {
        Lcd_Data.Lcd_Display1_Flag = 0;
        snprintf(dis_arr1,sizeof(dis_arr1),"当前温度：%.1f℃",Lm35_Data.Lm35_temp);   //显示温度保留1位小数
        GuiRowText(0,0,400, FONT_LEFT,(uint8_t*)dis_arr1); //这个显示不会有抖动也不需要去覆盖
        //fb_fillrect(0,50 , 480, 96, cidxBLACK);
        //fb_textout(0,50,dis_arr1);
    }
    if(Lcd_Data.Lcd_Display2_Flag)  //显示2
    {
        Lcd_Data.Lcd_Display2_Flag = 0;
        snprintf(dis_arr4,sizeof(dis_arr4), "当前电机转速:%drpm   ", (int)Motor_Data.Now_RPM);
        GuiRowText(0,0+200,400, FONT_LEFT,dis_arr4);
        Motor_Data.Motor_IRQ_count = 0;
    }
    if(Lcd_Data.Lcd_Display3_Flag)  //显示3
    {
        Lcd_Data.Lcd_Display3_Flag = 0;
        memset(dis_arr3,0,sizeof(dis_arr3));
        snprintf(dis_arr3,sizeof(dis_arr3),"当前环境光强度：%.0flx    ",Bh1750_Data.Bh1750_value);   //显示光度保留0位小数，后面空几个格避免显示乱码
        GuiRowText(0,0+100,400, FONT_LEFT,(uint8_t*)dis_arr3);
    }
    if(Lcd_Data.Lcd_Display4_Flag)  //显示4
    {
        Lcd_Data.Lcd_Display4_Flag = 0;
    }
}




