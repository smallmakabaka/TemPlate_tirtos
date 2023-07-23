/************************************
File_Name:Timer32.c
Date:2023��7��11��
Author:������
Declaration:δ��������ֹ������ҵ��;
*************************************/

/* Header files */
#include "Timer32.h"


/*  ���ܣ�Timer32��ʼ��
 *  ��ʱģʽ��
 *  Timer_ONESHOT_CALLBACK��������һ���жϣ�������;
 *  Timer_CONTINUOUS_CALLBACK�����������жϣ�������;
 *  Timer_ONESHOT_BLOCKING��������һ���жϣ�����;
 *  Timer_FREE_RUNNING���������жϣ���������һֱ���е�����Timer_stop();
 */
void Timer32_INIT()
{
    Timer_init();
    Timer_Params_init(&timer32params);
    timer32params.periodUnits = Timer_PERIOD_US;            /// ���ڵ�λ
    timer32params.period = 30000000;                        /// ���ڴ�С
    timer32params.timerMode  = Timer_ONESHOT_CALLBACK;      /// ��ʱģʽ
    timer32params.timerCallback = Timer32_CallBackFxn;      /// �ص�����
    timer32handle = Timer_open(Timer32, &timer32params);    /// �򿪶�ʱ��
//    timer32status = Timer_start(timer32handle);             /// ��ʱ����ʼ����
//    if (timer32status ==Timer_STATUS_ERROR)                 /// �������ʧ��
//    {
//        while (1);
//    }

}

/*  ���ܣ�Timer32�Ļص�����
 *
 */
void Timer32_CallBackFxn(Timer_Handle handle)
{

}

