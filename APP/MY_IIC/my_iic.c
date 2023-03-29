/*
 * my_iic.c
 *
 * created: 2023-03-27
 *  author: Yang
 *  module: I2Cͨ������
 */
#include "my_iic.h"

/*
���ܣ�IIC��ʼ��
������ָ�� MY_IIC_DATA_TypeDef ���͵�ָ��
*/
void vMY_IIC_init(MY_IIC_DATA_TypeDef *dev)
{
    gpio_enable(dev->SCL_Pin,DIR_OUT);    //ʱ�������ģʽ
    gpio_enable(dev->SDA_Pin,DIR_OUT);    //���������ģʽ
    IIC_SCL(dev->SCL_Pin,1);    //����
    IIC_SDA(dev->SDA_Pin,1);    //����
}

/*
���ܣ���ʱ
һ����ʱ5us
*/
void vMY_IIC_delay(void)
{
    delay_us(5);
}

/*
���ܣ�������ʼ�ź�
������ָ�� MY_IIC_DATA_TypeDef ���͵�ָ��
*/
void vMY_IIC_start(MY_IIC_DATA_TypeDef *dev)
{
    SDA_OUTPUT(dev->SDA_Pin);   //���������ģʽ
    IIC_SDA(dev->SDA_Pin,1);    //����
    vMY_IIC_delay();    
    IIC_SCL(dev->SCL_Pin,1);    //����
    vMY_IIC_delay();    
    IIC_SDA(dev->SDA_Pin,0);    //����
    vMY_IIC_delay();    
    IIC_SCL(dev->SDA_Pin,0);    //����
    vMY_IIC_delay();    
}

/*
���ܣ�����ֹͣ�ź�
������ָ�� MY_IIC_DATA_TypeDef ���͵�ָ��
*/
void vMY_IIC_stop(MY_IIC_DATA_TypeDef *dev)
{
    SDA_OUTPUT(dev->SDA_Pin);   //���������ģʽ
    IIC_SCL(dev->SCL_Pin,0);    //����
    vMY_IIC_delay();
    IIC_SDA(dev->SDA_Pin,0);    //����
    vMY_IIC_delay();
    IIC_SCL(dev->SCL_Pin,1);    //����
    vMY_IIC_delay();
    IIC_SDA(dev->SDA_Pin,1);    //����
    vMY_IIC_delay();
}

/*
���ܣ��ȴ�Ӧ��
������ָ�� MY_IIC_DATA_TypeDef ���͵�ָ��
����ֵ��1--����Ӧ��ʧ�� 0--����Ӧ��ɹ�
*/
uint8_t ucMY_IIC_wait_ack(MY_IIC_DATA_TypeDef *dev)
{
    uint8_t ucErrorTime = 0;    //��ʱ����
    
    SDA_INPUT(dev->SDA_Pin);    //����������ģʽ
    IIC_SDA(dev->SDA_Pin,1);    //����
    vMY_IIC_delay();
    IIC_SCL(dev->SCL_Pin,1);    //����
    vMY_IIC_delay();
    
    while(SDA_READ(dev->SDA_Pin))
    {
        ucErrorTime++;
        if(ucErrorTime > 250)
        {
            vMY_IIC_stop(dev);
            return 1;
        }
    }
    IIC_SCL(dev->SCL_Pin,0);    //����
    return 0;
}

/*
���ܣ�����Ӧ��
������ָ�� MY_IIC_DATA_TypeDef ���͵�ָ��
*/
void vMY_IIC_ack(MY_IIC_DATA_TypeDef *dev)
{
    IIC_SCL(dev->SCL_Pin,0);    //����
    vMY_IIC_delay();
    SDA_OUTPUT(dev->SDA_Pin);   //���������ģʽ
    IIC_SDA(dev->SDA_Pin,0);    //����
    vMY_IIC_delay();
    IIC_SCL(dev->SCL_Pin,1);    //����
    vMY_IIC_delay();
    IIC_SCL(dev->SCL_Pin,0);    //����
    vMY_IIC_delay();
}

/*
���ܣ�������Ӧ��
������ָ�� MY_IIC_DATA_TypeDef ���͵�ָ��
*/
void vMY_IIC_nack(MY_IIC_DATA_TypeDef *dev)
{
    IIC_SCL(dev->SCL_Pin,0);    //����
    vMY_IIC_delay();
    SDA_OUTPUT(dev->SDA_Pin);   //���������ģʽ
    IIC_SDA(dev->SDA_Pin,1);    //����
    vMY_IIC_delay();
    IIC_SCL(dev->SCL_Pin,1);    //����
    vMY_IIC_delay();
    IIC_SCL(dev->SCL_Pin,0);    //����
    vMY_IIC_delay();
}

/*
���ܣ�����һ���ֽ�
����1��ָ�� MY_IIC_DATA_TypeDef ���͵�ָ��
����2�������͵�����
*/
void vMY_IIC_send_byte(MY_IIC_DATA_TypeDef *dev,uint8_t data)
{
    uint8_t i = 8;
    
    SDA_OUTPUT(dev->SDA_Pin);   //���������ģʽ
    while(i--)
    {
        IIC_SCL(dev->SCL_Pin,0);    //����
        vMY_IIC_delay();
        IIC_SDA(dev->SDA_Pin,data&0x80);    //SDA���data�����λ
        vMY_IIC_delay();
        data <<= 1;   //����1λ
        vMY_IIC_delay();
        IIC_SCL(dev->SCL_Pin,1);    //����
        vMY_IIC_delay();
    }
    IIC_SCL(dev->SCL_Pin,0);    //����
    vMY_IIC_delay();
}
/*
���ܣ���ȡһ���ֽ�
����1��ָ�� MY_IIC_DATA_TypeDef ���͵�ָ��
����ֵ����ȡ������(һ���ֽ�)
*/
uint8_t ucMY_IIC_read_byte(MY_IIC_DATA_TypeDef *dev)
{
    uint8_t i = 8;
    uint8_t read_temp = 0;
    
    SDA_INPUT(dev->SDA_Pin);    //����������ģʽ
    while(i--)
    {
        read_temp <<= 1;    //�������������1λ(��һ�εĻ� 0<<1����0)
        IIC_SCL(dev->SCL_Pin,0);    //����
        vMY_IIC_delay();
        IIC_SCL(dev->SCL_Pin,1);    //����
        vMY_IIC_delay();
        read_temp |= SDA_READ(dev->SDA_Pin);    //����ȡ�����ݵ�ֵ(0��1)���ظ�read_temp
    }
    IIC_SCL(dev->SCL_Pin,0);    //����
    vMY_IIC_delay();
    SDA_OUTPUT(dev->SDA_Pin);   //���������ģʽ
    return read_temp;
}
