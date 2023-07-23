/*
 *	File_Name:Type_Change.h
 *	Author:胡尔勤
 *	Date:2023年7月17日
 *	Declaration:未经允许，禁止用于商业用途
 */

#ifndef MODULE_FILES_TYPE_CHANGE_INC_TYPE_CHANGE_H_
#define MODULE_FILES_TYPE_CHANGE_INC_TYPE_CHANGE_H_
/* Header files */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "ti_drivers_config.h"
#include "unistd.h"

/* TI-Drivers Header files */
///


/* User Header files */
///


/* Variable Define */
///





/* Function Declaration */

/* 十六进制数2字符串 */
void Int_to_Byte(int i,uint8_t *byte);
void Float_to_Byte(float f,uint8_t *byte);
void Short_to_Byte(short s,uint8_t *byte);
void Num2Char(uint8_t num,char * c);
void Hex2String(uint8_t H,char * str);
void HexN2String(uint8_t * HN,uint16_t N,char * strs);

uint8_t FracPart_Len(float f);
uint8_t IntPart_Len(float f);
void Float2String(float f,uint8_t N,char * str,uint8_t L);

#endif /* MODULE_FILES_TYPE_CHANGE_INC_TYPE_CHANGE_H_ */
