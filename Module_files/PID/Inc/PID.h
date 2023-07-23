/***************************************
File_Name:PID.h
Date:2023年7月11日
Author:胡尔勤
Declaration:未经允许，禁止用于商业用途
****************************************/
#ifndef MODULE_FILES_PID_INC_PID_H_
#define MODULE_FILES_PID_INC_PID_H_

/* Header files */
///

/* TI-Drivers Header files */
///

/* User Header files */
///

/* Variable Define */
int Error_Last,Integral_error;


/* Structure */
typedef struct
{
    float kp;
    float ki;
    float kd;
}_PID;


/* Function Declaration */
float Position_PID(int error,_PID pid);


#endif /* MODULE_FILES_PID_INC_PID_H_ */
