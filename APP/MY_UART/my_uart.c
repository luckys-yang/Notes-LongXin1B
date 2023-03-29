/*
 * my_uart.c
 *
 * created: 2023-03-28
 *  author: Yang
 *  module: 串口通信
 */
#include "my_uart.h"


//初始化结构体
MY_UART_TypeDef My_uart_Data =
{
    .UART5_Over_Flag = 0,
    .Uart5_rx_buff = {0},
    .Uart5_rx_len = 0,
    .vMY_UART5_init = &vMY_UART5_init,
    .vMY_UART5_receive_data_function = &vMY_UART5_receive_data_function,
    .vMY_UART5_run_function = &vMY_UART5_run_function
};

/*
功能：串口5初始化
*/
void vMY_UART5_init(void)
{
    uint32_t BaudRate = 115200; //波特率
    ls1x_uart_init(devUART5,(void *)BaudRate); //初始化串口
    ls1x_uart_open(devUART5,NULL); //打开串口
}

/*
功能：接收数据
*/
void vMY_UART5_receive_data_function(void)
{
    if(My_uart_Data.UART5_Over_Flag)
    {
        My_uart_Data.UART5_Over_Flag = 0;
        My_uart_Data.Uart5_rx_len = ls1x_uart_read(devUART5,My_uart_Data.Uart5_rx_buff,UART5_RX_MAX_LEN,NULL);
        if(My_uart_Data.Uart5_rx_len > 0)
        {
            ls1x_uart_write(devUART5,My_uart_Data.Uart5_rx_buff,My_uart_Data.Uart5_rx_len,NULL);  //发送数据
            //My_uart_Data.Uart5_rx_len = 0;
            My_uart_Data.vMY_UART5_run_function();
            memset(My_uart_Data.Uart5_rx_buff,0,sizeof(My_uart_Data.Uart5_rx_buff));    //清空
        }
    }
}

/*
功能：根据串口数据执行
*/
void vMY_UART5_run_function(void)
{
    if(strncmp(My_uart_Data.Uart5_rx_buff,"led_on",6) == 0) //比较前n个字节
    {
        Led_Data.vLED_control(Led_Data.Red_Led,SET);// 开启LED
    }
    if(strncmp(My_uart_Data.Uart5_rx_buff,"led_off",7) == 0) //比较前n个字节
    {
        Led_Data.vLED_control(Led_Data.Red_Led,RESET);// 开启LED
    }

}
