/************************************
File_Name:Motor.c
Date:2023年7月11日
Author:胡尔勤
Declaration:未经允许，禁止用于商业用途
*************************************/
/* Header files */
#include "Motor.h"

/*  功能：电机初始化
 *  前进：01
 *  后退：10
 */
void Motor_INIT()
{
    GPIO_write(Left_IN1, 0);    /// 前进
    GPIO_write(Left_IN2, 1);
    GPIO_write(Right_IN1, 0);
    GPIO_write(Right_IN2, 1);
}





