/*
 * lkd_system_clk.c
 *
 * created: 2022/7/13
 *  author:
 */
#include <stdio.h>

#include "ls1b.h"
#include "mips.h"
#include "stdint.h"
static uint32_t timeCount;
/**
  *@brief 获取开始计时数
  *@param  None
  *@retval beginTick  计时开始数，
  */
uint32_t GetTimer1Tick(void)
{
    timeCount = get_clock_ticks();

    return timeCount;
}
/**
  *@brief 获取间隔周期数
  *@param  beginTick  计时开始数，由GetTimer1Tick()函数获得
  *@retval 间隔周期数
  */
uint32_t GetTimer1IntervalTick(uint32_t beginTick)
{
    uint32_t temptick;
    temptick = GetTimer1Tick();
    if(beginTick <= temptick)
    {
        return (temptick - beginTick);
    }
    else
    {
        return ((0xFFFFFFFF - beginTick)+temptick);
    }
}


