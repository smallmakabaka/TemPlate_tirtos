/***************************************
File_Name:LED.h
Date:2023年7月11日
Author:胡尔勤
Declaration:未经允许，禁止用于商业用途
****************************************/
#ifndef MODULE_FILES_LED_INC_LED_H_
#define MODULE_FILES_LED_INC_LED_H_

/* Header files */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "ti_drivers_config.h"
#include "unistd.h"


/* TI-Drivers Header files */
#include <ti/drivers/apps/LED.h>


/* User Header files */
///


/* Variable Define */
LED_Handle ledHandle1,ledHandle2,ledHandle3,ledHandle4;
LED_Params ledParams;


/* Function Declaration */
void Led_INIT();

#endif /* MODULE_FILES_LED_INC_LED_H_ */
