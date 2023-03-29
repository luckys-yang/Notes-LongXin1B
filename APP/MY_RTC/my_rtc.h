#ifndef _MY_RTC_H
#define _MY_RTC_H
#include "all.h"

typedef struct
{
    bool MY_RTC_over_Flag; //RTCʱ��Ƭ��־λ
    uint16_t RTC_now_year;    //��
    uint8_t RTC_now_mon;    //��
    uint8_t RTC_now_day;    //��
    uint8_t RTC_now_hour;    //ʱ
    uint8_t RTC_now_min;    //��
    uint8_t RTC_now_sec;    //��
    void (*vMY_RTC_init)(void);
    void (*vMY_RTC_get_time_function)(void);
}MY_RTC_TypeDef;

extern MY_RTC_TypeDef myRtcData;

void vMY_RTC_init(void);
void vMY_RTC_get_time_function(void);
#endif


