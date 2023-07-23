/***************************************
File_Name:Timer32.h
Date:2023年7月11日
Author:胡尔勤
Declaration:未经允许，禁止用于商业用途
****************************************/
#ifndef MODULE_FILES_TIMER32_INC_TIMER32_H_
#define MODULE_FILES_TIMER32_INC_TIMER32_H_



/* Header files */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "ti_drivers_config.h"
#include "unistd.h"

/* TI-Drivers Header files */
#include <ti/drivers/Timer.h>


/* User Header files */
///


/* Variable Define */
Timer_Handle    timer32handle;
Timer_Params    timer32params;
int32_t timer32status;


/* Function Declaration */
void Timer32_INIT();
void Timer32_CallBackFxn(Timer_Handle handle);


#endif /* MODULE_FILES_TIMER32_INC_TIMER32_H_ */
