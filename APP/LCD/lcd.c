/*
 * lcd.c
 *
 * created: 2023-03-24
 *  author: Yang
 *  module: LCD
 */

#include "lcd.h"

char Lcd_xiaochuang_identify_display_str[15]; //小创识别后结果打印数据

//初始化结构体数据
LCD_TypeDef Lcd_Data =
{
    .Lcd_open_Flag = 0,
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
    .vLCD_display_gb2312_char = &vLCD_display_gb2312_char,
    .vLCD_gui_display_graphics = &vLCD_gui_display_graphics,
    .vLCD_gui_equilateral_triangle = &vLCD_gui_equilateral_triangle,
    .vLCD_gui_circle = &vLCD_gui_circle,
    .vLCD_gui_pentagram = &vLCD_gui_pentagram
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
功能：在指定坐标画一个等边三角形
参数1：中心点的x
参数2：中心点的Y
参数3：三角形半径
参数4:颜色 黑色0x01(则线是白)--CBLACK 白色0x00--CWHITLE(则线是黑)
150 150 50 比较等边
*/
void vLCD_gui_equilateral_triangle(lkdCoord x, lkdCoord y, lkdCoord r, lkdColour color)
{
    /* 计算三个顶点的坐标 */

    lkdCoord x0 = x;
    lkdCoord y0 = y - r;
    lkdCoord x1 = x - r * sin(M_PI / 3);
    lkdCoord y1 = y + r / 2;
    lkdCoord x2 = x + r * sin(M_PI / 3);
    lkdCoord y2 = y + r / 2;

    /* 画三条线连接三个点 */
    GuiBiasLine(x0, y0, x1, y1, color);
    GuiBiasLine(x1, y1, x2, y2, color);
    GuiBiasLine(x2, y2, x0, y0, color);
}

/*
功能：在指定坐标画一个五角星
参数1：五角星中心点的 x
参数2：五角星中心点的y
参数3：五角星大小，即正五边形的边长
参数4:颜色 黑色0x01(则线是白)--CBLACK 白色0x00--CWHITLE(则线是黑)
*/
void vLCD_gui_pentagram(lkdCoord x, lkdCoord y, lkdCoord size, lkdColour color)
{
    /* 计算五个点的坐标 */
    lkdCoord x1 = x;
    lkdCoord y1 = y - size;
    lkdCoord x2 = x + (size * 0.951);
    lkdCoord y2 = y - (size * 0.309);
    lkdCoord x3 = x + (size * 0.588);
    lkdCoord y3 = y + (size * 0.809);
    lkdCoord x4 = x - (size * 0.588);
    lkdCoord y4 = y + (size * 0.809);
    lkdCoord x5 = x - (size * 0.951);
    lkdCoord y5 = y - (size * 0.309);

    /* 绘制五条线段 */
    GuiBiasLine(x1, y1, x3, y3, color);
    GuiBiasLine(x3, y3, x5, y5, color);
    GuiBiasLine(x5, y5, x2, y2, color);
    GuiBiasLine(x2, y2, x4, y4, color);
    GuiBiasLine(x4, y4, x1, y1, color);
}


/*
功能：在指定坐标画一个圆(Bresenham 圆算法)
参数1：圆心坐标的x
参数2：圆心坐标的Y
参数3：圆心半径
参数4:颜色 黑色0x01(则线是白)--CBLACK 白色0x00--CWHITLE(则线是黑)
实现过程：从圆心向四周绘制像素点。具体来说，在 while 循环中，我们从圆的上部开始，
          首先绘制它的上方 180 度弧度的点，然后利用对称性绘制它的下方 180 度弧度的点。
          在循环中不断更新 x、y 坐标的偏移量以获取新的像素位置，同时计算出当前像素所在的距离
          圆周最近的整数值（即 d 值），并用于决定下一步采取何种策略。最终绘制出一个完整的圆形。
*/
void vLCD_gui_circle(lkdCoord x, lkdCoord y, lkdCoord r, lkdColour color)
{
    /* 从圆心向四周绘制像素 */
    int16_t x_offset = 0;
    int16_t y_offset = r;
    int16_t d = 3 - (r << 1);
    while (x_offset <= y_offset)
    {
        GuiPoint(x + x_offset, y + y_offset, color);
        GuiPoint(x + x_offset, y - y_offset, color);
        GuiPoint(x - x_offset, y + y_offset, color);
        GuiPoint(x - x_offset, y - y_offset, color);
        GuiPoint(x + y_offset, y + x_offset, color);
        GuiPoint(x + y_offset, y - x_offset, color);
        GuiPoint(x - y_offset, y + x_offset, color);
        GuiPoint(x - y_offset, y - x_offset, color);
        if (d < 0)
        {
            d += (x_offset << 2) + 6;  //d=d+4*x_offset+6
        }
        else
        {
            d += ((x_offset - y_offset) << 2) + 10;  //d=d+4*(x_offset-y_offset)+10
            y_offset--;
        }
        x_offset++;
    }
}


/*
功能：GUI画矩形，正方形
参数1：图形编号(1--矩形 2--正方形)
参数2：颜色 黑色0x01(则线是白)--CBLACK 白色0x00--CWHITLE(则线是黑)
*/
void vLCD_gui_display_graphics(uint8_t graphics_id,uint8_t wire_color)
{
    switch(graphics_id)
    {
        case 1:
            {
                GuiRect(10,20,200,60,wire_color);   //长：x1-x0 = 190 宽：y1-y0 = 40
                break;
            }
        case 2:
            {
                GuiRect(10,80,210,280,wire_color);   //长：x1-x0 = 200 宽：y1-y0 = 200
                break;
            }
        default :
            break;
    }

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

extern uint8_t ms_count;

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

    if(Lcd_Data.Lcd_open_Flag)
    {
        if(Lcd_Data.Lcd_Display1_Flag)  //显示1
        {
            Lcd_Data.Lcd_Display1_Flag = 0;
            snprintf(dis_arr1,sizeof(dis_arr1),"当前温度：%.1f℃",Lm35_Data.Lm35_temp);//显示温度保留1位小数
            GuiRowText(0,0,400,FONT_LEFT,dis_arr1);
            Lm35_Data.vLM35_run_function(); //根据温度执行对应功能
        }
        if(Lcd_Data.Lcd_Display3_Flag)  //显示3
        {
            Lcd_Data.Lcd_Display3_Flag = 0;
            memset(dis_arr3,0,sizeof(dis_arr3));
            snprintf(dis_arr3,sizeof(dis_arr3),"当前环境光强度：%.0flx    ",Bh1750_Data.Bh1750_value);   //显示光度保留0位小数，后面空几个格避免显示乱码
            GuiRowText(0,0+100,400, FONT_LEFT,(uint8_t*)dis_arr3);
            Bh1750_Data.vBH1750_run_function(); //根据光度执行对应功能
        }
        if(Lcd_Data.Lcd_Display2_Flag)  //显示2
        {
            Lcd_Data.Lcd_Display2_Flag = 0;
            //snprintf(dis_arr4,sizeof(dis_arr4), "当前电机转速:%drpm   ", (int)Motor_Data.Now_RPM);
            //GuiRowText(0,0+200,400, FONT_LEFT,dis_arr4);
            //Motor_Data.Motor_IRQ_count = 0;
        }
        if(Lcd_Data.Lcd_Display4_Flag)  //显示4
        {
            Lcd_Data.Lcd_Display4_Flag = 0;
        }
    }


}




