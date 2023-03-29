/*
 * resistor.c
 *
 * created: 2023-03-26
 *  author: Yang
 *  module: 加热电阻
 */
 
#include "resistor.h"

//结构体初始化
RESISTOR_TypeDef Resistor_Data =
{
    .vRESISTOR_init = &vRESISTOR_init,
    .vRESISTOR_control = &vRESISTOR_control
};
/*
功能：初始化
*/
void vRESISTOR_init(void)
{
    gpio_enable(RESISTOR_PIN,DIR_OUT);  //输出模式
    Resistor_Data.vRESISTOR_control(RESET); //默认关闭状态
}

/*
功能：控制加热电阻开关
参数：SET--开 RESET--关
*/
void vRESISTOR_control(uint8_t swch)
{
    if(SET == swch)
    {
        gpio_write(RESISTOR_PIN,SET); //开
    }
    else
    {
        gpio_write(RESISTOR_PIN,RESET); //关
    }
}
