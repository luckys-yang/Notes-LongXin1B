/*
 * hmc5883l.c
 *
 * created: 2023-03-26
 *  author: Yang
 *  module: 电子罗盘(磁力计) 硬件连接：P1插板子左侧P3
 */
#include "hmc5883l.h"

int16_t HMC_X,HMC_Y,HMC_Z;

//初始化管脚
MY_IIC_DATA_TypeDef HMC_IIC_DATA =
{
    .SCL_Pin = HMC5883L_SCL,
    .SDA_Pin = HMC5883L_SDA
};

//初始化结构体
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
功能：初始化
*/
void vHMC5883L_init(void)
{
    vMY_IIC_init(&HMC_IIC_DATA);    //i2c引脚初始化
    Hmc5883l_Data.ucHMC5883L_write(&HMC_IIC_DATA,HMC5883L_REGISTER_A,0x58); //输出速率75hz 平均采样4次
    Hmc5883l_Data.ucHMC5883L_write(&HMC_IIC_DATA,HMC5883L_REGISTER_B,0x20); //默认1090
    Hmc5883l_Data.ucHMC5883L_write(&HMC_IIC_DATA,HMC5883L_REGISTER_MODE,0x00); //连续测量模式
}
/*
功能：读取数据计算角度
返回值：角度
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
    HMC_X = read_buff[0]<<8 | read_buff[1];//组合数据
    HMC_Z = read_buff[2]<<8 | read_buff[3];//组合数据
    HMC_Y = read_buff[4]<<8 | read_buff[5];//组合数据
    Hmc5883l_Data.Angle_value = atan2((double)HMC_Y,(double)HMC_X) * (180 / 3.14159265) + 180; // 计算角度

    return Hmc5883l_Data.Angle_value;
}

/*
功能：通过角度计算方向
参数：角度
*/
void vHMC5883L_calculate_direction(float angle_num)
{
    if(angle_num >= 22 && angle_num <= 67)  //东北
    {
        Hmc5883l_Data.Hmc588l_EN_Flag = 1;
    }
    else if(angle_num >= 68 && angle_num <= 111)    //东
    {
        Hmc5883l_Data.Hmc588l_E_Flag = 1;
    }
    else if(angle_num >= 112 && angle_num <= 157)   //东南
    {
        Hmc5883l_Data.Hmc588l_ES_Flag = 1;
    }
    else if(angle_num >= 158 && angle_num <= 201)   //南
    {
        Hmc5883l_Data.Hmc588l_S_Flag = 1;
    }
    else if(angle_num >= 202 && angle_num <= 247)   //西南
    {
        Hmc5883l_Data.Hmc588l_WS_Flag = 1;
    }
    else if(angle_num >= 248 && angle_num <= 291)   //西
    {
        Hmc5883l_Data.Hmc588l_W_Flag = 1;
    }
    else if(angle_num >= 292 && angle_num <= 337)   //西北
    {
        Hmc5883l_Data.Hmc588l_WN_Flag = 1;
    }
    else    //北
    {
        Hmc5883l_Data.Hmc588l_N_Flag = 1;
    }
}

/*
功能：根据方向执行功能
*/
void vHMC5883L_direction_function(void)
{
    char arr1[50] = {0};
    char arr2[50] = {0};
    if(Hmc5883l_Data.Hmc5883l_Over_Flag)
    {
        Hmc5883l_Data.vHMC5883L_get_angle();
        Hmc5883l_Data.vHMC5883L_calculate_direction(Hmc5883l_Data.Angle_value);

        if(Hmc5883l_Data.Hmc588l_EN_Flag)  //东北
        {
            snprintf(arr1,sizeof(arr1),"东北   ");
            Hmc5883l_Data.Hmc588l_EN_Flag = 0;
        }
        if(Hmc5883l_Data.Hmc588l_E_Flag)    //东
        {
            snprintf(arr1,sizeof(arr1),"东    ");
            Hmc5883l_Data.Hmc588l_E_Flag = 0;
        }
        if(Hmc5883l_Data.Hmc588l_ES_Flag)   //东南
        {
            snprintf(arr1,sizeof(arr1),"东南    ");
            Hmc5883l_Data.Hmc588l_ES_Flag = 0;
        }
        if(Hmc5883l_Data.Hmc588l_S_Flag)    //南
        {
            snprintf(arr1,sizeof(arr1),"南    ");
            Hmc5883l_Data.Hmc588l_S_Flag = 0;
        }
        if(Hmc5883l_Data.Hmc588l_WS_Flag)   //西南
        {
            snprintf(arr1,sizeof(arr1),"西南    ");
            Hmc5883l_Data.Hmc588l_WS_Flag = 0;
        }
        if(Hmc5883l_Data.Hmc588l_W_Flag)    //西
        {
            snprintf(arr1,sizeof(arr1),"西    ");
            Hmc5883l_Data.Hmc588l_W_Flag = 0;
        }
        if(Hmc5883l_Data.Hmc588l_WN_Flag)   //西北
        {
            snprintf(arr1,sizeof(arr1),"西北    ");
            Hmc5883l_Data.Hmc588l_WN_Flag = 0;
        }
        if(Hmc5883l_Data.Hmc588l_N_Flag)    //北
        {
            snprintf(arr1,sizeof(arr1),"北    ");
            Hmc5883l_Data.Hmc588l_N_Flag = 0;
        }
        snprintf(arr2,sizeof(arr2),"角度:%.0f°方向:%s",Hmc5883l_Data.Angle_value,arr1);
        GuiRowText(0,0+300,400, FONT_LEFT,(uint8_t*)arr2);
        Hmc5883l_Data.Hmc5883l_Over_Flag = 0;
    }
}


/*
功能：HMC5883L读取寄存器的数据
参数1：结构体指针
参数2：寄存器地址
*/
uint8_t ucHMC5883L_read(MY_IIC_DATA_TypeDef *hmc,uint8_t register_addr)
{
    static uint8_t read_temp = 0;

    vMY_IIC_start(hmc); //开始信号
    vMY_IIC_send_byte(hmc,HMC5883L_WRITE_ADDR); //写操作
    ucMY_IIC_wait_ack(hmc); //等待应答
    vMY_IIC_send_byte(hmc,register_addr); //发送寄存器地址
    ucMY_IIC_wait_ack(hmc); //等待应答

    vMY_IIC_start(hmc); //开始信号
    vMY_IIC_send_byte(hmc,HMC5883L_READ_ADDR); //读操作
    ucMY_IIC_wait_ack(hmc); //等待应答
    read_temp = ucMY_IIC_read_byte(hmc);    //读取一个字节
    vMY_IIC_nack(hmc);  //发送NACK
    vMY_IIC_stop(hmc);  //停止信号

    return read_temp;
}
/*
功能：HMC5883L把数据写入寄存器
参数1：结构体指针
参数2：寄存器地址
参数3：要写入的数据
返回值：1---写入失败 0---写入成功
*/
uint8_t ucHMC5883L_write(MY_IIC_DATA_TypeDef *hmc,uint8_t register_addr,uint8_t data)
{
    vMY_IIC_start(hmc); //开始信号
    vMY_IIC_send_byte(hmc,HMC5883L_WRITE_ADDR); //写操作
    if(ucMY_IIC_wait_ack(hmc))  //等待ACK
    {
        vMY_IIC_stop(hmc);  //停止信号
        return 1;
    }
    vMY_IIC_send_byte(hmc,register_addr); //发送寄存器地址
    ucMY_IIC_wait_ack(hmc);
    vMY_IIC_send_byte(hmc,data); //发送数据
    if(ucMY_IIC_wait_ack(hmc))  //等待ACK
    {
        vMY_IIC_stop(hmc);  //停止信号
        return 1;
    }
    vMY_IIC_stop(hmc);  //停止信号

    return 0;
}
