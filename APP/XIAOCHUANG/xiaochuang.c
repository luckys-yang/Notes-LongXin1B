/*
 * xiaochuang.c
 *
 * created: 2023-03-24
 *  author: Yang
 *  module: С������
 */
#include "xiaochuang.h"

uint8_t ucXiaoChuang_rouse_arr[5] = {0xFA, 0xFA, 0xFA, 0xFA, 0xA1};	//С�����Ѵ�

//��ʼ���ṹ������
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

//����4��ʼ��
void vUART4_init(void)
{
    unsigned int BaudRate = 115200;

    ls1x_uart_init(devUART4,(void *)BaudRate); //��ʼ������
    ls1x_uart_open(devUART4,NULL); //�򿪴���
}

/*
���ܣ�����4���պ���
С��������ش������ʽ��55 02 01 00(֡ͷ �������� ״̬��־ ����λ ----֡ͷ�̶��ĺ���3λ���Զ���)
uart6_flagִ��˳��0x00-->0x01-->0x02-->0x03-->0x00...�Դ�ѭ��
*/
void vUART4_rx_data_function(void)
{
    static uint8_t timing_flag = 0;  //ʱ��
    static uint8_t rx_count = 0;

    rx_count = ls1x_uart_read(devUART4,XiaoChuangData.UART4_RX_BUFF,UART4_RX_MAX_LEN,NULL);  //��������,����ֵ�Ƕ�ȡ���ֽ���

    if(rx_count > 0)
    {
        if (timing_flag == 0x00)
        {
            if (XiaoChuangData.UART4_RX_BUFF[0] == 0x55)				// �Զ�������֡ͷ
            {
                timing_flag = 0x01;
                XiaoChuangData.Rx_Data[0] = XiaoChuangData.UART4_RX_BUFF[0];	// ֡ͷ
                XiaoChuangData.Rx_Data[1] = 0x00;
                XiaoChuangData.Rx_Data[2] = 0x00;
                XiaoChuangData.Rx_Data[3] = 0x00;
            }
        }
        else if (timing_flag == 0x01)
        {
            timing_flag = 0x02;
            XiaoChuangData.Rx_Data[1] = XiaoChuangData.UART4_RX_BUFF[0];		// ��������
        }
        else if(timing_flag == 0x02)
        {
            timing_flag = 0x03;
            XiaoChuangData.Rx_Data[2] = XiaoChuangData.UART4_RX_BUFF[0];		// ״̬��־
        }
        else if(timing_flag == 0x03)
        {
            timing_flag = 0x00;
            XiaoChuangData.Rx_Data[3] = XiaoChuangData.UART4_RX_BUFF[0];		// ����λ
            XiaoChuangData.UART4_Rx_Over_Flag = 1; //�������
            memset(XiaoChuangData.UART4_RX_BUFF,0,sizeof(XiaoChuangData.UART4_RX_BUFF));  //��0
        }
        else    //����ִ�е���
        {
            timing_flag = 0x00;
            XiaoChuangData.UART4_Rx_Over_Flag = 0; 
            XiaoChuangData.Rx_Data[0] = 0x00;
            memset(XiaoChuangData.UART4_RX_BUFF,0,sizeof(XiaoChuangData.UART4_RX_BUFF));  //��0
        }
    }
}

/*
��ǰ���ݣ�
����һ����::�õģ�����һ����:55020100
���������::�õģ����������:55020200
����������::�õģ�����������:55020300
����������::�õģ�����������:55020400
����������::�õģ�����������:55020500
����������::�õģ�����������:55020600
����������::�õģ�����������:55020700
���������::�õģ����������:55020800
���������::�õģ����������:55020900
����ʮ����::�õģ�����ʮ����:55020A00
��������::ʶ��ɹ�����������:55020B00
��������::ʶ��ɹ�����������:55020C00
��Խ����::ʶ��ɹ�����Խ����:55020D00
���ʸ߷�::ʶ��ɹ������ʸ߷�:55020E00
*/

/*
���ܣ�С���ش�����
��Ҫ���ж�asrWordlist.txt�������ش�
ͨ������ֵͬ��־λXiaoChuang_return_state�����зֱ治ͬ�ش�����
�ش���ʽ��5502XX00
*/
void vXIAOCHUANG_order_parse(void)
{
    if (XiaoChuangData.UART4_Rx_Over_Flag)
    {
        XiaoChuangData.UART4_Rx_Over_Flag = 0;

        if(0x02 == XiaoChuangData.Rx_Data[1]) //��������
        {
            switch(XiaoChuangData.Rx_Data[2])    //״̬��־
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
        else if(0x03 == XiaoChuangData.Rx_Data[2]) //�������͡���Ҫ�ж�serialTTS.txt��ġ�
        {
            ;
        }
    }
    memset(XiaoChuangData.Rx_Data,0,sizeof(XiaoChuangData.Rx_Data));  //��0
}

/*
���ܣ�����С���ش�����״̬XiaoChuang_return_stateִ�ж�Ӧ����
*/
void vXIAOCHUANG_state_function(void)
{
    switch(XiaoChuangData.XiaoChuang_return_state)
    {
        case 1:
            {
                auto_task1();   //����1
                break;
            }
        case 2:
            {
                break;
            }
        case 3:
            {
                auto_task3();   //����3
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
                snprintf(Lcd_xiaochuang_identify_display_str,sizeof(Lcd_xiaochuang_identify_display_str),"��������");
                //Lcd_Data.Lcd_Display4_Flag = 1; //LCDˢ��
                GuiRowText(0,0+300,400, FONT_LEFT,(uint8_t*)Lcd_xiaochuang_identify_display_str);
                break;
            }
        case 12:
            {
                memset(Lcd_xiaochuang_identify_display_str,0,sizeof(Lcd_xiaochuang_identify_display_str));
                snprintf(Lcd_xiaochuang_identify_display_str,sizeof(Lcd_xiaochuang_identify_display_str),"��������");
                //Lcd_Data.Lcd_Display4_Flag = 1; //LCDˢ��
                GuiRowText(0,0+300,400, FONT_LEFT,(uint8_t*)Lcd_xiaochuang_identify_display_str);
                break;
            }
        case 13:
            {
                memset(Lcd_xiaochuang_identify_display_str,0,sizeof(Lcd_xiaochuang_identify_display_str));
                snprintf(Lcd_xiaochuang_identify_display_str,sizeof(Lcd_xiaochuang_identify_display_str),"��Խ����");
                //Lcd_Data.Lcd_Display4_Flag = 1; //LCDˢ��
                GuiRowText(0,0+300,400, FONT_LEFT,(uint8_t*)Lcd_xiaochuang_identify_display_str);
                break;
            }
        case 14:
            {
                memset(Lcd_xiaochuang_identify_display_str,0,sizeof(Lcd_xiaochuang_identify_display_str));
                snprintf(Lcd_xiaochuang_identify_display_str,sizeof(Lcd_xiaochuang_identify_display_str),"���ʸ߷�");
                //Lcd_Data.Lcd_Display4_Flag = 1; //LCDˢ��
                GuiRowText(0,0+300,400, FONT_LEFT,(uint8_t*)Lcd_xiaochuang_identify_display_str);
                break;
            }
        default:
            break;
    }
    XiaoChuangData.XiaoChuang_return_state = 0;    //���״̬
}

/*
��ǰ����
01::��ף�й�����������100����:55030100
02::ϲӭ��ʮ����Զ�����ߡ��ܽ�������:55030200
*/
/*
����ָ������
�������������
*/
void vXIAOCHUANG_play_specify_content(int id)
{
    int ID_number = id;
    ls1x_uart_write(devUART4,&ID_number,1,NULL);    //����һ���ֽ�
}

/*
���ܣ�����С������
*/
void vXIAOCHUANG_send_rouse(void)
{
    ls1x_uart_write(devUART4,&ucXiaoChuang_rouse_arr,sizeof(ucXiaoChuang_rouse_arr),NULL);    //���ͻ���
}



