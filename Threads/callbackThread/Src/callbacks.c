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
#include <Threads/ledThread/Inc/led_thread.h>
#include <Threads/mainThread/Inc/main_thread.h>
#include <Threads/uartThread/Inc/uart_thread.h>
#include <Threads/pcThread/Inc/PC_thread.h>
#include <Threads/uart32Thread/Inc/uart32_thread.h>

#include <Module_files/Button/Inc/Button.h>
#include <Module_files/LED/Inc/LED.h>
#include <Module_files/DataPackage/Inc/DataPackage.h>
#include <Module_files/UART/Inc/UART.h>

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
 */
void ReadUART1_Callback (UART_Handle handle,void *buf,size_t count)
{
    int rc;
    rc = sem_post(&semUART);                            /// �ͷ��ź�
    if (rc == -1)
    {
        while (1);
    }
//    UART_writeCancel(uartHandle1);      /// ֹͣд
//    UART_readCancel(uartHandle1);       /// ֹͣ��
//    UART_close(uartHandle1);            /// �رմ���1
//    read_status=1;
//    close_status=1;
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
 */
void ReadUART3_Callback (UART_Handle handle,void *buf,size_t count)
{
    int rc;
    if(STM2RX_BUF[0]==0x12)                                /// STM32׼���ý�������
    {
        rc = sem_post(&semUART32S);                             /// �ͷ��ź�
        if (rc == -1)
        {
            while (1);
        }
    }
    else if(STM2RX_BUF[0]==0x11)                                 /// λ�û�ִ�����
    {
        rc = sem_post(&semUART32);                              /// �ͷ��ź�
        if (rc == -1)
        {
            while (1);
        }
    }
    rc = sem_post(&semUART32PC);                              /// �ͷ��ź�
    if (rc == -1)
    {
        while (1);
    }


}



