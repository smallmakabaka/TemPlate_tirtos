/*
 *	File_Name:DataPackage.h
 *	Author:������
 *	Date:2023��7��17��
 *	Declaration:δ��������ֹ������ҵ��;
 */

#ifndef MODULE_FILES_DATAPACKAGE_INC_DATAPACKAGE_H_
#define MODULE_FILES_DATAPACKAGE_INC_DATAPACKAGE_H_
/* Header files */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "ti_drivers_config.h"
#include "unistd.h"

/* TI-Drivers Header files */
///


/* User Header files */
///



/* Macro definition */
#define decL 2          //// С��λ��



/* Variable Define */



/* Function Declaration */
void DATApack(float * f,uint8_t N,uint8_t * L,char * str);
//void packup32(uint8_t boolnum,uint8_t bytenum,uint8_t shortnum,uint8_t intnum, uint8_t floatnum,uint8_t *bl,uint8_t *by, short *sh, int *in, float *fl);
void Pack2Stm(uint8_t wm , float f1 , float f2 , float f3 , float f4 , uint8_t * txbuff , uint8_t len);
#endif /* MODULE_FILES_DATAPACKAGE_INC_DATAPACKAGE_H_ */
