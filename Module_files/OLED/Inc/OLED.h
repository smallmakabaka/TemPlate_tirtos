/***************************************
File_Name:OLED.h
Date:2023年7月11日
Author:胡尔勤
Declaration:未经允许，禁止用于商业用途
****************************************/
#ifndef MODULE_FILES_OLED_INC_OLED_H_
#define MODULE_FILES_OLED_INC_OLED_H_

/* Header files */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "ti_drivers_config.h"
#include "unistd.h"
//#include "msp.h"
#include <stdint.h>

/* TI-Drivers Header files */
#include <ti/drivers/GPIO.h>

/* User Header files */
#include "Others.h"


/* Variable Define */
///

/*Macro Define */
#define OLED_CMD  0 //写命令
#define OLED_DATA 1 //写数据


/* Function Declaration */
uint32_t oled_pow(uint8_t m,uint8_t n);
void OLED_WR_Byte(uint8_t dat,uint8_t cmd);
void OLED_Set_Pos_16x16(uint8_t x,uint8_t y);
void OLED_Set_Pos_8x16(uint8_t x,uint8_t y);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr);
void OLED_ShowNum_int(uint8_t x,uint8_t y,uint32_t num);
void OLED_ShowNum_float(uint8_t x,uint8_t y,uint8_t n,float num);
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr);
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no);
void OLED_Init(void);

#endif /* MODULE_FILES_OLED_INC_OLED_H_ */
