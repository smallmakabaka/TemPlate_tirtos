/************************************
File_Name:Motor.c
Date:2023��7��11��
Author:������
Declaration:δ��������ֹ������ҵ��;
*************************************/
/* Header files */
#include "Motor.h"

/*  ���ܣ������ʼ��
 *  ǰ����01
 *  ���ˣ�10
 */
void Motor_INIT()
{
    GPIO_write(Left_IN1, 0);    /// ǰ��
    GPIO_write(Left_IN2, 1);
    GPIO_write(Right_IN1, 0);
    GPIO_write(Right_IN2, 1);
}





