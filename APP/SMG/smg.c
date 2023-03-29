/*
 * smg.c
 *
 * created: 2023-03-24
 *  author: Yang
 *  module: 共阴数码管
 */
 
#include "smg.h"

//结构体初始化
SMG_TypeDef Smg_Data =
{
    .vSMG_init = &vSMG_init,
    .vHC595_send_data = &vHC595_send_data,
    .vSMG_choose = &vSMG_choose,
    .vSMG_countdown = &vSMG_countdown
};

//段码--0~F
unsigned char Display[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71}; // 不带小数点
unsigned char Display_1[] = {0xbf,0x86,0xdb,0xcf,0xef,0xed,0xfd,0x87,0xff,0xef,0xff,0x00};	// 带小数点

//数码管初始化
void vSMG_init(void)
{
    //595
    gpio_enable(SMG_SI,DIR_OUT);
    gpio_enable(SMG_RCK,DIR_OUT);
    gpio_enable(SMG_SCK,DIR_OUT);
    //COM端
    gpio_enable(SMG_COM1,DIR_OUT);
    gpio_enable(SMG_COM2,DIR_OUT);
    gpio_enable(SMG_COM3,DIR_OUT);
    gpio_enable(SMG_COM4,DIR_OUT);

    Smg_Data.vHC595_send_data(0x00);    //全灭
}

//HC595发送数据
//参数：段码数据
void vHC595_send_data(uint8_t dat)
{
    uint8_t dat_buf = 0, i;
    for(i=0; i<8; i++)
    {
        dat_buf = dat & 0x80;
        if (dat_buf)      //输出1bit数据
        {
            HC595_SI(SET);    //串行输入拉高
        }
        else
        {
            HC595_SI(RESET);    //串行输入拉低
        }
        HC595_SCK(RESET);   //时钟拉低
        delay_us(1);
        HC595_SCK(SET); //时钟拉高
        delay_us(1);
        dat <<= 1;
    }
    HC595_RCK(RESET);   //锁存拉低
    delay_us(3);
    HC595_RCK(SET);   //锁存拉高
}

//数码管选择(从左到右)
//参数：对应的数码管(0~3)
void vSMG_choose(uint8_t index)
{
    switch(index)
    {
        case 0: //1
            gpio_write(SMG_COM1,SET);
            gpio_write(SMG_COM2,RESET);
            gpio_write(SMG_COM3,RESET);
            gpio_write(SMG_COM4,RESET);
            break;
        case 1: //2
            gpio_write(SMG_COM1,RESET);
            gpio_write(SMG_COM2,SET);
            gpio_write(SMG_COM3,RESET);
            gpio_write(SMG_COM4,RESET);
            break;
        case 2: //3
            gpio_write(SMG_COM1,RESET);
            gpio_write(SMG_COM2,RESET);
            gpio_write(SMG_COM3,SET);
            gpio_write(SMG_COM4,RESET);
            break;
        case 3: //4
            gpio_write(SMG_COM1,RESET);
            gpio_write(SMG_COM2,RESET);
            gpio_write(SMG_COM3,RESET);
            gpio_write(SMG_COM4,SET);
            break;
        default:    //全部不选
            gpio_write(SMG_COM1,RESET);
            gpio_write(SMG_COM2,RESET);
            gpio_write(SMG_COM3,RESET);
            gpio_write(SMG_COM4,RESET);
            break;
    }
}

//倒计时
void vSMG_countdown(uint16_t init_value)
{
    //判断参数是否超出最大范围
    if(init_value > 9999)
    {
        init_value = 0;
    }
        
    uint16_t count = init_value;
    uint8_t temp = 0;   //段码数据
    uint32_t ms_count = get_clock_ticks()+1000;;  //获取当前时间+1000
    
    while(count > 0)
    {
        // 每隔1000个倒计时周期刷新显示
        if(get_clock_ticks() > ms_count)
        {
            ms_count=get_clock_ticks()+1000;
            count--;
        }
        //数码管1显示
        temp = Display[count / 1000];
#if 0
        if(0x3F == temp)
        {
            Smg_Data.vHC595_send_data(0x00);
        }
#endif
        Smg_Data.vSMG_choose(0);
        delay_ms(1);
        //数码管2显示
        temp = Display[count / 100 % 10];
        Smg_Data.vHC595_send_data(temp);
        Smg_Data.vSMG_choose(1);
        delay_ms(1);
        //数码管3显示
        temp = Display[count / 10 % 10];
        Smg_Data.vHC595_send_data(temp);
        Smg_Data.vSMG_choose(2);
        delay_ms(1);
        //数码管4显示
        temp = Display[count % 10];
        Smg_Data.vHC595_send_data(temp);
        Smg_Data.vSMG_choose(3);
        delay_ms(1);
    }
//倒计时完成显示0000
        //数码管1显示
        temp = Display[0];
        Smg_Data.vHC595_send_data(temp);
        Smg_Data.vSMG_choose(0);
        delay_ms(1);
        //数码管2显示
        temp = Display[0];
        Smg_Data.vHC595_send_data(temp);
        Smg_Data.vSMG_choose(1);
        delay_ms(1);
        //数码管3显示
        temp = Display[0];
        Smg_Data.vHC595_send_data(temp);
        Smg_Data.vSMG_choose(2);
        delay_ms(1);
        //数码管4显示
        temp = Display[0];
        Smg_Data.vHC595_send_data(temp);
        Smg_Data.vSMG_choose(3);
        delay_ms(1);
}



