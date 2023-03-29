/*
 * lcd.c
 *
 * created: 2023-03-24
 *  author: Yang
 *  module: LCD
 */

#include "lcd.h"

char Lcd_xiaochuang_identify_display_str[15] = {0}; //С��ʶ�������ӡ����

//��ʼ���ṹ������
LCD_TypeDef Lcd_Data =
{
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
    .vLCD_display_gb2312_char = &vLCD_display_gb2312_char
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

extern uint8_t threshold;

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

    //snprintf(dis_arr2,sizeof(dis_arr2),"��ǰ��ֵ��%d��",threshold);   //��ʾ�¶ȱ���1λС��
    //GuiRowText(0,0+100,400, FONT_LEFT,dis_arr2);
    if(Lcd_Data.Lcd_Display1_Flag)  //��ʾ1
    {
        Lcd_Data.Lcd_Display1_Flag = 0;
        snprintf(dis_arr1,sizeof(dis_arr1),"��ǰ�¶ȣ�%.1f��",Lm35_Data.Lm35_temp);   //��ʾ�¶ȱ���1λС��
        GuiRowText(0,0,400, FONT_LEFT,(uint8_t*)dis_arr1); //�����ʾ�����ж���Ҳ����Ҫȥ����
        //fb_fillrect(0,50 , 480, 96, cidxBLACK);
        //fb_textout(0,50,dis_arr1);
    }
    if(Lcd_Data.Lcd_Display2_Flag)  //��ʾ2
    {
        Lcd_Data.Lcd_Display2_Flag = 0;
        snprintf(dis_arr4,sizeof(dis_arr4), "��ǰ���ת��:%drpm   ", (int)Motor_Data.Now_RPM);
        GuiRowText(0,0+200,400, FONT_LEFT,dis_arr4);
        Motor_Data.Motor_IRQ_count = 0;
    }
    if(Lcd_Data.Lcd_Display3_Flag)  //��ʾ3
    {
        Lcd_Data.Lcd_Display3_Flag = 0;
        memset(dis_arr3,0,sizeof(dis_arr3));
        snprintf(dis_arr3,sizeof(dis_arr3),"��ǰ������ǿ�ȣ�%.0flx    ",Bh1750_Data.Bh1750_value);   //��ʾ��ȱ���0λС��������ռ����������ʾ����
        GuiRowText(0,0+100,400, FONT_LEFT,(uint8_t*)dis_arr3);
    }
    if(Lcd_Data.Lcd_Display4_Flag)  //��ʾ4
    {
        Lcd_Data.Lcd_Display4_Flag = 0;
    }
}




