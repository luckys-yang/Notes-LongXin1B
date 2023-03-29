/**
  * @file   userAppPort.c
  * @author  guoweilkd
  * @version V0.0.0
  * @date    2019/01/17
  * @brief  lkdGui�û�Ӧ�ñ�д�ļ���
  */

#include "lkdGui.h"

static void UserMainWinFun(void *param);

/* �û������� */
lkdWin userMainWin = {
    .x = 20,
    .y = 20,
    .wide = 440,
    .hight = 760,
    .title = "����1��GPIO������������",
    .param = NULL,
    .WindowFunction = UserMainWinFun,
};

/**
  *@brief gui��ʼ���ο�����
  *@param  None
  *@retval None
  */
void userAppPortInit(void)
{

    /* 3. ��ʼ������,��Ӵ��� */
    GuiWinInit();
    GuiWinAdd(&userMainWin);

}




static void UserMainWinFun(void *param)
 {
     //�û��Զ�����롣
 }
