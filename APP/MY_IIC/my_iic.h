#ifndef _MY_IIC_H
#define _MY_IIC_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "ls1b.h"
#include "mips.h"
#include "tick.h"
#include "ls1b_gpio.h"


//引脚定义
#define IIC_SCL(pin,state) gpio_write(pin,state) //时钟线
#define IIC_SDA(pin,state) gpio_write(pin,state) //数据线
#define SDA_READ(pin) gpio_read(pin)  //读取数据线电平
#define SDA_INPUT(pin) gpio_enable(pin,DIR_IN)  //设置数据线为输入模式
#define SDA_OUTPUT(pin) gpio_enable(pin,DIR_OUT)  //设置数据线为输出模式

//结构体
typedef struct
{
    uint8_t SCL_Pin;    //时钟线引脚编号
    uint8_t SDA_Pin;    //数据线引脚编号
}MY_IIC_DATA_TypeDef;


void vMY_IIC_init(MY_IIC_DATA_TypeDef *dev);
void vMY_IIC_delay(void);
void vMY_IIC_start(MY_IIC_DATA_TypeDef *dev);
void vMY_IIC_stop(MY_IIC_DATA_TypeDef *dev);
uint8_t ucMY_IIC_wait_ack(MY_IIC_DATA_TypeDef *dev);
void vMY_IIC_ack(MY_IIC_DATA_TypeDef *dev);
void vMY_IIC_nack(MY_IIC_DATA_TypeDef *dev);
void vMY_IIC_send_byte(MY_IIC_DATA_TypeDef *dev,uint8_t data);
uint8_t ucMY_IIC_read_byte(MY_IIC_DATA_TypeDef *dev);
#endif

