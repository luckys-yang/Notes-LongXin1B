#ifndef _HMC5883L_H
#define _HMC5883L_H
#include "all.h"
#include "my_iic.h"
//��������
#define HMC5883L_SDA 29 //�����߹ܽ�
#define HMC5883L_SCL 28 //ʱ���߹ܽ�
//д������ַ
#define HMC5883L_WRITE_ADDR 0x3C
//��������ַ
#define HMC5883L_READ_ADDR 0x3D
//�Ĵ�����ַ
#define HMC5883L_REGISTER_A 0x00    //A
#define HMC5883L_REGISTER_B 0x01    //B
#define HMC5883L_REGISTER_MODE 0x02    //ģʽ

typedef struct
{
    bool Hmc5883l_Over_Flag;    //���б�־λ
    float Angle_value;  //�Ƕ�ֵ
    bool Hmc588l_WN_Flag;    //����
    bool Hmc588l_WS_Flag;    //����
    bool Hmc588l_ES_Flag;    //����
    bool Hmc588l_EN_Flag;    //����
    bool Hmc588l_W_Flag;    //��
    bool Hmc588l_E_Flag;    //��
    bool Hmc588l_S_Flag;    //��
    bool Hmc588l_N_Flag;    //��
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

