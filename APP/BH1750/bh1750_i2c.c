/*
 * bh1750_i2c.c
 *
 * created: 2023-03-26
 *  author:
 *  module: 光度传感器 ---I2C相关
 */
#include "bh1750_i2c.h"

/*********************************************************
//功  能：初始化IIC
//参  数: 无
//返回值: 无
//**********************************************************/
//void IIC_Init(void)
//{
    //gpio_enable( 32, DIR_OUT );
    //gpio_enable( 33, DIR_OUT );
    //gpio_write(32,1);
    //gpio_write(33,1);
//}

/**************************************************************
//*功  能：配置输出端口
//*参  数: 无
//*返回值: 无
//**************************************************************/
//void SDA_OUT(void)
//{
    //gpio_enable( 33, DIR_OUT );
//}

/**************************************************************
//*功  能：配置输入端口
//*参  数: 无
//*返回值: 无
//**************************************************************/
//void SDA_IN(void)
//{
    //gpio_enable( 33, DIR_IN );

//}

/*********************************************************
//功  能：产生IIC起始信号
//参  数: 无
//返回值: 无
//**********************************************************/
//void IIC_Start(void)
//{
    //SDA_OUT();     //sda线输出
    //gpio_write(33,1);
    //gpio_write(32,1);
    //delay_us(2);
    //gpio_write(33,0);//START:when CLK is high,DATA change form high to low
    //delay_us(2);
    //gpio_write(32,0);//钳住I2C总线，准备发送或接收数据
//}

/*********************************************************
//功  能：产生IIC停止信号
//参  数: 无
//返回值: 无
//**********************************************************/
//void IIC_Stop(void)
//{
    //SDA_OUT();//sda线输出
    //gpio_write(32,0);
    //gpio_write(33,0);//STOP:when CLK is high DATA change form low to high
    //delay_us(2);
    //gpio_write(32,1);
    //gpio_write(33,1);//发送I2C总线结束信号
    //delay_us(2);
//}

/*********************************************************
//功  能：等待应答信号到来
//参  数: 无
//返回值: 1，接收应答失败
        //0，接收应答成功
//**********************************************************/
//unsigned char IIC_Wait_Ack(void)
//{
    //unsigned char ucErrTime=0;
    //SDA_IN();      //SDA设置为输入
    //gpio_write(33,1);
    //delay_us(1);
    //gpio_write(32,1);
    //delay_us(1);
    //while(gpio_read( 33 ))
    //{
        //ucErrTime++;
        //if(ucErrTime>250)
        //{
            //IIC_Stop();
            //return 1;
        //}
    //}
    //gpio_write(32,0);//时钟输出0
    //return 0;
//}

/*********************************************************
//功  能：产生ACK应答
//参  数: 无
//返回值: 无
//**********************************************************/
//void IIC_Ack(void)
//{
    //gpio_write(32,0);
    //SDA_OUT();
    //gpio_write(33,0);
    //delay_us(2);
    //gpio_write(32,1);
    //delay_us(2);
    //gpio_write(32,0);
//}

/*********************************************************
//功  能：不产生ACK应答
//参  数: 无
//返回值: 无
//**********************************************************/
//void IIC_NAck(void)
//{
    //gpio_write(32,0);
    //SDA_OUT();
    //gpio_write(33,1);
    //delay_us(2);
    //gpio_write(32,1);
    //delay_us(2);
    //gpio_write(32,0);
//}

/*********************************************************
//功  能：IIC发送一个字节
//参  数: 无
//返回值: 从机有无应答
		//1，有应答
		//0，无应答
//**********************************************************/
//void IIC_Send_Byte(unsigned char txd)
//{
    //unsigned char t;
    //SDA_OUT();
    //gpio_write(32,0);//拉低时钟开始数据传输
    //for(t=0; t<8; t++)
    //{
        //gpio_write(33,(txd&0x80)>>7);
        //txd<<=1;
        //delay_us(1);   //对TEA5767这三个延时都是必须的
        //gpio_write(32,1);
        //delay_us(1);
        //gpio_write(32,0);
        //delay_us(1);
    //}
//}

/*********************************************************
//功  能：读1个字节
//参  数: ack=1时，ack=0时
//返回值: 发送ACK，发送nACK
//**********************************************************/
//unsigned char IIC_Read_Byte(unsigned char ack)
//{
    //unsigned char i,receive=0;
    //SDA_IN();//SDA设置为输入
    //for(i=0; i<8; i++ )
    //{
        //gpio_write(32,0);
        //delay_us(1);
        //gpio_write(32,1);
        //receive<<=1;
        //if(gpio_read( 33 ))
            //receive++;
        //delay_us(1);
    //}
    //if (!ack)
        //IIC_NAck();//发送nACK
    //else
        //IIC_Ack(); //发送ACK
    //return receive;
//}

/***使用模拟I2C进行编写BH1750时序***/

/*
//功能：写入指令
//参数：命令(16进制)
//*/
//void vBH1750_I2C_write(uint8_t order_addr)
//{
    //IIC_Start();    //开始信号
    //IIC_Send_Byte(BH1750_WRITE_ADDR);   //写操作
    //IIC_Wait_Ack();
    //IIC_Send_Byte(order_addr);  //发送命令
    //IIC_Wait_Ack();
    //IIC_Stop(); //停止信号
//}

/*
//功能：读取数据
//返回值：16位合成的数据
//*/
//uint16_t vBH1750_I2C_read(void)
//{
    //uint16_t H_byte,L_byte;

    //IIC_Start();    //开始信号
    //IIC_Send_Byte(BH1750_READ_ADDR);   //读操作
    //IIC_Wait_Ack();
    //H_byte = IIC_Read_Byte(1);
    //L_byte = IIC_Read_Byte(0);
    //IIC_Stop(); //停止信号
    //return (H_byte<<8)|L_byte;
//}
/*
//功能：完成一次采集
//*/
//void VBH1750_I2C_whole_get_data(void)
//{
    //uint16_t num1;
    //char test_arr[30];
    //vBH1750_I2C_write(0x01);
    //vBH1750_I2C_write(0x10);
    //num1 = vBH1750_I2C_read();
    //snprintf(test_arr,sizeof(test_arr),"当前环境光强度：%dlx    ",num1);   //显示光度保留0位小数，后面空几个格避免显示乱码
    //GuiRowText(0,0+100,400, FONT_LEFT,(uint8_t*)test_arr);
//}

