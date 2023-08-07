///************************************
//File_Name:PWM.c
//Date:2023��7��11��
//Author:������
//Declaration:δ��������ֹ������ҵ��;
//*************************************/
//
///*************************
//    �ı�ռ�ձȣ�PWM_setDuty(pwmHandle, dutyValue);
//***************************/
//
///* Header files */
//#include "PWM.h"
//
//
///*  ���ܣ�PWM��ʼ��
// *
// */
//void PWM_INIT()
//{
//    PWM_init();
//    PWM_Params_init(&pwmParams);
//    pwmParams.idleLevel = PWM_IDLE_LOW;         /// ��ʼ��ƽ
//    pwmParams.periodUnits = PWM_PERIOD_US;      /// ���ڵ�λ
//    pwmParams.periodValue = 1000;               /// ���ڴ�С
//    pwmParams.dutyUnits = PWM_DUTY_US;          /// ռ�ձȵ�λ
//    pwmParams.dutyValue = 0;                    /// ռ�ձȴ�С
//    pwm1 = PWM_open(PWM_Left, &pwmParams);
//    pwm2 = PWM_open(PWM_Right,&pwmParams);
//    PWM_start(pwm1);                            /// PWM ����
//    PWM_start(pwm2);
//}
//
///*  ���ܣ����ְٷֱȵ���
// *
// */
//void Speed_Cro_Left(uint16_t percent)
//{
//    uint32_t dutyCycle;
//    dutyCycle = (uint32_t) (((uint64_t) (1000 *percent )) / 100);
//    PWM_setDuty(pwm1, dutyCycle);
//}
//
///*  ���ܣ����ְٷֱȵ���
// *
// */
//void Speed_Cro_Right(uint16_t percent)
//{
//    uint32_t dutyCycle;
//    dutyCycle = (uint32_t) (((uint64_t) (1000 *percent )) / 100);
//    PWM_setDuty(pwm2, dutyCycle);
//}
//
///*  ���ܣ�����PWM���ƣ����ű�ʾǰ�������ű�ʾ����
// *
// */
//void set_PWM_L(int speed)
//{
//  if (speed > 0)
//  {
//      GPIO_write(Left_IN1, 0);  /// ǰ��
//      GPIO_write(Left_IN2, 1);
//  }
//  else
//  {
//      GPIO_write(Left_IN1, 1);  /// ����
//      GPIO_write(Left_IN2, 0);
//  }
//
//  PWM_setDuty(pwm1,  abs(speed));
//}
//
///*  ���ܣ�����=��PWM���ƣ����ű�ʾǰ�������ű�ʾ����
// *
// */
//void set_PWM_R(int speed)
//{
//  if (speed > 0)
//  {
//      GPIO_write(Right_IN1, 0);  /// ǰ��
//      GPIO_write(Right_IN2, 1);
//  }
//  else
//  {
//      GPIO_write(Right_IN1, 1);  /// ����
//      GPIO_write(Right_IN2, 0);
//  }
//
//  PWM_setDuty(pwm2,  abs(speed));
//}
