/*
 * xiaochuang.c
 *
 * created: 2023-03-24
 *  author: Yang
 *  module: 小创语音
 */
#include "xiaochuang.h"

uint8_t ucXiaoChuang_rouse_arr[5] = {0xFA, 0xFA, 0xFA, 0xFA, 0xA1};	//小创唤醒词

//初始化结构体数据
XIAOCHUANG_TypeDef XiaoChuangData =
{
    .UART4_Rx_Over_Flag = 0,
    .Rx_Data = {0},
    .UART4_RX_BUFF = {0},
    .XiaoChuang_return_state = 0,
    .vUART4_init = &vUART4_init,
    .vXIAOCHUANG_order_parse = &vXIAOCHUANG_order_parse,
    .vXIAOCHUANG_state_function = &vXIAOCHUANG_state_function,
    .vXIAOCHUANG_play_specify_content = &vXIAOCHUANG_play_specify_content,
    .vXIAOCHUANG_send_rouse = &vXIAOCHUANG_send_rouse,
    .vUART4_rx_data_function = &vUART4_rx_data_function
};

//串口4初始化
void vUART4_init(void)
{
    unsigned int BaudRate = 115200;

    ls1x_uart_init(devUART4,(void *)BaudRate); //初始化串口
    ls1x_uart_open(devUART4,NULL); //打开串口
}

/*
功能：串口4接收函数
小创播报后回传命令格式：55 02 01 00(帧头 数据类型 状态标志 数据位 ----帧头固定的后面3位可自定义)
uart6_flag执行顺序：0x00-->0x01-->0x02-->0x03-->0x00...以此循环
*/
void vUART4_rx_data_function(void)
{
    static uint8_t timing_flag = 0;  //时序
    static uint8_t rx_count = 0;

    rx_count = ls1x_uart_read(devUART4,XiaoChuangData.UART4_RX_BUFF,UART4_RX_MAX_LEN,NULL);  //接收数据,返回值是读取的字节数

    if(rx_count > 0)
    {
        if (timing_flag == 0x00)
        {
            if (XiaoChuangData.UART4_RX_BUFF[0] == 0x55)				// 自定义数据帧头
            {
                timing_flag = 0x01;
                XiaoChuangData.Rx_Data[0] = XiaoChuangData.UART4_RX_BUFF[0];	// 帧头
                XiaoChuangData.Rx_Data[1] = 0x00;
                XiaoChuangData.Rx_Data[2] = 0x00;
                XiaoChuangData.Rx_Data[3] = 0x00;
            }
        }
        else if (timing_flag == 0x01)
        {
            timing_flag = 0x02;
            XiaoChuangData.Rx_Data[1] = XiaoChuangData.UART4_RX_BUFF[0];		// 数据类型
        }
        else if(timing_flag == 0x02)
        {
            timing_flag = 0x03;
            XiaoChuangData.Rx_Data[2] = XiaoChuangData.UART4_RX_BUFF[0];		// 状态标志
        }
        else if(timing_flag == 0x03)
        {
            timing_flag = 0x00;
            XiaoChuangData.Rx_Data[3] = XiaoChuangData.UART4_RX_BUFF[0];		// 数据位
            XiaoChuangData.UART4_Rx_Over_Flag = 1; //接收完成
            memset(XiaoChuangData.UART4_RX_BUFF,0,sizeof(XiaoChuangData.UART4_RX_BUFF));  //清0
        }
        else    //不会执行到这
        {
            timing_flag = 0x00;
            XiaoChuangData.UART4_Rx_Over_Flag = 0; 
            XiaoChuangData.Rx_Data[0] = 0x00;
            memset(XiaoChuangData.UART4_RX_BUFF,0,sizeof(XiaoChuangData.UART4_RX_BUFF));  //清0
        }
    }
}

/*
当前数据：
任务一启动::好的，任务一启动:55020100
任务二启动::好的，任务二启动:55020200
任务三启动::好的，任务三启动:55020300
任务四启动::好的，任务四启动:55020400
任务五启动::好的，任务五启动:55020500
任务六启动::好的，任务六启动:55020600
任务七启动::好的，任务七启动:55020700
任务八启动::好的，任务八启动:55020800
任务九启动::好的，任务九启动:55020900
任务十启动::好的，任务十启动:55020A00
砺练能力::识别成功，砺练能力:55020B00
交流技艺::识别成功，交流技艺:55020C00
超越自我::识别成功，超越自我:55020D00
勇攀高峰::识别成功，勇攀高峰:55020E00
*/

/*
功能：小创回传解析
主要是判断asrWordlist.txt里的命令回传
通过赋不同值标志位XiaoChuang_return_state来进行分辨不同回传命令
回传格式：5502XX00
*/
void vXIAOCHUANG_order_parse(void)
{
    if (XiaoChuangData.UART4_Rx_Over_Flag)
    {
        XiaoChuangData.UART4_Rx_Over_Flag = 0;

        if(0x02 == XiaoChuangData.Rx_Data[1]) //数据类型
        {
            switch(XiaoChuangData.Rx_Data[2])    //状态标志
            {
                case 0x01:
                    {
                        XiaoChuangData.XiaoChuang_return_state = 1;
                        break;
                    }
                case 0x02:
                    {
                        XiaoChuangData.XiaoChuang_return_state = 2;
                        break;
                    }
                case 0x03:
                    {
                        XiaoChuangData.XiaoChuang_return_state = 3;
                        break;
                    }
                case 0x04:
                    {
                        XiaoChuangData.XiaoChuang_return_state = 4;
                        break;
                    }
                case 0x05:
                    {
                        XiaoChuangData.XiaoChuang_return_state = 5;
                        break;
                    }
                case 0x06:
                    {
                        XiaoChuangData.XiaoChuang_return_state = 6;
                        break;
                    }
                case 0x07:
                    {
                        XiaoChuangData.XiaoChuang_return_state = 7;
                        break;
                    }
                case 0x08:
                    {
                        XiaoChuangData.XiaoChuang_return_state = 8;
                        break;
                    }
                case 0x09:
                    {
                        XiaoChuangData.XiaoChuang_return_state = 9;
                        break;
                    }
                case 0x0A:
                    {
                        XiaoChuangData.XiaoChuang_return_state = 10;
                        break;
                    }
                case 0x0B:
                    {
                        XiaoChuangData.XiaoChuang_return_state = 11;
                        break;
                    }
                case 0x0C:
                    {
                        XiaoChuangData.XiaoChuang_return_state = 12;
                        break;
                    }
                case 0x0D:
                    {
                        XiaoChuangData.XiaoChuang_return_state = 13;
                        break;
                    }
                case 0x0E:
                    {
                        XiaoChuangData.XiaoChuang_return_state = 14;
                        break;
                    }
                default:
                    break;
            }
        }
        else if(0x03 == XiaoChuangData.Rx_Data[2]) //数据类型【主要判断serialTTS.txt里的】
        {
            ;
        }
    }
    memset(XiaoChuangData.Rx_Data,0,sizeof(XiaoChuangData.Rx_Data));  //清0
}

/*
功能：根据小创回传命令状态XiaoChuang_return_state执行对应功能
*/
void vXIAOCHUANG_state_function(void)
{
    switch(XiaoChuangData.XiaoChuang_return_state)
    {
        case 1:
            {
                auto_task1();   //任务1
                break;
            }
        case 2:
            {
                break;
            }
        case 3:
            {
                auto_task3();   //任务3
                break;
            }
        case 4:
            {
                auto_task4();
                break;
            }
        case 5:
            {
                break;
            }
        case 6:
            {
                break;
            }
        case 7:
            {
                break;
            }
        case 8:
            {
                break;
            }
        case 9:
            {
                break;
            }
        case 10:
            {
                break;
            }
        case 11:
            {
                memset(Lcd_xiaochuang_identify_display_str,0,sizeof(Lcd_xiaochuang_identify_display_str));
                snprintf(Lcd_xiaochuang_identify_display_str,sizeof(Lcd_xiaochuang_identify_display_str),"砺练能力");
                //Lcd_Data.Lcd_Display4_Flag = 1; //LCD刷新
                GuiRowText(0,0+300,400, FONT_LEFT,(uint8_t*)Lcd_xiaochuang_identify_display_str);
                break;
            }
        case 12:
            {
                memset(Lcd_xiaochuang_identify_display_str,0,sizeof(Lcd_xiaochuang_identify_display_str));
                snprintf(Lcd_xiaochuang_identify_display_str,sizeof(Lcd_xiaochuang_identify_display_str),"交流技艺");
                //Lcd_Data.Lcd_Display4_Flag = 1; //LCD刷新
                GuiRowText(0,0+300,400, FONT_LEFT,(uint8_t*)Lcd_xiaochuang_identify_display_str);
                break;
            }
        case 13:
            {
                memset(Lcd_xiaochuang_identify_display_str,0,sizeof(Lcd_xiaochuang_identify_display_str));
                snprintf(Lcd_xiaochuang_identify_display_str,sizeof(Lcd_xiaochuang_identify_display_str),"超越自我");
                //Lcd_Data.Lcd_Display4_Flag = 1; //LCD刷新
                GuiRowText(0,0+300,400, FONT_LEFT,(uint8_t*)Lcd_xiaochuang_identify_display_str);
                break;
            }
        case 14:
            {
                memset(Lcd_xiaochuang_identify_display_str,0,sizeof(Lcd_xiaochuang_identify_display_str));
                snprintf(Lcd_xiaochuang_identify_display_str,sizeof(Lcd_xiaochuang_identify_display_str),"勇攀高峰");
                //Lcd_Data.Lcd_Display4_Flag = 1; //LCD刷新
                GuiRowText(0,0+300,400, FONT_LEFT,(uint8_t*)Lcd_xiaochuang_identify_display_str);
                break;
            }
        default:
            break;
    }
    XiaoChuangData.XiaoChuang_return_state = 0;    //清除状态
}

/*
当前数据
01::庆祝中国共产党成立100周年:55030100
02::喜迎二十大、永远跟党走、奋进新征程:55030200
*/
/*
播报指定词条
参数：词条编号
*/
void vXIAOCHUANG_play_specify_content(int id)
{
    int ID_number = id;
    ls1x_uart_write(devUART4,&ID_number,1,NULL);    //发送一个字节
}

/*
功能：发送小创唤醒
*/
void vXIAOCHUANG_send_rouse(void)
{
    ls1x_uart_write(devUART4,&ucXiaoChuang_rouse_arr,sizeof(ucXiaoChuang_rouse_arr),NULL);    //发送唤醒
}



