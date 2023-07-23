/************************************
File_Name:Timer32.c
Date:2023年7月11日
Author:胡尔勤
Declaration:未经允许，禁止用于商业用途
*************************************/

/* Header files */
#include "Timer32.h"


/*  功能：Timer32初始化
 *  定时模式：
 *  Timer_ONESHOT_CALLBACK：仅生成一次中断，非阻塞;
 *  Timer_CONTINUOUS_CALLBACK：定期生成中断，非阻塞;
 *  Timer_ONESHOT_BLOCKING：仅生成一次中断，阻塞;
 *  Timer_FREE_RUNNING：不生成中断，非阻塞，一直运行到调用Timer_stop();
 */
void Timer32_INIT()
{
    Timer_init();
    Timer_Params_init(&timer32params);
    timer32params.periodUnits = Timer_PERIOD_US;            /// 周期单位
    timer32params.period = 30000000;                        /// 周期大小
    timer32params.timerMode  = Timer_ONESHOT_CALLBACK;      /// 定时模式
    timer32params.timerCallback = Timer32_CallBackFxn;      /// 回调函数
    timer32handle = Timer_open(Timer32, &timer32params);    /// 打开定时器
//    timer32status = Timer_start(timer32handle);             /// 定时器开始工作
//    if (timer32status ==Timer_STATUS_ERROR)                 /// 如果启动失败
//    {
//        while (1);
//    }

}

/*  功能：Timer32的回调函数
 *
 */
void Timer32_CallBackFxn(Timer_Handle handle)
{

}

