/************************************
File_Name:PID.c
Date:2023年7月11日
Author:胡尔勤
Declaration:未经允许，禁止用于商业用途
*************************************/

/* Header files */
#include "Module_files/PID/Inc/PID.h"


/// 简易的离散位置式 PID
float Position_PID(float error,_PID pid)//error为输入偏差
{
    float Position_KP=pid.kp,Position_KI=pid.ki,Position_KD=pid.kd;
    float Error_Current , pid_out;
    Error_Current=error;                                                //计算当前的偏差值
    Integral_error+=Error_Current;                                      //求出偏差的积分
    pid_out=Position_KP*Error_Current+Position_KI*Integral_error+Position_KD*(Error_Current-Error_Last); //位置式PID控制器
    Error_Last=Error_Current;                                          //保存上一次偏差
    pid_out=(pid_out>30)?30:pid_out;                                    // 输出限幅
    pid_out=(pid_out<-30)?-30:pid_out;
    return pid_out;
}
