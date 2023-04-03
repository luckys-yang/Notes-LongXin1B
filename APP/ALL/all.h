#ifndef _ALL_H
#define _ALL_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include "ls1b.h"
#include "mips.h"
#include "tick.h"

/*BSP BEGIN*/
#include "bsp.h"
#include "ls1b_gpio.h"
#include "ls1x_fb.h"
#include "lkdGui.h"
#include "ns16550.h"
#include "ls1x_rtc.h"
#include "ls1x_i2c_bus.h"
#include "i2c/ads1015.h"
#include "i2c/gp7101.h"
#include "lwmem.h"
#include "ls1x_pwm.h"
#include "lkdGuiTypedef.h"
/*BSP END*/

/*MY BEGIN*/
#include "tim.h"
#include "led.h"
#include "key.h"
#include "buzzer.h"
#include "smg.h"
#include "lcd.h"
#include "xiaochuang.h"
#include "lm35.h"
#include "resistor.h"
#include "fan.h"
#include "bh1750.h"
#include "hmc5883l.h"
#include "motor.h"
#include "my_pwm.h"
#include "ultrasound.h"
#include "my_uart.h"
#include "my_rtc.h"
#include "my_adc.h"
#include "task.h"
/*MY END*/

#define SET  1
#define RESET 0

//Ê±¼äÆ¬ÂÖÑ¯
//typedef struct
//{
    //uint32_t TASK_LCD_TIME;
//}TASK_TypeDef;
//extern TASK_TypeDef TaskData;


/*TEST FUNCTION BEGIN*/
void Task_1_1(void);
void vSMG_test(void);
void Task_3(void);
void Task_5(void);
void Task_7(void);
void Coord_init(void);
void Coord_display_date(void);
void Task_while(void);
/*TEST FUNCTION END*/

#endif

