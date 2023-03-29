#ifndef _HMC5883L_H
#define _HMC5883L_H
#include "all.h"
#include "my_iic.h"
//定义引脚
#define HMC5883L_SDA 29 //数据线管脚
#define HMC5883L_SCL 28 //时钟线管脚
//写操作地址
#define HMC5883L_WRITE_ADDR 0x3C
//读操作地址
#define HMC5883L_READ_ADDR 0x3D
//寄存器地址
#define HMC5883L_REGISTER_A 0x00    //A
#define HMC5883L_REGISTER_B 0x01    //B
#define HMC5883L_REGISTER_MODE 0x02    //模式

typedef struct
{
    bool Hmc5883l_Over_Flag;    //运行标志位
    float Angle_value;  //角度值
    bool Hmc588l_WN_Flag;    //西北
    bool Hmc588l_WS_Flag;    //西南
    bool Hmc588l_ES_Flag;    //东南
    bool Hmc588l_EN_Flag;    //东北
    bool Hmc588l_W_Flag;    //西
    bool Hmc588l_E_Flag;    //东
    bool Hmc588l_S_Flag;    //南
    bool Hmc588l_N_Flag;    //北
    void (*vHMC5883L_init)(void);
    uint8_t (*ucHMC5883L_read)(MY_IIC_DATA_TypeDef *,uint8_t);
    uint8_t (*ucHMC5883L_write)(MY_IIC_DATA_TypeDef *,uint8_t,uint8_t);
    float (*vHMC5883L_get_angle)(void);
    void (*vHMC5883L_calculate_direction)(float);
    void (*vHMC5883L_direction_function)(void);
}HMC5883L_TypeDef;

extern HMC5883L_TypeDef Hmc5883l_Data;
extern MY_IIC_DATA_TypeDef HMC_IIC_DATA;

void vHMC5883L_init(void);
float vHMC5883L_get_angle(void);
uint8_t ucHMC5883L_read(MY_IIC_DATA_TypeDef *hmc,uint8_t register_addr);
uint8_t ucHMC5883L_write(MY_IIC_DATA_TypeDef *hmc,uint8_t register_addr,uint8_t data);
void vHMC5883L_calculate_direction(float angle_num);
void vHMC5883L_direction_function(void);
#endif

