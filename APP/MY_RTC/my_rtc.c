/*
 * my_rtc.c
 *
 * created: 2023-03-28
 *  author: Yang
 *  module: RTC时间
 */
#include "my_rtc.h"

//初始化写入初始时间
struct tm tmp,now =
{
    .tm_sec = 20,
    .tm_min = 22,
    .tm_hour = 17,
    .tm_mday = 28,
    .tm_mon = 3,
    .tm_year = 2023
};

//初始化结构体
MY_RTC_TypeDef myRtcData =
{
    .MY_RTC_over_Flag = 0,
    .RTC_now_year = 0,
    .RTC_now_mon = 0,
    .RTC_now_day = 0,
    .RTC_now_hour = 0,
    .RTC_now_min = 0,
    .RTC_now_sec = 0,
    .vMY_RTC_init = &vMY_RTC_init,
    .vMY_RTC_get_time_function = &vMY_RTC_get_time_function
};

/*
功能：初始化
*/
void vMY_RTC_init(void)
{
    ls1x_rtc_init(NULL,NULL);
    ls1x_rtc_set_datetime(&now);    //设置RTC时间
}

/*
功能：获取当前时间
*/
void vMY_RTC_get_time_function(void)
{
    char arr1[50] = {0};
    char arr2[50] = {0};
    
    if(myRtcData.MY_RTC_over_Flag)
    {
        myRtcData.MY_RTC_over_Flag = 0;
        ls1x_rtc_get_datetime(&tmp);    //获取时间
        normalize_tm(&tmp,0);   //转换为实际时间---年份+1900，月份+1
        myRtcData.RTC_now_year = tmp.tm_year;
        myRtcData.RTC_now_mon = tmp.tm_mon;
        myRtcData.RTC_now_day = tmp.tm_mday;
        myRtcData.RTC_now_hour = tmp.tm_hour;
        myRtcData.RTC_now_min = tmp.tm_min;
        myRtcData.RTC_now_sec = tmp.tm_sec;

        snprintf(arr1,sizeof(arr1),"当前日期：%04d-%02d-%02d    ",myRtcData.RTC_now_year,myRtcData.RTC_now_mon,myRtcData.RTC_now_day);
        GuiRowText(0,0+500,400, FONT_LEFT,(uint8_t*)arr1);
        snprintf(arr2,sizeof(arr2),"当前时间：%02d-%02d-%02d    ",myRtcData.RTC_now_hour,myRtcData.RTC_now_min,myRtcData.RTC_now_sec);
        GuiRowText(0,0+600,400, FONT_LEFT,(uint8_t*)arr2);
    }
}
