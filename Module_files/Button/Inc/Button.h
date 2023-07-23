/***************************************
File_Name:Button.h
Date:2023年7月11日
Author:胡尔勤
Declaration:未经允许，禁止用于商业用途
****************************************/
#ifndef MODULE_FILES_BUTTON_INC_BUTTON_H_
#define MODULE_FILES_BUTTON_INC_BUTTON_H_


/* Header files */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "ti_drivers_config.h"
#include "unistd.h"

/* TI-Drivers Header files */
#include <ti/drivers/apps/LED.h>
#include <ti/drivers/apps/Button.h>

/* User Header files */
///

/* Variable Define */
Button_Params buttonparams;
Button_Handle buttonhandle1,buttonhandle2;
uint8_t Mode;                   /// 用于模式区分


/* Function Declaration */
void Button_INIT();
void buttonCallbackFxn1(Button_Handle handle, Button_EventMask events);
void buttonCallbackFxn2(Button_Handle handle, Button_EventMask events);



#endif /* MODULE_FILES_BUTTON_INC_BUTTON_H_ */
