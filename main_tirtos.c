/*
 * Copyright (c) 2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== main_tirtos.c ========
 */
/* Includes */
#include <stdint.h>

/* POSIX Header Files */
#include <pthread.h>

/* RTOS Header Files */
#include <ti/sysbios/BIOS.h>

/* Example/Board Header Files */
#include <ti/drivers/Board.h>

/* Thread Header files */
#include <Threads/callbackThread/Inc/callbacks.h>
#include <Threads/ledThread/Inc/led_thread.h>
#include <Threads/mainThread/Inc/main_thread.h>
#include <Threads/uartThread/Inc/uart_thread.h>
#include <Threads/pcThread/Inc/PC_thread.h>
#include <Threads/uart32Thread/Inc/uart32_thread.h>
/* Stack size in bytes */
#define THREADSTACKSIZE    1024

/*
 *  ======== main ========
 */
int main(void)
{
    /********** 线程变量定义 ***********/
    pthread_attr_t      pAttrs;             /// 线程属性
    struct sched_param  priParam;           /// 线程参数
    struct mq_attr      attr;               /// 消息属性
    int                 retc;               /// 保存返回值用于检测
    int                 detachState;        /// 线程分离状态
    /***********************************/
    /* Call driver init functions */
    Board_init();

    /************生成消息队列***********/
    /*=======mq_open()=========/
     *  功能：创建一个消息队列
     *  Params
     *  name:消息队列标识符，加下斜杠表示指向已经存在的相同队列
     *  oflag:O_RDONLY（只读）、O_WRONLY（只写）、O_RDWR（读写）
     *        O_CREAT（创造一个空的消息队列、O_NONBLOCK（接收消息非阻塞）
     */
    attr.mq_maxmsg = LED_MSG_NUM;               /// 消息队列的最大数量
    attr.mq_msgsize = LED_MSG_SIZE;             /// 消息的最大Size
    attr.mq_flags = 0;                          /// 0 or O_NONBLOCK
    mqUART = mq_open("uart", O_RDWR | O_CREAT | O_NONBLOCK, 0664, &attr);
    if (mqLED == (mqd_t)-1)
    {
        while (1);
    }
    /***********************************/


    /************生成信号***************/
    /*=======sem_init()=========/
     *  功能:初始化无名信号量
     *  Params:
     *  sem:信号标识符
     *  pshared:0 表示不在进程之间共享
     *  value:信号的初始值
     */
    retc = sem_init(&semUART, 0, 0);
    if (retc == -1)
    {
        while (1);
    }

    retc = sem_init(&semUART1W, 0, 0);
    if (retc == -1)
    {
        while (1);
    }

    retc = sem_init(&semPCW, 0, 0);
    if (retc == -1)
    {
        while (1);
    }

    retc = sem_init(&semPCR, 0, 0);
    if (retc == -1)
    {
        while (1);
    }

    retc = sem_init(&semUART32, 0, 1);
    if (retc == -1)
    {
        while (1);
    }

    retc = sem_init(&semUART32S, 0, 0);
    if (retc == -1)
    {
        while (1);
    }
    retc = sem_init(&semUART32PC, 0, 0);
    if (retc == -1)
    {
        while (1);
    }
    /***********************************/

    /***********生成线程****************/
    pthread_attr_init(&pAttrs);
    priParam.sched_priority = 1;                                    /// 线程优先级
    detachState = PTHREAD_CREATE_DETACHED;
    retc = pthread_attr_setdetachstate(&pAttrs, detachState);       /// 设置线程分离
    if (retc != 0)
    {
        while (1);
    }
    pthread_attr_setschedparam(&pAttrs, &priParam);
    retc |= pthread_attr_setstacksize(&pAttrs, THREADSTACKSIZE);        /// 设置栈大小
    if (retc != 0)
    {
        while (1);
    }
    retc = pthread_create(&ledthread_handler, &pAttrs, ledThread, NULL);
    if (retc != 0)
    {
        while (1);
    }

    /*
     * ==========第二个线程==========
     */
    priParam.sched_priority = 2;
    pthread_attr_setschedparam(&pAttrs, &priParam);
    retc = pthread_create(&pcthread_handler, &pAttrs, pcThread, NULL);  /// PC调试线程
    if (retc != 0)
    {
        while (1);
    }

    /*
     * =========第三个线程===========
     */
    priParam.sched_priority = 3;
    pthread_attr_setschedparam(&pAttrs, &priParam);
    retc = pthread_create(&uartthread_handler, &pAttrs, uartThread, NULL);  /// UART线程，激光传感器
    if (retc != 0)
    {
        while (1);
    }


    /*
     * =========第四个线程===========
     */

    priParam.sched_priority = 4;
    pthread_attr_setschedparam(&pAttrs, &priParam);
    retc = pthread_create(&uart32thread_handler, &pAttrs, uart32Thread, NULL);  /// 与32通信的线程
    if (retc != 0)
    {
        while (1);
    }
    /*
     * =========第五个线程===========
     */
    priParam.sched_priority = 5;
    pthread_attr_setschedparam(&pAttrs, &priParam);
    retc = pthread_create(&mainthread_handler, &pAttrs, mainThread, NULL);  /// 主线程
    if (retc != 0)
    {
        while (1);
    }
    /************************************/

    BIOS_start();                               /// 启动

    return (0);
}
