/*
 *	File_Name:uart_thread.c
 *	Author:������
 *	Date:2023��7��14��
 *	Declaration:δ��������ֹ������ҵ��;
 */

/* Includes */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>

/* POSIX Header Files */
#include <semaphore.h>
#include <mqueue.h>
#include <semaphore.h>

/* Driver Header Files */
#include <ti/drivers/GPIO.h>


/* Board Header file */
#include "ti_drivers_config.h"

/* Thread Header files */
#include <Threads/callbackThread/Inc/callbacks.h>
#include <Threads/mainThread/Inc/main_thread.h>
#include <Threads/uartThread/Inc/uart_thread.h>
#include <Threads/uart32Thread/Inc/uart32_thread.h>
#include <Threads/lcdThread/Inc/lcd_thread.h>

/* Module Header files */
#include <Module_files/Button/Inc/Button.h>
#include <Module_files/LED/Inc/LED.h>
#include <Module_files/UART/Inc/UART.h>
#include <Module_files/DataPackage/Inc/DaTaPackage.h>
#include <Module_files/Others/Inc/Others.h>
#include <Threads/lcdThread/Inc/lcd_thread.h>
/* Global Variables */
pthread_t uartthread_handler;
sem_t semUART ;

// ����Ϊ PC ������ʱ
//sem_t semUART1W;

/// ����ΪOpenMV �ӿ�ʱ
//uint8_t WMV=0x5A;

// ���봫����
uint8_t Rangbuff[9]={0x62,0x33,0x09,0xFF,0xFF,0x00,0x00,0x00,0x58};

void *uartThread(void *arg0)
{
    /******************* UART1 ���ڼ��⴫����ʱ ********************/
    int retc;
    while (1)
    {
        retc = sem_wait(&semUART);
        if (retc == 0)
        {
            if((Disbuff[0]==0x62)&&(Disbuff[1]==0x33))        /// ������Ӧ����
            {
                Dis=Disbuff[5]*256+Disbuff[6];               /// ���룬��λmm
            }

           UART_write(uartHandle1, Rangbuff, 9);           /// ���;�������
           UART_read(uartHandle1, Disbuff, 9);             /// ��ȡ��������
        }
        msleep(100);
    }
    /***************************************************************/

//    /******************* UART1 ��ʱ����ΪPC������ʱ ********************/
//    int retc;
//    while (1)
//    {
//        retc = sem_wait(&semUART1W);
//        if (retc == 0)
//        {
//            LED_Buff[0]=L2+48;
//            LED_Buff[1]=L1+48;
//            LED_Buff[2]=M+48;
//            LED_Buff[3]=R1+48;
//            LED_Buff[4]=R2+48;
//            LED_Buff[5]=0x0A;
//
//            UART_write(uartHandle1, LED_Buff, 6);               /// ��ȡ��������
//            msleep(5);
//        }
//    }
//    /***************************************************************/


    /******************* UART1 ��ʱ����ΪOpenMV�ӿ�ʱ ********************/
//    int retc;
//    while (1)
//    {
//        retc = sem_wait(&semUART);
//        if (retc == 0)
//        {
//            if(RMV==0xA5)
//            {
//                int rc;
//                rc = sem_post(&semUART1W);                            /// �ͷ��ź�
//                if (rc == -1)
//                {
//                    while (1);
//                }
//            }
//            else
//            {
//                UART_read(uartHandle1, &RMV, 1);
//            }
//        }
//    }
    /***************************************************************/
}

