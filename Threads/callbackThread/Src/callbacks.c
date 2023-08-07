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
 *  UART1 ��д�ص�,����Ϊ PC������ʱʹ��
 */
//void WriteUART1_Callback (UART_Handle handle,void *buf,size_t count)
//{
//    int rc;
//    rc = sem_post(&semUART1W);                            /// �ͷ��ź�
//    if (rc == -1)
//    {
//        while (1);
//    }
//}


/*========= ReadUART1_Callback() ========
 *  UART1 �Ķ��ص�
 *  ����һ�ζ�ȡ���������ȡ����ȡ��ɺ��ͷ�semUART���ظ��˹���
 */
void ReadUART1_Callback (UART_Handle handle,void *buf,size_t count)
{
    int rc;
    rc = sem_post(&semUART);                            /// �ͷ��ź�
    if (rc == -1)
    {
        while (1);
    }
}

/*========= ReadUART2_Callback() ========
 *  UART2 �Ķ��ص�
 */
void ReadUART2_Callback (UART_Handle handle,void *buf,size_t count)
{
    int rc;
    rc = sem_post(&semPCR);                            /// �ͷ��ź�
    if (rc == -1)
    {
        while (1);
    }
}

/*========= WriteUART2_Callback() ========
 *  UART2 ��д�ص�
 */
void WriteUART2_Callback (UART_Handle handle,void *buf,size_t count)
{
    int rc;
    rc = sem_post(&semPCW);                            /// �ͷ��ź�
    if (rc == -1)
    {
        while (1);
    }
}


/*========= ReadUART3_Callback() ========
 *  UART3 �Ķ��ص�
 *  ��ȡ����ʼ�źţ�0X12�����ͷ� semUART32S������ÿ��ȡһ���ͷ�һ�� semUART32
 */
void ReadUART3_Callback (UART_Handle handle,void *buf,size_t count)
{
//    int rc;
//    if(STM2RX_BUF==0x66)                                /// STM32׼���ý�������
//    {
//        rc = sem_post(&semUART32S);                             /// �ͷ��ź�
//        if (rc == -1)
//        {
//            while (1);
//        }
//    }
//    else if(STM2RX_BUF[0]==0x11)                                 /// λ�û�ִ�����
//    {
//        rc = sem_post(&semUART32);                              /// �ͷ��ź�
//        if (rc == -1)
//        {
//            while (1);
//        }
//    }
    int rc;
    rc = sem_post(&semUART32);                              /// �ͷ��ź�
    if (rc == -1)
    {
        while (1);
    }

}

/*======== I2C_CallBackFxn() =================
 * ���ܣ�I2C�Ļص�����
 * ��i2cstatusΪtrueʱ��������д״̬��i2cstatusΪfalseʱ�������ڶ�״̬
 *
 */
void I2C_CallBackFxn(I2C_Handle handle, I2C_Transaction *msg, bool status)
{

    /************** д->��->д........***************/
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


   /*************** ���϶� ************************/
    sem_post(&semi2cRE);
    /**********************************************/
}

///*======== I2CSlaveCallBackFxn() =================
// * ���ܣ�I2CSlave�Ļص�����
// */
//
//void I2CSlaveCallBackFxn(I2CSlave_Handle handle, bool status)
//{
//    int rc;
//    rc = sem_post(&semi2cslave);                              /// �ͷ��ź�
//    if (rc == -1)
//    {
//        while (1);
//    }
//}

