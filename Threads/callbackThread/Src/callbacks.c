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
 *  ======== callbacks.c ========
 */
/* Includes */
#include <stdbool.h>
#include <stdlib.h>

/* POSIX Header files */
#include <semaphore.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/PWM.h>
#include <ti/drivers/Timer.h>

/* Board Header file */
#include "ti_drivers_config.h"

/* Thread Header files */
#include <Threads/callbackThread/Inc/callbacks.h>
#include <Threads/mainThread/Inc/main_thread.h>
#include <Threads/uartThread/Inc/uart_thread.h>
#include <Threads/pcThread/Inc/PC_thread.h>
#include <Threads/uart32Thread/Inc/uart32_thread.h>
#include <Threads/lcdThread/Inc/lcd_thread.h>
#include <Threads/cameraThread/Inc/camera_thread.h>

#include <Module_files/Button/Inc/Button.h>
#include <Module_files/LED/Inc/LED.h>
#include <Module_files/DataPackage/Inc/DataPackage.h>
#include <Module_files/UART/Inc/UART.h>
#include <Module_files/I2C/Inc/I2C.h>
#include <Module_files/Others/Inc/Others.h>
/*========= WriteUART1_Callback() ========
 *  UART1 的写回调,征用为 PC调试器时使用
 */
//void WriteUART1_Callback (UART_Handle handle,void *buf,size_t count)
//{
//    int rc;
//    rc = sem_post(&semUART1W);                            /// 释放信号
//    if (rc == -1)
//    {
//        while (1);
//    }
//}


/*========= ReadUART1_Callback() ========
 *  UART1 的读回调
 *  发送一次读取命令后开启读取，读取完成后释放semUART，重复此过程
 */
void ReadUART1_Callback (UART_Handle handle,void *buf,size_t count)
{
    int rc;
    rc = sem_post(&semUART);                            /// 释放信号
    if (rc == -1)
    {
        while (1);
    }
}

/*========= ReadUART2_Callback() ========
 *  UART2 的读回调
 */
void ReadUART2_Callback (UART_Handle handle,void *buf,size_t count)
{
    int rc;
    rc = sem_post(&semPCR);                            /// 释放信号
    if (rc == -1)
    {
        while (1);
    }
}

/*========= WriteUART2_Callback() ========
 *  UART2 的写回调
 */
void WriteUART2_Callback (UART_Handle handle,void *buf,size_t count)
{
    int rc;
    rc = sem_post(&semPCW);                            /// 释放信号
    if (rc == -1)
    {
        while (1);
    }
}


/*========= ReadUART3_Callback() ========
 *  UART3 的读回调
 *  读取到开始信号（0X12）后释放 semUART32S，此外每读取一次释放一次 semUART32
 */
void ReadUART3_Callback (UART_Handle handle,void *buf,size_t count)
{
//    int rc;
//    if(STM2RX_BUF==0x66)                                /// STM32准备好接收数据
//    {
//        rc = sem_post(&semUART32S);                             /// 释放信号
//        if (rc == -1)
//        {
//            while (1);
//        }
//    }
//    else if(STM2RX_BUF[0]==0x11)                                 /// 位置环执行完毕
//    {
//        rc = sem_post(&semUART32);                              /// 释放信号
//        if (rc == -1)
//        {
//            while (1);
//        }
//    }
    int rc;
    rc = sem_post(&semUART32);                              /// 释放信号
    if (rc == -1)
    {
        while (1);
    }

}

/*======== I2C_CallBackFxn() =================
 * 功能：I2C的回调函数
 * 当i2cstatus为true时，工作在写状态；i2cstatus为false时，工作在读状态
 *
 */
void I2C_CallBackFxn(I2C_Handle handle, I2C_Transaction *msg, bool status)
{

    /************** 写->读->写........***************/
//    if (status == false)
//    {
//        while(1);
//    }
//    else
//    {
//        if(i2cstatus)
//        {
//            sem_post(&semi2cRE);
//
//        }
//        else
//        {
//
//            sem_post(&semi2cWR);
//        }
//    }
    /***********************************************/


   /*************** 不断读 ************************/
    sem_post(&semi2cRE);
    /**********************************************/
}

///*======== I2CSlaveCallBackFxn() =================
// * 功能：I2CSlave的回调函数
// */
//
//void I2CSlaveCallBackFxn(I2CSlave_Handle handle, bool status)
//{
//    int rc;
//    rc = sem_post(&semi2cslave);                              /// 释放信号
//    if (rc == -1)
//    {
//        while (1);
//    }
//}

