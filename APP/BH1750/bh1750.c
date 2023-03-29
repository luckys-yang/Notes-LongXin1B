/*
 * bh1750.c
 *
 * created: 2023-03-26
 *  author: Yang
 *  module: 光度传感器 ---I2C通信 ----感应芯片在板子右上角U5
 */

#include "bh1750.h"

//初始化结构体
BH1750_TypeDef Bh1750_Data =
{
    .Bh1750_value = 0.0,
    .BH1750_Read_Buff = {0},
    .BH1750_init = &BH1750_init,
    .vBH1750_Cmd_Write = &vBH1750_Cmd_Write,
    .vBH1750_start = &vBH1750_start,
    .vBH1750_read = &vBH1750_read,
    .vBH1750_convert_data = &vBH1750_convert_data,
    .vBH1750_whole_get_data = &vBH1750_whole_get_data
};

/*
功能：初始化
*/
void BH1750_init(void)
{
    Bh1750_Data.vBH1750_start();
}

/*
功能：发送设备地址
*/
void vBH1750_Cmd_Write(uint8_t cmd)
{
    uint8_t data[2]= {0};
    data[0]=cmd;

    ls1x_i2c_send_start(busI2C0,BH1750_ADDR);//起始信号
    ls1x_i2c_send_addr(busI2C0,BH1750_ADDR,0);	//发送设备地址+写信号
    ls1x_i2c_write_bytes(busI2C0, data, 1);	//内部寄存器地址
    ls1x_i2c_send_stop(busI2C0,BH1750_ADDR);	//发送停止信号
    delay_ms(5);
}

/*
功能：开启一次高分辨率模式
*/
void vBH1750_start(void)
{
    Bh1750_Data.vBH1750_Cmd_Write(BH1750_ON);   //打开
    Bh1750_Data.vBH1750_Cmd_Write(BH1750_RSET); //清空
    Bh1750_Data.vBH1750_Cmd_Write(BH1750_CON); //1lx分辨率，至少120ms(如果是ONE则会进入掉电模式每次读取都要先执行vBH1750_start)
}

/*
功能：读光照数据
*/
void vBH1750_read(void)
{
    ls1x_i2c_send_start(busI2C0, BH1750_ADDR);//开始信号
    ls1x_i2c_send_addr(busI2C0,BH1750_ADDR,1);//发送设备地址+读信号
    ls1x_i2c_read_bytes(busI2C0,Bh1750_Data.BH1750_Read_Buff, 2);//读取两个字节数据
    ls1x_i2c_send_stop(busI2C0,BH1750_ADDR);//发送停止信号
}

/*
功能：合成光照数据
返回值：最终的光照数据
*/
float vBH1750_convert_data(void)
{
    uint16_t temp = 0;  //16位

    temp = Bh1750_Data.BH1750_Read_Buff[0];
    temp = (temp<<8)+Bh1750_Data.BH1750_Read_Buff[1];		//合成数据，即光照数据
    Bh1750_Data.Bh1750_value = (float)temp/1.2;

    return Bh1750_Data.Bh1750_value;
}

/*
功能：完成一次完整的采集
*/
void vBH1750_whole_get_data(void)
{
    Bh1750_Data.vBH1750_read(); //连续读取
    Bh1750_Data.vBH1750_convert_data(); //合成
}
