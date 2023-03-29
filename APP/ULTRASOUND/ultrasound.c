/*
 * ultrasound.c
 *
 * created: 2023-03-28
 *  author: Yang
 *  module: ������(ʹ��CX20106оƬ���в��)  Ӳ������---P1��UART1
 */
#include "ultrasound.h"


extern pwm_cfg_t pwm2_cfg;

//��ʼ���ṹ��
ULTRASOUND_TypeDef Ultrasound_Data =
{
    .Ultrasound_last_distance = 0,
    .Ultrasound_Over_Flag = 0,
    .Ultrasound_distance = 0.0,
    .vULTRASOUND_init = &vULTRASOUND_init,
    .vULTRASOUND_get_distance_function = &vULTRASOUND_get_distance_function
};



/*
���ܣ���ʼ��
*/
void vULTRASOUND_init(void)
{
    gpio_enable(CX_TRIG,DIR_OUT);   //���ģʽ
    gpio_enable(CX_ECHO,DIR_IN);   //����ģʽ
    ls1x_install_gpio_isr(CX_ECHO,INT_TRIG_EDGE_DOWN,vULTRASOUND_IRQhandler,NULL);    //�½��ش��� gpio �ж�
    ls1x_enable_gpio_interrupt(CX_ECHO);   //ʹ���ж�
    gpio_write(CX_TRIG,RESET);  //��������Ĭ������Ϊ�͵�ƽ
}

/*
���ܣ��жϷ�����
*/
void vULTRASOUND_IRQhandler(int IRQn,void *param)
{
    My_pwm_Data.PWM2_Start_Flag = 0;    //�رն�ʱ������
    Ultrasound_Data.Ultrasound_distance = My_pwm_Data.PWM2_Time_count*1.7/10/1.2;//��1.2Ϊ��ʱ��������/1.2
    My_pwm_Data.PWM2_Time_count = 0;    //��ʱ��������0
}

/*
���ܣ���������ຯ��
��������ֱ��LCD��ʾ��������Ļ����
*/
float vULTRASOUND_get_distance_function(void)
{
    uint8_t i=0;
    char arr[50] = {0};
    //if(Ultrasound_Data.Ultrasound_Over_Flag)
    //{
        for(i=0; i<4; i++)
        {
            gpio_write(CX_TRIG,SET);
            delay_us(12);
            gpio_write(CX_TRIG,RESET);
            delay_us(12);
        }
      //  ls1x_pwm_timer_start(devPWM2,(void *)&pwm2_cfg);    //�򿪶�ʱ��(�Ῠ��)
        My_pwm_Data.PWM2_Start_Flag = 1;    //����PWM2��ʱ������
        delay_ms(100);

        if(Ultrasound_Data.Ultrasound_distance >= 2000)
        {
            Ultrasound_Data.Ultrasound_distance = 2000;
        }
        if(Ultrasound_Data.Ultrasound_distance <= 0)
        {
            Ultrasound_Data.Ultrasound_distance = Ultrasound_Data.Ultrasound_last_distance;
        }
        snprintf(arr,sizeof(arr), "����:%.1fcm   ", Ultrasound_Data.Ultrasound_distance);
        GuiRowText(0,0+400,400, FONT_LEFT,(uint8_t*)arr);
        Ultrasound_Data.Ultrasound_last_distance = Ultrasound_Data.Ultrasound_distance;
        Ultrasound_Data.Ultrasound_Over_Flag = 0;
        return Ultrasound_Data.Ultrasound_distance;
    //}
    return 0;
}



