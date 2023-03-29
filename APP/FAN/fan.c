/*
 * fan.c
 *
 * created: 2023-03-26
 *  author: Yang
 *  module: ���� Ӳ�����ӣ���������FAN
 */
#include "fan.h"

//��ʼ���ṹ��
FAN_TypeDef Fan_Data =
{
    .vFAN_init = &vFAN_init,
    .vFAN_control = &vFAN_control,
    .vFAN_set_speed = &vFAN_set_speed
};


/*
���ܣ���ʼ��
*/
void vFAN_init(void)
{
    gpio_enable(FAN_PIN,DIR_OUT);//���
    Fan_Data.vFAN_control(RESET);//Ĭ�Ϲر�
    Fan_Data.vFAN_set_speed(0); //�ٶ�0
}

/*
���ܣ����Ʒ���
����:SET--�� RESET--��
*/
void vFAN_control(uint8_t swch)
{
    if(SET == swch)
    {
        gpio_write(FAN_PIN,SET);
    }
    else
    {
        gpio_write(FAN_PIN,RESET);
    }
}

/*
���ܣ�����ת�ٿ���
�������ٶ�(0~100)
*/
void vFAN_set_speed(uint8_t speed)
{
    set_lcd_brightness(speed);
}


