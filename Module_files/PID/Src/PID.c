/************************************
File_Name:PID.c
Date:2023��7��11��
Author:������
Declaration:δ��������ֹ������ҵ��;
*************************************/

/* Header files */
#include "Module_files/PID/Inc/PID.h"


/// ���׵���ɢλ��ʽ PID
float Position_PID(float error,_PID pid)//errorΪ����ƫ��
{
    float Position_KP=pid.kp,Position_KI=pid.ki,Position_KD=pid.kd;
    float Error_Current , pid_out;
    Error_Current=error;                                                //���㵱ǰ��ƫ��ֵ
    Integral_error+=Error_Current;                                      //���ƫ��Ļ���
    pid_out=Position_KP*Error_Current+Position_KI*Integral_error+Position_KD*(Error_Current-Error_Last); //λ��ʽPID������
    Error_Last=Error_Current;                                          //������һ��ƫ��
    pid_out=(pid_out>30)?30:pid_out;                                    // ����޷�
    pid_out=(pid_out<-30)?-30:pid_out;
    return pid_out;
}
