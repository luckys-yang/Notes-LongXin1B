/*
 * hmc5883l.c
 *
 * created: 2023-03-26
 *  author: Yang
 *  module: ��������(������) Ӳ�����ӣ�P1��������P3
 */
#include "hmc5883l.h"

int16_t HMC_X,HMC_Y,HMC_Z;

//��ʼ���ܽ�
MY_IIC_DATA_TypeDef HMC_IIC_DATA =
{
    .SCL_Pin = HMC5883L_SCL,
    .SDA_Pin = HMC5883L_SDA
};

//��ʼ���ṹ��
HMC5883L_TypeDef Hmc5883l_Data =
{
    .Hmc5883l_Over_Flag = 0,
    .Angle_value = 0.0,
    .Hmc588l_WN_Flag = 0,
    .Hmc588l_WS_Flag = 0,
    .Hmc588l_ES_Flag = 0,
    .Hmc588l_EN_Flag = 0,
    .Hmc588l_W_Flag = 0,
    .Hmc588l_E_Flag = 0,
    .Hmc588l_S_Flag = 0,
    .Hmc588l_N_Flag = 0,
    .vHMC5883L_init = &vHMC5883L_init,
    .ucHMC5883L_read = &ucHMC5883L_read,
    .ucHMC5883L_write = &ucHMC5883L_write,
    .vHMC5883L_get_angle = &vHMC5883L_get_angle,
    .vHMC5883L_calculate_direction = &vHMC5883L_calculate_direction,
    .vHMC5883L_direction_function = &vHMC5883L_direction_function
};

/*
���ܣ���ʼ��
*/
void vHMC5883L_init(void)
{
    vMY_IIC_init(&HMC_IIC_DATA);    //i2c���ų�ʼ��
    Hmc5883l_Data.ucHMC5883L_write(&HMC_IIC_DATA,HMC5883L_REGISTER_A,0x58); //�������75hz ƽ������4��
    Hmc5883l_Data.ucHMC5883L_write(&HMC_IIC_DATA,HMC5883L_REGISTER_B,0x20); //Ĭ��1090
    Hmc5883l_Data.ucHMC5883L_write(&HMC_IIC_DATA,HMC5883L_REGISTER_MODE,0x00); //��������ģʽ
}
/*
���ܣ���ȡ���ݼ���Ƕ�
����ֵ���Ƕ�
*/
float vHMC5883L_get_angle(void)
{
    uint8_t i;
    int16_t read_buff[6];

    for(i=0; i<6; i++)
    {
        //x--03 04 z--05 06 y--07 08
        read_buff[i] = ucHMC5883L_read(&HMC_IIC_DATA,i+3);
    }
    HMC_X = read_buff[0]<<8 | read_buff[1];//�������
    HMC_Z = read_buff[2]<<8 | read_buff[3];//�������
    HMC_Y = read_buff[4]<<8 | read_buff[5];//�������
    Hmc5883l_Data.Angle_value = atan2((double)HMC_Y,(double)HMC_X) * (180 / 3.14159265) + 180; // ����Ƕ�

    return Hmc5883l_Data.Angle_value;
}

/*
���ܣ�ͨ���Ƕȼ��㷽��
�������Ƕ�
*/
void vHMC5883L_calculate_direction(float angle_num)
{
    if(angle_num >= 22 && angle_num <= 67)  //����
    {
        Hmc5883l_Data.Hmc588l_EN_Flag = 1;
    }
    else if(angle_num >= 68 && angle_num <= 111)    //��
    {
        Hmc5883l_Data.Hmc588l_E_Flag = 1;
    }
    else if(angle_num >= 112 && angle_num <= 157)   //����
    {
        Hmc5883l_Data.Hmc588l_ES_Flag = 1;
    }
    else if(angle_num >= 158 && angle_num <= 201)   //��
    {
        Hmc5883l_Data.Hmc588l_S_Flag = 1;
    }
    else if(angle_num >= 202 && angle_num <= 247)   //����
    {
        Hmc5883l_Data.Hmc588l_WS_Flag = 1;
    }
    else if(angle_num >= 248 && angle_num <= 291)   //��
    {
        Hmc5883l_Data.Hmc588l_W_Flag = 1;
    }
    else if(angle_num >= 292 && angle_num <= 337)   //����
    {
        Hmc5883l_Data.Hmc588l_WN_Flag = 1;
    }
    else    //��
    {
        Hmc5883l_Data.Hmc588l_N_Flag = 1;
    }
}

/*
���ܣ����ݷ���ִ�й���
*/
void vHMC5883L_direction_function(void)
{
    char arr1[50] = {0};
    char arr2[50] = {0};
    if(Hmc5883l_Data.Hmc5883l_Over_Flag)
    {
        Hmc5883l_Data.vHMC5883L_get_angle();
        Hmc5883l_Data.vHMC5883L_calculate_direction(Hmc5883l_Data.Angle_value);

        if(Hmc5883l_Data.Hmc588l_EN_Flag)  //����
        {
            snprintf(arr1,sizeof(arr1),"����   ");
            Hmc5883l_Data.Hmc588l_EN_Flag = 0;
        }
        if(Hmc5883l_Data.Hmc588l_E_Flag)    //��
        {
            snprintf(arr1,sizeof(arr1),"��    ");
            Hmc5883l_Data.Hmc588l_E_Flag = 0;
        }
        if(Hmc5883l_Data.Hmc588l_ES_Flag)   //����
        {
            snprintf(arr1,sizeof(arr1),"����    ");
            Hmc5883l_Data.Hmc588l_ES_Flag = 0;
        }
        if(Hmc5883l_Data.Hmc588l_S_Flag)    //��
        {
            snprintf(arr1,sizeof(arr1),"��    ");
            Hmc5883l_Data.Hmc588l_S_Flag = 0;
        }
        if(Hmc5883l_Data.Hmc588l_WS_Flag)   //����
        {
            snprintf(arr1,sizeof(arr1),"����    ");
            Hmc5883l_Data.Hmc588l_WS_Flag = 0;
        }
        if(Hmc5883l_Data.Hmc588l_W_Flag)    //��
        {
            snprintf(arr1,sizeof(arr1),"��    ");
            Hmc5883l_Data.Hmc588l_W_Flag = 0;
        }
        if(Hmc5883l_Data.Hmc588l_WN_Flag)   //����
        {
            snprintf(arr1,sizeof(arr1),"����    ");
            Hmc5883l_Data.Hmc588l_WN_Flag = 0;
        }
        if(Hmc5883l_Data.Hmc588l_N_Flag)    //��
        {
            snprintf(arr1,sizeof(arr1),"��    ");
            Hmc5883l_Data.Hmc588l_N_Flag = 0;
        }
        snprintf(arr2,sizeof(arr2),"�Ƕ�:%.0f�㷽��:%s",Hmc5883l_Data.Angle_value,arr1);
        GuiRowText(0,0+300,400, FONT_LEFT,(uint8_t*)arr2);
        Hmc5883l_Data.Hmc5883l_Over_Flag = 0;
    }
}


/*
���ܣ�HMC5883L��ȡ�Ĵ���������
����1���ṹ��ָ��
����2���Ĵ�����ַ
*/
uint8_t ucHMC5883L_read(MY_IIC_DATA_TypeDef *hmc,uint8_t register_addr)
{
    static uint8_t read_temp = 0;

    vMY_IIC_start(hmc); //��ʼ�ź�
    vMY_IIC_send_byte(hmc,HMC5883L_WRITE_ADDR); //д����
    ucMY_IIC_wait_ack(hmc); //�ȴ�Ӧ��
    vMY_IIC_send_byte(hmc,register_addr); //���ͼĴ�����ַ
    ucMY_IIC_wait_ack(hmc); //�ȴ�Ӧ��

    vMY_IIC_start(hmc); //��ʼ�ź�
    vMY_IIC_send_byte(hmc,HMC5883L_READ_ADDR); //������
    ucMY_IIC_wait_ack(hmc); //�ȴ�Ӧ��
    read_temp = ucMY_IIC_read_byte(hmc);    //��ȡһ���ֽ�
    vMY_IIC_nack(hmc);  //����NACK
    vMY_IIC_stop(hmc);  //ֹͣ�ź�

    return read_temp;
}
/*
���ܣ�HMC5883L������д��Ĵ���
����1���ṹ��ָ��
����2���Ĵ�����ַ
����3��Ҫд�������
����ֵ��1---д��ʧ�� 0---д��ɹ�
*/
uint8_t ucHMC5883L_write(MY_IIC_DATA_TypeDef *hmc,uint8_t register_addr,uint8_t data)
{
    vMY_IIC_start(hmc); //��ʼ�ź�
    vMY_IIC_send_byte(hmc,HMC5883L_WRITE_ADDR); //д����
    if(ucMY_IIC_wait_ack(hmc))  //�ȴ�ACK
    {
        vMY_IIC_stop(hmc);  //ֹͣ�ź�
        return 1;
    }
    vMY_IIC_send_byte(hmc,register_addr); //���ͼĴ�����ַ
    ucMY_IIC_wait_ack(hmc);
    vMY_IIC_send_byte(hmc,data); //��������
    if(ucMY_IIC_wait_ack(hmc))  //�ȴ�ACK
    {
        vMY_IIC_stop(hmc);  //ֹͣ�ź�
        return 1;
    }
    vMY_IIC_stop(hmc);  //ֹͣ�ź�

    return 0;
}
