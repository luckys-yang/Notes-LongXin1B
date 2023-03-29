/*
 * bh1750.c
 *
 * created: 2023-03-26
 *  author: Yang
 *  module: ��ȴ����� ---I2Cͨ�� ----��ӦоƬ�ڰ������Ͻ�U5
 */

#include "bh1750.h"

//��ʼ���ṹ��
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
���ܣ���ʼ��
*/
void BH1750_init(void)
{
    Bh1750_Data.vBH1750_start();
}

/*
���ܣ������豸��ַ
*/
void vBH1750_Cmd_Write(uint8_t cmd)
{
    uint8_t data[2]= {0};
    data[0]=cmd;

    ls1x_i2c_send_start(busI2C0,BH1750_ADDR);//��ʼ�ź�
    ls1x_i2c_send_addr(busI2C0,BH1750_ADDR,0);	//�����豸��ַ+д�ź�
    ls1x_i2c_write_bytes(busI2C0, data, 1);	//�ڲ��Ĵ�����ַ
    ls1x_i2c_send_stop(busI2C0,BH1750_ADDR);	//����ֹͣ�ź�
    delay_ms(5);
}

/*
���ܣ�����һ�θ߷ֱ���ģʽ
*/
void vBH1750_start(void)
{
    Bh1750_Data.vBH1750_Cmd_Write(BH1750_ON);   //��
    Bh1750_Data.vBH1750_Cmd_Write(BH1750_RSET); //���
    Bh1750_Data.vBH1750_Cmd_Write(BH1750_CON); //1lx�ֱ��ʣ�����120ms(�����ONE���������ģʽÿ�ζ�ȡ��Ҫ��ִ��vBH1750_start)
}

/*
���ܣ�����������
*/
void vBH1750_read(void)
{
    ls1x_i2c_send_start(busI2C0, BH1750_ADDR);//��ʼ�ź�
    ls1x_i2c_send_addr(busI2C0,BH1750_ADDR,1);//�����豸��ַ+���ź�
    ls1x_i2c_read_bytes(busI2C0,Bh1750_Data.BH1750_Read_Buff, 2);//��ȡ�����ֽ�����
    ls1x_i2c_send_stop(busI2C0,BH1750_ADDR);//����ֹͣ�ź�
}

/*
���ܣ��ϳɹ�������
����ֵ�����յĹ�������
*/
float vBH1750_convert_data(void)
{
    uint16_t temp = 0;  //16λ

    temp = Bh1750_Data.BH1750_Read_Buff[0];
    temp = (temp<<8)+Bh1750_Data.BH1750_Read_Buff[1];		//�ϳ����ݣ�����������
    Bh1750_Data.Bh1750_value = (float)temp/1.2;

    return Bh1750_Data.Bh1750_value;
}

/*
���ܣ����һ�������Ĳɼ�
*/
void vBH1750_whole_get_data(void)
{
    Bh1750_Data.vBH1750_read(); //������ȡ
    Bh1750_Data.vBH1750_convert_data(); //�ϳ�
}
