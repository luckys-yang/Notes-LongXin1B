/*
 * buzzer.c
 *
 * created: 2023-03-24
 *  author: Yang
 *  module: ������
 */
 
#include "buzzer.h"

//�ṹ���ʼ��
BUZZER_TypeDef Buzzer_Data =
{
    .vBUZZER_init = &vBUZZER_init,
    .vBUZZER_control = &vBUZZER_control
};


//��������ʼ��
void vBUZZER_init(void)
{
    gpio_enable(BUZZER,DIR_OUT);    //���
    gpio_write(BUZZER,RESET);   //�ر�
}

//����\�رշ�����
//������SET--�� RESET--��
void vBUZZER_control(uint8_t swch)
{
    if(SET == swch)
    {
        gpio_write(BUZZER,SET);
    }
    else
    {
        gpio_write(BUZZER,RESET);
    }
}


