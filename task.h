#ifndef _TASK_H
#define _TASK_H
#include "all.h"

typedef struct
{
    uint8_t Now_task_state; //当前任务
    void (*vTASK_one)(void);
    void (*vTASK_two)(void);
    void (*vTASK_three)(void);
    void (*vTASK_four)(void);
    void (*vTASK_five)(void);
    void (*vTASK_six)(void);
    void (*vTASK_seven)(void);
    void (*vTASK_eight)(void);
    void (*vTASK_nine)(void);
    void (*vTASK_ten)(void);
    void (*vTASK_all)(void);

}TASK_TypeDef;

extern TASK_TypeDef TaskData;


void vTASK_one(void);
void vTASK_two(void);
void vTASK_three(void);
void vTASK_four(void);
void vTASK_five(void);
void vTASK_six(void);
void vTASK_seven(void);
void vTASK_eight(void);
void vTASK_nine(void);
void vTASK_ten(void);
void vTASK_all(void);
#endif 

