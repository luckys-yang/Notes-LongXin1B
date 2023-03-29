/*
 * my_iic.c
 *
 * created: 2023-03-27
 *  author: Yang
 *  module: I2C通用驱动
 */
#include "my_iic.h"

/*
功能：IIC初始化
参数：指向 MY_IIC_DATA_TypeDef 类型的指针
*/
void vMY_IIC_init(MY_IIC_DATA_TypeDef *dev)
{
    gpio_enable(dev->SCL_Pin,DIR_OUT);    //时钟线输出模式
    gpio_enable(dev->SDA_Pin,DIR_OUT);    //数据线输出模式
    IIC_SCL(dev->SCL_Pin,1);    //拉高
    IIC_SDA(dev->SDA_Pin,1);    //拉高
}

/*
功能：延时
一般延时5us
*/
void vMY_IIC_delay(void)
{
    delay_us(5);
}

/*
功能：产生开始信号
参数：指向 MY_IIC_DATA_TypeDef 类型的指针
*/
void vMY_IIC_start(MY_IIC_DATA_TypeDef *dev)
{
    SDA_OUTPUT(dev->SDA_Pin);   //数据线输出模式
    IIC_SDA(dev->SDA_Pin,1);    //拉高
    vMY_IIC_delay();    
    IIC_SCL(dev->SCL_Pin,1);    //拉高
    vMY_IIC_delay();    
    IIC_SDA(dev->SDA_Pin,0);    //拉低
    vMY_IIC_delay();    
    IIC_SCL(dev->SDA_Pin,0);    //拉低
    vMY_IIC_delay();    
}

/*
功能：产生停止信号
参数：指向 MY_IIC_DATA_TypeDef 类型的指针
*/
void vMY_IIC_stop(MY_IIC_DATA_TypeDef *dev)
{
    SDA_OUTPUT(dev->SDA_Pin);   //数据线输出模式
    IIC_SCL(dev->SCL_Pin,0);    //拉低
    vMY_IIC_delay();
    IIC_SDA(dev->SDA_Pin,0);    //拉低
    vMY_IIC_delay();
    IIC_SCL(dev->SCL_Pin,1);    //拉高
    vMY_IIC_delay();
    IIC_SDA(dev->SDA_Pin,1);    //拉高
    vMY_IIC_delay();
}

/*
功能：等待应答
参数：指向 MY_IIC_DATA_TypeDef 类型的指针
返回值：1--接收应答失败 0--接收应答成功
*/
uint8_t ucMY_IIC_wait_ack(MY_IIC_DATA_TypeDef *dev)
{
    uint8_t ucErrorTime = 0;    //超时计数
    
    SDA_INPUT(dev->SDA_Pin);    //数据线输入模式
    IIC_SDA(dev->SDA_Pin,1);    //拉高
    vMY_IIC_delay();
    IIC_SCL(dev->SCL_Pin,1);    //拉高
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
    IIC_SCL(dev->SCL_Pin,0);    //拉低
    return 0;
}

/*
功能：产生应答
参数：指向 MY_IIC_DATA_TypeDef 类型的指针
*/
void vMY_IIC_ack(MY_IIC_DATA_TypeDef *dev)
{
    IIC_SCL(dev->SCL_Pin,0);    //拉低
    vMY_IIC_delay();
    SDA_OUTPUT(dev->SDA_Pin);   //数据线输出模式
    IIC_SDA(dev->SDA_Pin,0);    //拉低
    vMY_IIC_delay();
    IIC_SCL(dev->SCL_Pin,1);    //拉高
    vMY_IIC_delay();
    IIC_SCL(dev->SCL_Pin,0);    //拉低
    vMY_IIC_delay();
}

/*
功能：不产生应答
参数：指向 MY_IIC_DATA_TypeDef 类型的指针
*/
void vMY_IIC_nack(MY_IIC_DATA_TypeDef *dev)
{
    IIC_SCL(dev->SCL_Pin,0);    //拉低
    vMY_IIC_delay();
    SDA_OUTPUT(dev->SDA_Pin);   //数据线输出模式
    IIC_SDA(dev->SDA_Pin,1);    //拉高
    vMY_IIC_delay();
    IIC_SCL(dev->SCL_Pin,1);    //拉高
    vMY_IIC_delay();
    IIC_SCL(dev->SCL_Pin,0);    //拉低
    vMY_IIC_delay();
}

/*
功能：发送一个字节
参数1：指向 MY_IIC_DATA_TypeDef 类型的指针
参数2：待发送的数据
*/
void vMY_IIC_send_byte(MY_IIC_DATA_TypeDef *dev,uint8_t data)
{
    uint8_t i = 8;
    
    SDA_OUTPUT(dev->SDA_Pin);   //数据线输出模式
    while(i--)
    {
        IIC_SCL(dev->SCL_Pin,0);    //拉低
        vMY_IIC_delay();
        IIC_SDA(dev->SDA_Pin,data&0x80);    //SDA输出data的最高位
        vMY_IIC_delay();
        data <<= 1;   //左移1位
        vMY_IIC_delay();
        IIC_SCL(dev->SCL_Pin,1);    //拉高
        vMY_IIC_delay();
    }
    IIC_SCL(dev->SCL_Pin,0);    //拉低
    vMY_IIC_delay();
}
/*
功能：读取一个字节
参数1：指向 MY_IIC_DATA_TypeDef 类型的指针
返回值：读取的数据(一个字节)
*/
uint8_t ucMY_IIC_read_byte(MY_IIC_DATA_TypeDef *dev)
{
    uint8_t i = 8;
    uint8_t read_temp = 0;
    
    SDA_INPUT(dev->SDA_Pin);    //数据线输入模式
    while(i--)
    {
        read_temp <<= 1;    //读入的数据左移1位(第一次的话 0<<1还是0)
        IIC_SCL(dev->SCL_Pin,0);    //拉低
        vMY_IIC_delay();
        IIC_SCL(dev->SCL_Pin,1);    //拉高
        vMY_IIC_delay();
        read_temp |= SDA_READ(dev->SDA_Pin);    //将读取的数据的值(0或1)返回给read_temp
    }
    IIC_SCL(dev->SCL_Pin,0);    //拉低
    vMY_IIC_delay();
    SDA_OUTPUT(dev->SDA_Pin);   //数据线输出模式
    return read_temp;
}
