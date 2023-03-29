/**
  * @file   userAppPort.c
  * @author  guoweilkd
  * @version V0.0.0
  * @date    2019/01/17
  * @brief  lkdGui用户应用编写文件。
  */

#include "lkdGui.h"

static void UserMainWinFun(void *param);

/* 用户主窗口 */
lkdWin userMainWin = {
    .x = 20,
    .y = 20,
    .wide = 440,
    .hight = 760,
    .title = "任务1：GPIO基础驱动开发",
    .param = NULL,
    .WindowFunction = UserMainWinFun,
};

/**
  *@brief gui初始化参考函数
  *@param  None
  *@retval None
  */
void userAppPortInit(void)
{

    /* 3. 初始化窗口,添加窗口 */
    GuiWinInit();
    GuiWinAdd(&userMainWin);

}




static void UserMainWinFun(void *param)
 {
     //用户自定义代码。
 }
