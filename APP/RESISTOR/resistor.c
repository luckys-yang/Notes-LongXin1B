/*
 * resistor.c
 *
 * created: 2023-03-26
 *  author: Yang
 *  module: ���ȵ���
 */
 
#include "resistor.h"

//�ṹ���ʼ��
RESISTOR_TypeDef Resistor_Data =
{
    .vRESISTOR_init = &vRESISTOR_init,
    .vRESISTOR_control = &vRESISTOR_control
};
/*
���ܣ���ʼ��
*/
void vRESISTOR_init(void)
{
    gpio_enable(RESISTOR_PIN,DIR_OUT);  //���ģʽ
    Resistor_Data.vRESISTOR_control(RESET); //Ĭ�Ϲر�״̬
}

/*
���ܣ����Ƽ��ȵ��迪��
������SET--�� RESET--��
*/
void vRESISTOR_control(uint8_t swch)
{
    if(SET == swch)
    {
        gpio_write(RESISTOR_PIN,SET); //��
    }
    else
    {
        gpio_write(RESISTOR_PIN,RESET); //��
    }
}
