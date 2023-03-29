/*
 * xiaochuang.c
 *
 * created: 2023-03-24
 *  author: Yang
 *  module: С������
 */
#include "xiaochuang.h"


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
    .vXIAOCHUANG_play_specify_content = &vXIAOCHUANG_play_specify_content
};

//����4��ʼ��
void vUART4_init(void)
{
    unsigned int BaudRate = 115200;

    ls1x_uart_init(devUART4,(void *)BaudRate); //��ʼ������
    ls1x_uart_open(devUART4,NULL); //�򿪴���
    ls1x_disable_gpio_interrupt(USART4_GPIO);   //ʧ��GPIO�ж�
    //�˿ںţ������ش������жϺ�������NULL
    ls1x_install_gpio_isr(USART4_GPIO,INT_TRIG_EDGE_UP,vUART4_IRQhandler,NULL); //�жϳ�ʼ��
    ls1x_enable_gpio_interrupt(USART4_GPIO);    //ʹ��GPIO�ж�
}

/*
���ܣ�����4�жϺ���
С��������ش������ʽ��55 02 01 00(֡ͷ �������� ״̬��־ ����λ ----֡ͷ�̶��ĺ���3λ���Զ���)
uart6_flagִ��˳��0x00-->0x01-->0x02-->0x03-->0x00...�Դ�ѭ��
*/
void vUART4_IRQhandler(int IRQn,void* param)
{
    static uint8_t timing_flag = 0;  //ʱ��

    ls1x_uart_read(devUART4,XiaoChuangData.UART4_RX_BUFF,UART4_RX_MAX_LEN,NULL);  //��������,����ֵ�Ƕ�ȡ���ֽ���

    if(0x55 == XiaoChuangData.UART4_RX_BUFF[0])
    {
        timing_flag = 1;

    }
    switch(timing_flag)
    {
        case 1: //֡ͷ
            {
                XiaoChuangData.Rx_Data[0] = XiaoChuangData.UART4_RX_BUFF[0];
                timing_flag = 2;
                break;
            }
        case 2: //0xFF
            {
                XiaoChuangData.Rx_Data[1] = XiaoChuangData.UART4_RX_BUFF[0];
                timing_flag = 3;
                break;
            }
        case 3: //��������
            {
                XiaoChuangData.Rx_Data[2] = XiaoChuangData.UART4_RX_BUFF[0];
                timing_flag = 4;
                break;
            }
        case 4: //0xFF
            {
                timing_flag = 5;
                XiaoChuangData.Rx_Data[3] = XiaoChuangData.UART4_RX_BUFF[0];
                break;
            }
        case 5: //״̬��־
            {
                timing_flag = 0;    //�µ�һ��
                XiaoChuangData.UART4_Rx_Over_Flag = 1; //�������
                XiaoChuangData.Rx_Data[4] = XiaoChuangData.UART4_RX_BUFF[0];
                memset(XiaoChuangData.UART4_RX_BUFF,0,sizeof(XiaoChuangData.UART4_RX_BUFF));  //��0
#if 0
                printk("%#x--%#x--%#x--%#x--%#x\r\n",Rx_Data[0],Rx_Data[1],Rx_Data[2],Rx_Data[3],Rx_Data[4]);
#endif
                break;
            }
        default:
            break;
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
        
        if(0x02 == XiaoChuangData.Rx_Data[2]) //��������
        {
            switch(XiaoChuangData.Rx_Data[4])    //״̬��־
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
                default:
                    break;
            }
        }
        else if(0x03 == XiaoChuangData.Rx_Data[2]) //�������͡���Ҫ�ж�asrWordlist.txt��ġ�
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
                //memset(Lcd_xiaochuang_identify_display_str,0,sizeof(Lcd_xiaochuang_identify_display_str));
                //snprintf(Lcd_xiaochuang_identify_display_str,sizeof(Lcd_xiaochuang_identify_display_str),"ʵ����������");
                //Lcd_Data.Lcd_Display2_Flag = 1; //LCDˢ��
                break;
            }
        case 2:
            {
                //memset(Lcd_xiaochuang_identify_display_str,0,sizeof(Lcd_xiaochuang_identify_display_str));
                //snprintf(Lcd_xiaochuang_identify_display_str,sizeof(Lcd_xiaochuang_identify_display_str),"�������Բ���");
                //Lcd_Data.Lcd_Display2_Flag = 1; //LCDˢ��
                break;
            }
        case 3:
            {
                //memset(Lcd_xiaochuang_identify_display_str,0,sizeof(Lcd_xiaochuang_identify_display_str));
                //snprintf(Lcd_xiaochuang_identify_display_str,sizeof(Lcd_xiaochuang_identify_display_str),"���ܳɾ�����");
                //Lcd_Data.Lcd_Display2_Flag = 1; //LCDˢ��
                break;
            }
        case 4:
            {
                //memset(Lcd_xiaochuang_identify_display_str,0,sizeof(Lcd_xiaochuang_identify_display_str));
                //snprintf(Lcd_xiaochuang_identify_display_str,sizeof(Lcd_xiaochuang_identify_display_str),"�˲Ŵ�������");
                //Lcd_Data.Lcd_Display2_Flag = 1; //LCDˢ��
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


