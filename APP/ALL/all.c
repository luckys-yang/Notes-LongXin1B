/*
 * all.c
 *
 * created: 2023-03-23
 *  author: Yang
 *  module: 测试区
 */

#include "all.h"

/*SYS FUNCTION BEGIN*/
//ls1x_uart_write(uart, buf, size, arg);发送字符串
//获取当前时间(单位ms)
extern unsigned int get_clock_ticks(void);
//打印函数在控制台(需要拨下MCU通信开关)
extern int printk(const char* format, ...);
//LCD清屏
extern void fb_cons_clear(void);
//画有颜色的矩形
extern void fb_drawrect(int x1, int y1, int x2, int y2, unsigned coloridx);
//填充矩形(常用于刷新需要变化的数据，坐标和显示文本坐标一致)
extern void fb_fillrect(int x1, int y1, int x2, int y2, unsigned coloridx);
//输出文本
extern void fb_textout(int x, int y, char *str);
//在LCD[x,y]处用指定颜色、宽度画点(宽度越大点越大)
extern void fb_drawpoint(int x, int y, int thickness, unsigned coloridx);
/*SYS FUNCTION END*/

/*GUI FUNCTION BEGIN*/

//写单行文本(一般Y相隔40 字体宽480 只能显示15个中文)
extern void GuiRowText(lkdCoord x, lkdCoord y,uint16_t wide, FontFlag flag,uint8_t *str);
//清屏CWHITLE(白色) CBLACK(黑色)
//#define GuiClearScreen(color) GuiFillRect(0, 0, GUIXMAX - 1,GUIXMAX - 1,color);

/*GUI FUNCTION END*/

TASK_TypeDef TaskData =
{
    .TASK_LCD_TIME = 0,
};



//任务1.1
void Task_1_1(void)
{
    Led_Data.vLED_control(Led_Data.Red_Led,SET);    //红
    delay_ms(1000); //延时1s
    Led_Data.vLED_control(Led_Data.Red_Led,RESET);
    Led_Data.vLED_control(Led_Data.Green_Led,SET);    //绿
    delay_ms(1000); //延时1s
    Led_Data.vLED_control(Led_Data.Green_Led,RESET);
    Led_Data.vLED_control(Led_Data.Blue_Led,SET);    //蓝
    delay_ms(1000); //延时1s
    Led_Data.vLED_control(Led_Data.Blue_Led,RESET);
}

//任务2
void vSMG_test(void)
{
    uint16_t count = 5;
    uint8_t temp = 0;   //段码数据
    uint32_t ms_count1 = get_clock_ticks()+1000;  //获取当前时间+1000
    uint32_t ms_count2 = 0; //500ms
    uint8_t num = 3;
    bool flag = 1;
    while(count > 0)
    {
        // 每隔1000个倒计时周期刷新显示
        if(get_clock_ticks() > ms_count1)
        {
            ms_count1=get_clock_ticks()+1000;
            count--;
        }
        //数码管1显示
        Smg_Data.vHC595_send_data(0x40);    //'-'
        Smg_Data.vSMG_choose(0);
        delay_ms(1);
        //数码管2显示
        temp = Display[count / 10 % 10];
        Smg_Data.vHC595_send_data(temp);
        Smg_Data.vSMG_choose(1);
        delay_ms(1);
        //数码管3显示
        temp = Display[count % 10];
        Smg_Data.vHC595_send_data(temp);
        Smg_Data.vSMG_choose(2);
        delay_ms(1);
        //数码管4显示
        Smg_Data.vHC595_send_data(0x40);    //'-'
        Smg_Data.vSMG_choose(3);
        delay_ms(1);
    }
    ms_count2 = get_clock_ticks()+500;
    while(num > 0)
    {
        if(flag)
        {
            Smg_Data.vHC595_send_data(0x40);    //'-'
            Smg_Data.vSMG_choose(0);
            delay_ms(1);
            //数码管2显示
            Smg_Data.vHC595_send_data(Display[15]);
            Smg_Data.vSMG_choose(1);
            delay_ms(1);
            //数码管3显示
            Smg_Data.vHC595_send_data(Display[15]);
            Smg_Data.vSMG_choose(2);
            delay_ms(1);
            //数码管4显示
            Smg_Data.vHC595_send_data(0x40);    //'-'
            Smg_Data.vSMG_choose(3);
            delay_ms(1);
            Led_Data.vLED_control(Led_Data.Red_Led,SET);
            Buzzer_Data.vBUZZER_control(SET);
            if(get_clock_ticks() > ms_count2)
            {
                ms_count2 = get_clock_ticks()+500;
                flag = !flag;
            }
        }
        else
        {
            Smg_Data.vHC595_send_data(0x00);
            Smg_Data.vSMG_choose(0);
            delay_ms(1);
            //数码管2显示
            Smg_Data.vHC595_send_data(0x00);
            Smg_Data.vSMG_choose(1);
            delay_ms(1);
            //数码管3显示
            Smg_Data.vHC595_send_data(0x00);
            Smg_Data.vSMG_choose(2);
            delay_ms(1);
            //数码管4显示
            Smg_Data.vHC595_send_data(0x00);
            Smg_Data.vSMG_choose(3);
            delay_ms(1);
            Led_Data.vLED_control(Led_Data.Red_Led,RESET);
            Buzzer_Data.vBUZZER_control(RESET);
            if(get_clock_ticks() > ms_count2)
            {
                ms_count2 = get_clock_ticks()+500;
                flag = !flag;
                num--;
            }
        }
    }

}
extern const unsigned char gImage_111[320000];
//任务3
void Task_3(void)
{
    Lcd_Data.vLCD_set_bgcolor(cidxBLACK,clRED); //红
    delay_ms(1000);
    Lcd_Data.vLCD_set_bgcolor(cidxBLACK,clGREEN); //绿
    delay_ms(1000);
    Lcd_Data.vLCD_set_bgcolor(cidxBLACK,clBLUE); //蓝
    delay_ms(1000);
    fb_cons_clear();    //清屏
    GuiRowText(0,100,480,FONT_LEFT,(uint8_t*)"喜迎二十大、永远跟党走、");
    GuiRowText(0,140,480,FONT_LEFT,(uint8_t*)"奋进新征程");
    //fb_textout(0,200,"喜迎二十大、永远跟党走、奋进新征程");
    delay_ms(4000);
    fb_cons_clear();//清屏
    Lcd_Data.display_pic(50,50,400,400,(uint8_t*)gImage_111);  //显示图片
}

uint8_t threshold = 33; //阈值要求是+-2

//任务5(丢定时器中断里)
void Task_5(void)
{

    if(Lm35_Data.Lm35_temp <= (threshold - 1))//当前温度小于阈值+-1
    {
        Fan_Data.vFAN_control(0);
        Fan_Data.vFAN_set_speed(0);
        Resistor_Data.vRESISTOR_control(SET);   //加热打开
        Led_Data.vLED_control(Led_Data.Green_Led,RESET);
        Led_Data.vLED_control(Led_Data.Red_Led,SET);
    }
    if(Lm35_Data.Lm35_temp >= (threshold + 1))//当前温度大于阈值+-1
    {
        Resistor_Data.vRESISTOR_control(RESET);   //加热关闭
        Fan_Data.vFAN_control(1);
        Fan_Data.vFAN_set_speed(100);
        Led_Data.vLED_control(Led_Data.Red_Led,RESET);
        Led_Data.vLED_control(Led_Data.Green_Led,SET);

    }
}

bool Task_7_Flag = 0;

//任务
void Task_7(void)
{
    if(Ultrasound_Data.Ultrasound_distance >= 20)
    {
        Motor_Data.vMOTOR_set_speed(0); //最大转速
    }
    else if(Ultrasound_Data.Ultrasound_distance >= 10 && Ultrasound_Data.Ultrasound_distance < 20)
    {
        if(Ultrasound_Data.Ultrasound_distance <= 11)
        {
            Motor_Data.vMOTOR_set_speed(4);
        }
        else if(Ultrasound_Data.Ultrasound_distance <= 12)
        {
            Motor_Data.vMOTOR_set_speed(8);
        }
        else if(Ultrasound_Data.Ultrasound_distance <= 13)
        {
            Motor_Data.vMOTOR_set_speed(12);
        }
        else if(Ultrasound_Data.Ultrasound_distance <= 14)
        {
            Motor_Data.vMOTOR_set_speed(16);
        }
        else if(Ultrasound_Data.Ultrasound_distance <= 15)
        {
            Motor_Data.vMOTOR_set_speed(20);
        }
        else if(Ultrasound_Data.Ultrasound_distance <= 16)
        {
            Motor_Data.vMOTOR_set_speed(24);
        }
        else if(Ultrasound_Data.Ultrasound_distance <= 17)
        {
            Motor_Data.vMOTOR_set_speed(28);
        }
        else if(Ultrasound_Data.Ultrasound_distance <= 18)
        {
            Motor_Data.vMOTOR_set_speed(32);
        }
        else if(Ultrasound_Data.Ultrasound_distance <= 19)
        {
            Motor_Data.vMOTOR_set_speed(36);
        }

    }
    else if(Ultrasound_Data.Ultrasound_distance < 10)
    {
        Motor_Data.vMOTOR_set_speed(50); //停止
    }
    delay_ms(500);
    delay_ms(500);
}

bool LM35_Over_Flag = 0;
bool BH1750_Over_Flag = 0;

/*显示坐标初始化*/
void Coord_init(void)
{
    uint16_t i = 0;
    char arr[50];
    static num1 = 15;   //15s 500ms*30

    snprintf(arr,sizeof(arr),"(s)");
    fb_put_string(0,370,arr,Lcd_Data.Lcd_cid_color[6]);
    for(i = 0; i <=730;)
    {
        snprintf(arr,sizeof(arr),"%d",num1);
        fb_put_string(i+30,370,arr,Lcd_Data.Lcd_cid_color[6]);//显示x轴时间
        fb_drawpoint(i+40,350,20,Lcd_Data.Lcd_cid_color[7]);    //显示点
        i+=30;
        num1 += 15;
    }
    fb_drawline(0,350,800,350,Lcd_Data.Lcd_cid_color[7]);   //画x轴(白色)
    fb_drawline(0,20,0,350,Lcd_Data.Lcd_cid_color[7]);   //画y轴(白色)
}
/*
显示数据
*/
void Coord_display_date(void)
{
    if(LM35_Over_Flag)  //温度
    {
        char arr1[50];
        static int x1 = 0;
        static int y1 = 200;
        static float last_temp = 0;

        LM35_Over_Flag = 0;

        /*显示温度*/
        fb_fillrect(100,400,260,450, cidxBLACK);
        snprintf(arr1,sizeof(arr1),"当前温度:%.1f°",Lm35_Data.Lm35_temp);
        fb_put_string(100,400,arr1,Lcd_Data.Lcd_cid_color[4]);
        if(Lm35_Data.Lm35_temp > last_temp)
        {
            y1--;
        }
        else if(Lm35_Data.Lm35_temp < last_temp)
        {
            y1++;
        }
        else
        {
            y1 = y1;
        }
        x1++;

        fb_drawpoint(x1,y1,7,Lcd_Data.Lcd_cid_color[4]);
        last_temp = Lm35_Data.Lm35_temp;


        if(BH1750_Over_Flag)
        {
            char arr2[50];
            static int x2 = 0;
            static int y2 = 210;
            static float last_temp2 = 0;

            BH1750_Over_Flag = 0;
            /*显示光度值*/
            fb_fillrect(400,400,760,450, cidxBLACK);
            snprintf(arr2,sizeof(arr2),"当前光度值:%.0f lx",Bh1750_Data.Bh1750_value);
            fb_put_string(400,400,arr2,Lcd_Data.Lcd_cid_color[1]);
            if(Bh1750_Data.Bh1750_value > last_temp2)
            {
                y2--;
            }
            else if(Bh1750_Data.Bh1750_value < last_temp2)
            {
                y2++;
            }
            else
            {
                y2 = y2;
            }
            x2++;
            fb_drawpoint(x2,y2,7,Lcd_Data.Lcd_cid_color[1]);
            last_temp2 = Bh1750_Data.Bh1750_value;
        }
        if(730 == x1)
        {
            fb_cons_clear();
            Coord_init();
        }
    }
}

/*****************************************任务***********************************/

//任务1
void auto_task1(void)
{
    Task_1_1();
    delay_ms(1000);
    //渐变待写
}
//任务2
void auto_task2(void)
{
    static uint8_t key1_temp_flag = 0;
    if(Key_Data.Key1_Down_Flag)
    {
        Key_Data.Key1_Down_Flag = 0;
        key1_temp_flag = !key1_temp_flag;
    }
    if(key1_temp_flag)
    {
        Buzzer_Data.vBUZZER_control(SET);
    }
    else
    {
        Buzzer_Data.vBUZZER_control(RESET);
    }
}

//任务3

void auto_task3(void)
{
    //1
    uint16_t count1 = 0;
    uint32_t ms_count1 = get_clock_ticks()+3000;  //获取当前时间+3000 3s
    bool flag1 = 1;
    while(count1 < 2)
    {
        // 每隔3000个倒计时周期刷新显示
        if(get_clock_ticks() > ms_count1)
        {
            ms_count1=get_clock_ticks()+3000;
            flag1 = !flag1;   //取反
            count1++;
        }
        if(flag1)
        {
            Smg_Data.vSMG_display("2023");
        }
        else
        {
            Smg_Data.vSMG_display("0402");
        }
    }
    Smg_Data.vSMG_off();    //数码管全灭
    delay_ms(3000);
    //2
    uint8_t count2 = 6;
    char arr1[5] = "-05-";
    uint32_t ms_count2 = get_clock_ticks()+1000;  //获取当前时间+1000 1s;

    while(count2 > 0)
    {
        Smg_Data.vSMG_display((uint8_t*)arr1);
        // 每隔1000个倒计时周期刷新显示
        if(get_clock_ticks() > ms_count1)
        {
            ms_count1=get_clock_ticks()+1000;
            count2--;
            snprintf(arr1,sizeof(arr1),"-%02d-",count2);
        }

    }

    //3
    uint8_t num1 = 3;
    bool flag2 = 1;
    uint32_t ms_count3 = get_clock_ticks()+500; //500ms
    while(num1 > 0)
    {
        if(flag2)
        {
            Smg_Data.vSMG_display("-FF-");
            Led_Data.vLED_control(Led_Data.Green_Led,SET);
            Buzzer_Data.vBUZZER_control(SET);
            if(get_clock_ticks() > ms_count3)
            {
                ms_count3 = get_clock_ticks()+500;
                flag2 = !flag2;
            }
        }
        else
        {
            Smg_Data.vSMG_off();    //数码管全灭
            Led_Data.vLED_control(Led_Data.Green_Led,RESET);
            Buzzer_Data.vBUZZER_control(RESET);
            if(get_clock_ticks() > ms_count3)
            {
                ms_count3 = get_clock_ticks()+500;
                flag2 = !flag2;
                num1--;
            }
        }
    }
    /*最后全部熄灭*/
    Smg_Data.vSMG_off();    //数码管全灭
    Led_Data.vLED_control(Led_Data.Green_Led,RESET);
    Buzzer_Data.vBUZZER_control(RESET);
}

//任务4
void auto_task4(void)
{
    GuiClearScreen(CBLACK);  //清屏
    fb_cons_clear();    //清屏
    delay_ms(200);
    GuiRowText(0,0+500,480, FONT_LEFT,(uint8_t*)"技能成就人生，人才创造世界");
    delay_ms(5000);
    fb_drawrect(300,200,500,250,Lcd_Data.Lcd_cid_color[4]);  //红色矩形框200 X 50
    Lcd_Data.vLCD_gui_pentagram(60,200,50,CBLACK);  //五角星
    delay_ms(8000);
    GuiClearScreen(CBLACK);  //清屏
    fb_cons_clear();    //清屏
}
bool Lcd_display1_flag = 0; //LCD刷新标志位
//任务5
void auto_task5(void)
{
    static uint8_t Control_display_flag = 0;

    if(Key_Data.Key2_Down_Flag) //按键2控制是否显示
    {
        Key_Data.Key2_Down_Flag = 0;
        Lcd_Data.Lcd_open_Flag = !Lcd_Data.Lcd_open_Flag;
    }
}

//任务6
void auto_task6(void)
{
    if(Key_Data.Key3_Down_Flag) //按键3
    {
        Key_Data.Key3_Down_Flag = 0;
        GuiClearScreen(CBLACK);  //清屏
        fb_cons_clear();    //清屏
        XiaoChuangData.vXIAOCHUANG_play_specify_content(4); //播报"技能改变人生，技能成就梦想"
    }
    if(Key_Data.Key4_Down_Flag) //按键4
    {
        Key_Data.Key4_Down_Flag = 0;
        XiaoChuangData.vXIAOCHUANG_send_rouse();    //发送唤醒
    }
}

void Task_while(void)
{
    auto_task2();
    auto_task5();
    auto_task6();
}




