///************************************
//File_Name:PWM.c
//Date:2023年7月11日
//Author:胡尔勤
//Declaration:未经允许，禁止用于商业用途
//*************************************/
//
///*************************
//    改变占空比：PWM_setDuty(pwmHandle, dutyValue);
//***************************/
//
///* Header files */
//#include "PWM.h"
//
//
///*  功能：PWM初始化
// *
// */
//void PWM_INIT()
//{
//    PWM_init();
//    PWM_Params_init(&pwmParams);
//    pwmParams.idleLevel = PWM_IDLE_LOW;         /// 初始电平
//    pwmParams.periodUnits = PWM_PERIOD_US;      /// 周期单位
//    pwmParams.periodValue = 1000;               /// 周期大小
//    pwmParams.dutyUnits = PWM_DUTY_US;          /// 占空比单位
//    pwmParams.dutyValue = 0;                    /// 占空比大小
//    pwm1 = PWM_open(PWM_Left, &pwmParams);
//    pwm2 = PWM_open(PWM_Right,&pwmParams);
//    PWM_start(pwm1);                            /// PWM 开启
//    PWM_start(pwm2);
//}
//
///*  功能：左轮百分比调速
// *
// */
//void Speed_Cro_Left(uint16_t percent)
//{
//    uint32_t dutyCycle;
//    dutyCycle = (uint32_t) (((uint64_t) (1000 *percent )) / 100);
//    PWM_setDuty(pwm1, dutyCycle);
//}
//
///*  功能：右轮百分比调速
// *
// */
//void Speed_Cro_Right(uint16_t percent)
//{
//    uint32_t dutyCycle;
//    dutyCycle = (uint32_t) (((uint64_t) (1000 *percent )) / 100);
//    PWM_setDuty(pwm2, dutyCycle);
//}
//
///*  功能：左轮PWM控制，正号表示前进，负号表示后退
// *
// */
//void set_PWM_L(int speed)
//{
//  if (speed > 0)
//  {
//      GPIO_write(Left_IN1, 0);  /// 前进
//      GPIO_write(Left_IN2, 1);
//  }
//  else
//  {
//      GPIO_write(Left_IN1, 1);  /// 后退
//      GPIO_write(Left_IN2, 0);
//  }
//
//  PWM_setDuty(pwm1,  abs(speed));
//}
//
///*  功能：右左=轮PWM控制，正号表示前进，负号表示后退
// *
// */
//void set_PWM_R(int speed)
//{
//  if (speed > 0)
//  {
//      GPIO_write(Right_IN1, 0);  /// 前进
//      GPIO_write(Right_IN2, 1);
//  }
//  else
//  {
//      GPIO_write(Right_IN1, 1);  /// 后退
//      GPIO_write(Right_IN2, 0);
//  }
//
//  PWM_setDuty(pwm2,  abs(speed));
//}
