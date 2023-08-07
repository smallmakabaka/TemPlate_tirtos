/***************************************
File_Name:UART.h
Date:2023年7月11日
Author:胡尔勤
Declaration:未经允许，禁止用于商业用途
****************************************/
#ifndef MODULE_FILES_UART_INC_UART_H_
#define MODULE_FILES_UART_INC_UART_H_

/* Header files */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "ti_drivers_config.h"
#include "unistd.h"

/* TI-Drivers Header files */
#include <ti/drivers/UART.h>


/* User Header files */
///


/* Variable Define */
UART_Params uartparams1 , uartparams2 , uartparams3;
UART_Handle uartHandle1,uartHandle2,uartHandle3;
uint8_t readbuffer[10];
uint8_t read_status,close_status;

/* Function Declaration */
void UART_INIT();
void UART3_DEINIT();
//void WriteUART1_Callback (UART_Handle handle,void *buf,size_t count);
void ReadUART1_Callback (UART_Handle handle,void *buf,size_t count);
void ReadUART2_Callback (UART_Handle handle,void *buf,size_t count);
void WriteUART2_Callback (UART_Handle handle,void *buf,size_t count);
void ReadUART3_Callback (UART_Handle handle,void *buf,size_t count);
void Read_Circle();

#endif /* MODULE_FILES_UART_INC_UART_H_ */
