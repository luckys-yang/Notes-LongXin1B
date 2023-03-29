/*
 * lm35.c
 *
 * created: 2023-03-25
 *  author: Yang
 *  module: 温度传感器
 */

#include "lm35.h"

LM35_TypeDef Lm35_Data =
{
    .Lm35_temp = 0.0,
    .vLM35_init = &vLM35_init,
    .fLM35_get_temperature = &fLM35_get_temperature
};

//初始化
void vLM35_init(void)
{
    ls1x_i2c_initialize(busI2C0);   //初始化I2C0
    ls1x_ads1015_ioctl(busI2C0,IOCTL_ADS1015_DISP_CONFIG_REG,NULL); //初始化ADC
}

/*
功能：获取当前温度
返回值：当前温度
*/
float fLM35_get_temperature(void)
{
    uint16_t adc2 = get_ads1015_adc(busI2C0, ADS1015_REG_CONFIG_MUX_SINGLE_2); //获取ADC
    float temp = 4.096*2*adc2/4096;//采集电压的转换公式
    temp = temp*100;
    Lm35_Data.Lm35_temp = temp;

    return temp;
}


