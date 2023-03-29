/*
 * my_adc.c
 *
 * created: 2023-03-28
 *  author: Yang
 *  module: ADC (��ʼ������LM35��ʼ�������ﲻ��Ҫ�ٳ�ʼ��) �Ῠ�����ͬʱ��
 */
#include "my_adc.h"

//��ʼ���ṹ��
MY_ADC_TypeDef myAdcData =
{
    .Adc_Over_Flag = 0,
    .Adc1_value = 0.0,
    .Adc2_value = 0.0,
    .Adc3_value = 0.0,
    .Adc4_value = 0.0,
    .vMY_ADC_get_value = &vMY_ADC_get_value
};


/*
���ܣ���ȡADCֵ
*/
void vMY_ADC_get_value(void)
{
    uint16_t adc1,adc2,adc3,adc4;

    myAdcData.Adc_Over_Flag = 0;
    adc1 = get_ads1015_adc(busI2C0, ADS1015_REG_CONFIG_MUX_SINGLE_0);   //AIN0
    adc2 = get_ads1015_adc(busI2C0, ADS1015_REG_CONFIG_MUX_SINGLE_1);   //AIN1
    adc3 = get_ads1015_adc(busI2C0, ADS1015_REG_CONFIG_MUX_SINGLE_2);   //AIN2
    adc4 = get_ads1015_adc(busI2C0, ADS1015_REG_CONFIG_MUX_SINGLE_3);   //AIN3
    myAdcData.Adc1_value = 4.096*2*adc1/4096;//�ɼ���ѹ��ת����ʽ
    myAdcData.Adc2_value = 4.096*2*adc2/4096;//�ɼ���ѹ��ת����ʽ
    myAdcData.Adc3_value = 4.096*2*adc3/4096;//�ɼ���ѹ��ת����ʽ
    myAdcData.Adc4_value = 4.096*2*adc4/4096;//�ɼ���ѹ��ת����ʽ
}

