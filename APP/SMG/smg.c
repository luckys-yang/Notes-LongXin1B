/*
 * smg.c
 *
 * created: 2023-03-24
 *  author: Yang
 *  module: ���������
 */
 
#include "smg.h"

//�ṹ���ʼ��
SMG_TypeDef Smg_Data =
{
    .vSMG_init = &vSMG_init,
    .vHC595_send_data = &vHC595_send_data,
    .vSMG_choose = &vSMG_choose,
    .vSMG_countdown = &vSMG_countdown
};

//����--0~F
unsigned char Display[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71}; // ����С����
unsigned char Display_1[] = {0xbf,0x86,0xdb,0xcf,0xef,0xed,0xfd,0x87,0xff,0xef,0xff,0x00};	// ��С����

//����ܳ�ʼ��
void vSMG_init(void)
{
    //595
    gpio_enable(SMG_SI,DIR_OUT);
    gpio_enable(SMG_RCK,DIR_OUT);
    gpio_enable(SMG_SCK,DIR_OUT);
    //COM��
    gpio_enable(SMG_COM1,DIR_OUT);
    gpio_enable(SMG_COM2,DIR_OUT);
    gpio_enable(SMG_COM3,DIR_OUT);
    gpio_enable(SMG_COM4,DIR_OUT);

    Smg_Data.vHC595_send_data(0x00);    //ȫ��
}

//HC595��������
//��������������
void vHC595_send_data(uint8_t dat)
{
    uint8_t dat_buf = 0, i;
    for(i=0; i<8; i++)
    {
        dat_buf = dat & 0x80;
        if (dat_buf)      //���1bit����
        {
            HC595_SI(SET);    //������������
        }
        else
        {
            HC595_SI(RESET);    //������������
        }
        HC595_SCK(RESET);   //ʱ������
        delay_us(1);
        HC595_SCK(SET); //ʱ������
        delay_us(1);
        dat <<= 1;
    }
    HC595_RCK(RESET);   //��������
    delay_us(3);
    HC595_RCK(SET);   //��������
}

//�����ѡ��(������)
//��������Ӧ�������(0~3)
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
        default:    //ȫ����ѡ
            gpio_write(SMG_COM1,RESET);
            gpio_write(SMG_COM2,RESET);
            gpio_write(SMG_COM3,RESET);
            gpio_write(SMG_COM4,RESET);
            break;
    }
}

//����ʱ
void vSMG_countdown(uint16_t init_value)
{
    //�жϲ����Ƿ񳬳����Χ
    if(init_value > 9999)
    {
        init_value = 0;
    }
        
    uint16_t count = init_value;
    uint8_t temp = 0;   //��������
    uint32_t ms_count = get_clock_ticks()+1000;;  //��ȡ��ǰʱ��+1000
    
    while(count > 0)
    {
        // ÿ��1000������ʱ����ˢ����ʾ
        if(get_clock_ticks() > ms_count)
        {
            ms_count=get_clock_ticks()+1000;
            count--;
        }
        //�����1��ʾ
        temp = Display[count / 1000];
#if 0
        if(0x3F == temp)
        {
            Smg_Data.vHC595_send_data(0x00);
        }
#endif
        Smg_Data.vSMG_choose(0);
        delay_ms(1);
        //�����2��ʾ
        temp = Display[count / 100 % 10];
        Smg_Data.vHC595_send_data(temp);
        Smg_Data.vSMG_choose(1);
        delay_ms(1);
        //�����3��ʾ
        temp = Display[count / 10 % 10];
        Smg_Data.vHC595_send_data(temp);
        Smg_Data.vSMG_choose(2);
        delay_ms(1);
        //�����4��ʾ
        temp = Display[count % 10];
        Smg_Data.vHC595_send_data(temp);
        Smg_Data.vSMG_choose(3);
        delay_ms(1);
    }
//����ʱ�����ʾ0000
        //�����1��ʾ
        temp = Display[0];
        Smg_Data.vHC595_send_data(temp);
        Smg_Data.vSMG_choose(0);
        delay_ms(1);
        //�����2��ʾ
        temp = Display[0];
        Smg_Data.vHC595_send_data(temp);
        Smg_Data.vSMG_choose(1);
        delay_ms(1);
        //�����3��ʾ
        temp = Display[0];
        Smg_Data.vHC595_send_data(temp);
        Smg_Data.vSMG_choose(2);
        delay_ms(1);
        //�����4��ʾ
        temp = Display[0];
        Smg_Data.vHC595_send_data(temp);
        Smg_Data.vSMG_choose(3);
        delay_ms(1);
}



