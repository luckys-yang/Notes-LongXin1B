/*
 * my_rtc.c
 *
 * created: 2023-03-28
 *  author: Yang
 *  module: RTCʱ��
 */
#include "my_rtc.h"

//��ʼ��д���ʼʱ��
struct tm tmp,now =
{
    .tm_sec = 20,
    .tm_min = 22,
    .tm_hour = 17,
    .tm_mday = 28,
    .tm_mon = 3,
    .tm_year = 2023
};

//��ʼ���ṹ��
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
���ܣ���ʼ��
*/
void vMY_RTC_init(void)
{
    ls1x_rtc_init(NULL,NULL);
    ls1x_rtc_set_datetime(&now);    //����RTCʱ��
}

/*
���ܣ���ȡ��ǰʱ��
*/
void vMY_RTC_get_time_function(void)
{
    char arr1[50] = {0};
    char arr2[50] = {0};
    
    if(myRtcData.MY_RTC_over_Flag)
    {
        myRtcData.MY_RTC_over_Flag = 0;
        ls1x_rtc_get_datetime(&tmp);    //��ȡʱ��
        normalize_tm(&tmp,0);   //ת��Ϊʵ��ʱ��---���+1900���·�+1
        myRtcData.RTC_now_year = tmp.tm_year;
        myRtcData.RTC_now_mon = tmp.tm_mon;
        myRtcData.RTC_now_day = tmp.tm_mday;
        myRtcData.RTC_now_hour = tmp.tm_hour;
        myRtcData.RTC_now_min = tmp.tm_min;
        myRtcData.RTC_now_sec = tmp.tm_sec;

        snprintf(arr1,sizeof(arr1),"��ǰ���ڣ�%04d-%02d-%02d    ",myRtcData.RTC_now_year,myRtcData.RTC_now_mon,myRtcData.RTC_now_day);
        GuiRowText(0,0+500,400, FONT_LEFT,(uint8_t*)arr1);
        snprintf(arr2,sizeof(arr2),"��ǰʱ�䣺%02d-%02d-%02d    ",myRtcData.RTC_now_hour,myRtcData.RTC_now_min,myRtcData.RTC_now_sec);
        GuiRowText(0,0+600,400, FONT_LEFT,(uint8_t*)arr2);
    }
}
