/*
 *	File_Name:SPI.h
 *	Author:胡尔勤
 *	Date:2023年7月20日
 *	Declaration:未经允许，禁止用于商业用途
 */

#ifndef MODULE_FILES_SPI_INC_SPI_H_
#define MODULE_FILES_SPI_INC_SPI_H_


/* Header files */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "ti_drivers_config.h"
#include "unistd.h"


/* TI-Drivers Header files */
#include <ti/drivers/SPI.h>
#include <ti/drivers/GPIO.h>

/* User Header files */
///


/* Variable Define */
SPI_Handle      spihandle1,spihandle2;
SPI_Params      spiParams;
SPI_Transaction spiTransaction, spiTransaction2;
bool            transferOK,transferOK2;
/* Function Declaration */
void SPI_INIT();

#endif /* MODULE_FILES_SPI_INC_SPI_H_ */
