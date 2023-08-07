/***************************************
File_Name:PID.h
Date:2023��7��11��
Author:������
Declaration:δ��������ֹ������ҵ��;
****************************************/
#ifndef MODULE_FILES_PID_INC_PID_H_
#define MODULE_FILES_PID_INC_PID_H_

/* Header files */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "ti_drivers_config.h"
#include "unistd.h"

/* TI-Drivers Header files */
///

/* User Header files */
///

/* Variable Define */
float Error_Last,Integral_error;


/* Structure */
typedef struct
{
    float kp;
    float ki;
    float kd;
    uint8_t PIDnum;
}_PID;

typedef enum PIDSwitch
{
    PID_OFF=0,
    PID_ON=1

}PIDSwitch;

/* Variable Define */
_PID Trace_PID , TracePro_PID;          /// Ѳ��PID����
PIDSwitch pidS , PropidS;

/* Function Declaration */
float Position_PID(float error,_PID pid);


#endif /* MODULE_FILES_PID_INC_PID_H_ */
