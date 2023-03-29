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
  *@brief ��ȡ��ʼ��ʱ��
  *@param  None
  *@retval beginTick  ��ʱ��ʼ����
  */
uint32_t GetTimer1Tick(void)
{
    timeCount = get_clock_ticks();

    return timeCount;
}
/**
  *@brief ��ȡ���������
  *@param  beginTick  ��ʱ��ʼ������GetTimer1Tick()�������
  *@retval ���������
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


