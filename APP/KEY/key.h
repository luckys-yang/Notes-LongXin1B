#ifndef _KEY_H
#define _KEY_H
#include "all.h"

//按键
#define S1 56
#define S2 57
#define S3 40
#define S4 41
//读取电平
#define KEY1 gpio_read(S1)
#define KEY2 gpio_read(S2)
#define KEY3 gpio_read(S3)
#define KEY4 gpio_read(S4)

typedef struct
{
    bool Key1_Down_Long_Flag;
    bool Key2_Down_Long_Flag;
    bool Key3_Down_Long_Flag;
    bool Key4_Down_Long_Flag;
    bool Key1_Down_Flag;
    bool Key2_Down_Flag;
    bool Key3_Down_Flag;
    bool Key4_Down_Flag;
    void (*vKEY_init)(void);
    uint8_t (*ucKEY_sub)(void);
    void (*vKEY_detection)(void);
    void (*vKEY_function)(void);
    void (*vKEY_menu_display)(void);
}KEY_TypeDef;

extern KEY_TypeDef Key_Data;
extern uint8_t key1_short_menu_task_state;
extern uint8_t key1_long_enter_flag;  //按键1长按确认键(进入当前选择的任务)
extern uint8_t key2_long_quit_flag;  //按键2长按退出键(退出当前正在执行的任务回到菜单页)
extern bool lcd_display_refresh_flag;


void vKEY_init(void);
uint8_t ucKEY_sub(void);
void vKEY_detection(void);
void vKEY_function(void);
void vKEY_menu_display(void);
#endif

