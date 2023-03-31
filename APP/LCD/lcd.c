/*
 * lcd.c
 *
 * created: 2023-03-24
 *  author: Yang
 *  module: LCD
 */

#include "lcd.h"

char Lcd_xiaochuang_identify_display_str[15]; //С��ʶ�������ӡ����

//��ʼ���ṹ������
LCD_TypeDef Lcd_Data =
{
    .Lcd_open_Flag = 0,
    /*
    0��ɫ 1��ɫ 2��ɫ 3��ɫ 4��ɫ 5��ɫ 6��ɫ 7��ɫ
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
    0��ɫ 1��ɫ 2��ɫ 3��ɫ 4��ɫ 5��ɫ 6��ɫ 7��ɫ 8��ɫ
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
���ܣ���ʼ��
*/
void vLCD_init(void)
{
    lwmem_initialize(0);    //��ʼ����(LCDҪ)
    defaultFontInit();  //�ֿ��ʼ��
    fb_open();  //��ʼ������LCD��ʾ
    GuiClearScreen(CBLACK);  //����
    fb_cons_clear();    //����
    Lcd_Data.vLCD_set_fgcolor(Lcd_Data.Lcd_cid_color[2],Lcd_Data.Lcd_cl_color[2]);  //������ɫ
}

/*
���ܣ����ô�������ɫ
����1--color_cidx(��ls1x_fb.h386������)
����2--color_cl(��ls1x_fb.h350������)
*/
void vLCD_set_bgcolor(unsigned color_cidx, unsigned color_cl)
{
    fb_set_bgcolor(color_cidx,color_cl);
    fb_cons_clear();    //����(������Ч)
}

/*
���ܣ�������ɫ
����1--color_cidx(��ls1x_fb.h386������)
����2--color_cl(��ls1x_fb.h350������)
*/
void vLCD_set_fgcolor(unsigned color_cidx, unsigned color_cl)
{
    fb_set_fgcolor(color_cidx,color_cl);
}

/*
���ܣ���ָ��������ʾ�ַ���
����1��x(��Χ0~780)
����2��Y(��Χ0~460)
����3���ַ���
*/
void vLCD_display_text(uint16_t x1,uint16_t y1,char* str1)
{
    fb_textout(x1,y1,str1);
}

/*
���ܣ���ָ��������ʾָ����ɫ���ַ���
����1��x(��Χ0~780)
����2��Y(��Χ0~460)
����3���ַ���
����4��������ɫ
*/
void vLCD_disaplay_color_text(uint16_t x1,uint16_t y1,char* str1,unsigned color_cidx)
{
    fb_put_string(x1,y1,str1,color_cidx);
}

/*
���ܣ���ָ��������ʾһ������
����1��x(��Χ0~780)
����2��Y(��Χ0~460)
����3��һ�������ַ���
*/
void vLCD_display_gb2312_char(uint16_t x1,uint16_t y1,char *str1)
{
    fb_draw_gb2312_char(x1,y1,str1);
}

/*
���ܣ���ָ�����껭һ���ȱ�������
����1�����ĵ��x
����2�����ĵ��Y
����3�������ΰ뾶
����4:��ɫ ��ɫ0x01(�����ǰ�)--CBLACK ��ɫ0x00--CWHITLE(�����Ǻ�)
150 150 50 �Ƚϵȱ�
*/
void vLCD_gui_equilateral_triangle(lkdCoord x, lkdCoord y, lkdCoord r, lkdColour color)
{
    /* ����������������� */

    lkdCoord x0 = x;
    lkdCoord y0 = y - r;
    lkdCoord x1 = x - r * sin(M_PI / 3);
    lkdCoord y1 = y + r / 2;
    lkdCoord x2 = x + r * sin(M_PI / 3);
    lkdCoord y2 = y + r / 2;

    /* ������������������ */
    GuiBiasLine(x0, y0, x1, y1, color);
    GuiBiasLine(x1, y1, x2, y2, color);
    GuiBiasLine(x2, y2, x0, y0, color);
}

/*
���ܣ���ָ�����껭һ�������
����1����������ĵ�� x
����2����������ĵ��y
����3������Ǵ�С����������εı߳�
����4:��ɫ ��ɫ0x01(�����ǰ�)--CBLACK ��ɫ0x00--CWHITLE(�����Ǻ�)
*/
void vLCD_gui_pentagram(lkdCoord x, lkdCoord y, lkdCoord size, lkdColour color)
{
    /* �������������� */
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

    /* ���������߶� */
    GuiBiasLine(x1, y1, x3, y3, color);
    GuiBiasLine(x3, y3, x5, y5, color);
    GuiBiasLine(x5, y5, x2, y2, color);
    GuiBiasLine(x2, y2, x4, y4, color);
    GuiBiasLine(x4, y4, x1, y1, color);
}


/*
���ܣ���ָ�����껭һ��Բ(Bresenham Բ�㷨)
����1��Բ�������x
����2��Բ�������Y
����3��Բ�İ뾶
����4:��ɫ ��ɫ0x01(�����ǰ�)--CBLACK ��ɫ0x00--CWHITLE(�����Ǻ�)
ʵ�ֹ��̣���Բ�������ܻ������ص㡣������˵���� while ѭ���У����Ǵ�Բ���ϲ���ʼ��
          ���Ȼ��������Ϸ� 180 �Ȼ��ȵĵ㣬Ȼ�����öԳ��Ի��������·� 180 �Ȼ��ȵĵ㡣
          ��ѭ���в��ϸ��� x��y �����ƫ�����Ի�ȡ�µ�����λ�ã�ͬʱ�������ǰ�������ڵľ���
          Բ�����������ֵ���� d ֵ���������ھ�����һ����ȡ���ֲ��ԡ����ջ��Ƴ�һ��������Բ�Ρ�
*/
void vLCD_gui_circle(lkdCoord x, lkdCoord y, lkdCoord r, lkdColour color)
{
    /* ��Բ�������ܻ������� */
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
���ܣ�GUI�����Σ�������
����1��ͼ�α��(1--���� 2--������)
����2����ɫ ��ɫ0x01(�����ǰ�)--CBLACK ��ɫ0x00--CWHITLE(�����Ǻ�)
*/
void vLCD_gui_display_graphics(uint8_t graphics_id,uint8_t wire_color)
{
    switch(graphics_id)
    {
        case 1:
            {
                GuiRect(10,20,200,60,wire_color);   //����x1-x0 = 190 ��y1-y0 = 40
                break;
            }
        case 2:
            {
                GuiRect(10,80,210,280,wire_color);   //����x1-x0 = 200 ��y1-y0 = 200
                break;
            }
        default :
            break;
    }

}


/*
���ܣ���ʾͼƬ
����1��x
����2��y
����3������
����4������
����5����ʾ������
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
���ܣ�ˢ����ʾ
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
        if(Lcd_Data.Lcd_Display1_Flag)  //��ʾ1
        {
            Lcd_Data.Lcd_Display1_Flag = 0;
            snprintf(dis_arr1,sizeof(dis_arr1),"��ǰ�¶ȣ�%.1f��",Lm35_Data.Lm35_temp);//��ʾ�¶ȱ���1λС��
            GuiRowText(0,0,400,FONT_LEFT,dis_arr1);
            Lm35_Data.vLM35_run_function(); //�����¶�ִ�ж�Ӧ����
        }
        if(Lcd_Data.Lcd_Display3_Flag)  //��ʾ3
        {
            Lcd_Data.Lcd_Display3_Flag = 0;
            memset(dis_arr3,0,sizeof(dis_arr3));
            snprintf(dis_arr3,sizeof(dis_arr3),"��ǰ������ǿ�ȣ�%.0flx    ",Bh1750_Data.Bh1750_value);   //��ʾ��ȱ���0λС��������ռ����������ʾ����
            GuiRowText(0,0+100,400, FONT_LEFT,(uint8_t*)dis_arr3);
            Bh1750_Data.vBH1750_run_function(); //���ݹ��ִ�ж�Ӧ����
        }
        if(Lcd_Data.Lcd_Display2_Flag)  //��ʾ2
        {
            Lcd_Data.Lcd_Display2_Flag = 0;
            //snprintf(dis_arr4,sizeof(dis_arr4), "��ǰ���ת��:%drpm   ", (int)Motor_Data.Now_RPM);
            //GuiRowText(0,0+200,400, FONT_LEFT,dis_arr4);
            //Motor_Data.Motor_IRQ_count = 0;
        }
        if(Lcd_Data.Lcd_Display4_Flag)  //��ʾ4
        {
            Lcd_Data.Lcd_Display4_Flag = 0;
        }
    }


}




