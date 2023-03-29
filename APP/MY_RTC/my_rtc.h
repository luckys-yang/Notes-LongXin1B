#ifndef _MY_RTC_H
#define _MY_RTC_H
#include "all.h"

typedef struct
{
    bool MY_RTC_over_Flag; //RTC时间片标志位
    uint16_t RTC_now_year;    //年
    uint8_t RTC_now_mon;    //月
    uint8_t RTC_now_day;    //日
    uint8_t RTC_now_hour;    //时
    uint8_t RTC_now_min;    //分
    uint8_t RTC_now_sec;    //秒
    void (*vMY_RTC_init)(void);
    void (*vMY_RTC_get_time_function)(void);
}MY_RTC_TypeDef;

extern MY_RTC_TypeDef myRtcData;

void vMY_RTC_init(void);
void vMY_RTC_get_time_function(void);
#endif


