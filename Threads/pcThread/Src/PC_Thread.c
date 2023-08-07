/*
 *	File_Name:PC_Draw.c
 *	Author:������
 *	Date:2023��7��17��
 *	Declaration:δ��������ֹ������ҵ��;
 */
/* Includes */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
//#include "stdio.h"
#include "string.h"
/* XDC module Headers */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* POSIX Header Files */
#include <semaphore.h>

/* Driver Header Files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>

/* Board Header file */
#include "ti_drivers_config.h"

/* User Header Files */
#include "callbacks.h"
//#include "led_thread.h"
#include <Threads/callbackThread/Inc/callbacks.h>
#include <Threads/mainThread/Inc/main_thread.h>
#include <Threads/uartThread/Inc/uart_thread.h>
#include <Threads/pcThread/Inc/PC_thread.h>
#include <Threads/uart32Thread/Inc/uart32_thread.h>
#include <Threads/lcdThread/Inc/lcd_thread.h>

#include <Module_files/Button/Inc/Button.h>
#include <Module_files/LED/Inc/LED.h>
#include <Module_files/UART/Inc/UART.h>
#include <Module_files/Others/Inc/Others.h>
#include "Module_files/Ganwei/Inc/Ganwei.h"
//#include "Module_files/lwprintf/src/include/lwprintf/lwprintf_opts_template.h"
#include "Module_files/printf_master/Inc/printf.h"
//#include "Module_files/printf_master/Src/printf.c"
//#include "Module_files/printf_master/Inc/printf.c"

//#include "Module_files/format/lib/printf.h"
/* Global Variables */
sem_t semPCW,semPCR;
pthread_t pcthread_handler;

/*
 *  ======== pcThread ========
 */
/*  Note:
 *  �����Է��͵����ݸ�ʽ��"A5,float,float,float,5A"
 *  ���յ��Դ��������ݸ�ʽ��"A5 float float float 5A"
 */

/*======= sprintf(databuff,"A5,%7.2f,%7.2f,%7.2f,5A\r\n",f[0],f[1],f[2]) =====
 *  ���͵�float��ʽ��"+/-3λ����.2λС��"��'�Ҷ��루���ո�"  ��ӦDataLen=31(������������Ӧ23 )
 */
void *pcThread(void *arg0)
{

    int retc;
    while (1)
    {
        /************** PC���ݿ��ӻ���PCԶ�̵���*********************/
        retc = sem_trywait(&semPCW);
        if (retc == 0)
        {
//            memset(Databuff,0,sizeof(Databuff));
//            sprintf(Databuff,"A5,%7.2f,%7.2f,%7.2f,5A\r\n",Dataf[0],Dataf[1],Dataf[2]);
            snprintf(Databuff, DataLen+1 , "A5,%7.2f,%7.2f,5A\r\n", Dataf[0],Dataf[1]);
            UART_write(uartHandle2, Databuff, DataLen);
//            snprintf(Databuff, DataLen+1 , "A5,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,5A\r\n", ANA[0],ANA[1],ANA[2],ANA[3],ANA[4],ANA[5],ANA[6],ANA[7]);
//            UART_write(uartHandle2, Databuff, DataLen);
//            UART_write(uartHandle2, ANA, 8);

        }
        retc = sem_trywait(&semPCR);
        if (retc == 0)
        {
            if(Parambuff[0]=='A'&&Parambuff[1]=='5')     /// ��ͷ��ȷ
            {
                char * end;
                paramn1=strtof(Parambuff+2,&end);
                paramn2=strtof(end,&end);
                paramn3=strtof(end,&end);
                if((*(end+1)=='5')&&(*(end+2)=='A'))         /// ��β��ȷ
                {
                    if((param1!=paramn1)||(param2!=paramn2)||(param3!=paramn3))
                    {
                        param1=paramn1;                      /// ��������
                        param2=paramn2;
                        param3=paramn3;
                        LED_startBlinking(ledHandle3, 100, 2);
                    }
                }
            }
            UART_read(uartHandle2, Parambuff, ParamLen);
        }

        msleep(30);
        /**************************************************************/


       /************************* ���ݼ�� ***************************/
//        retc = sem_trywait(&semPCW);
//        if (retc == 0)
//        {
////            UART_write(uartHandle2,Disbuff,9);
//            UART_write(uartHandle2,LED_Buff,6);
//        }
        /***************************************************************/


//         /*********************** ��STM32�����ݻش���PC ****************/
//        retc = sem_wait(&semPCW);
//        if (retc == 0)
//        {
//            retc = sem_wait(&semUART32PC);
//            if (retc == 0)
//            {
//                UART_write(uartHandle2,STM2RX_BUF,1);
//                UART_read(uartHandle3, STM2RX_BUF, 1);
//            }
//
//        }
//        /***************************************************************/

        /*********************** ��OpenMV�����ݻش���PC ****************/
//       retc = sem_wait(&semPCW);
//       if (retc == 0)
//       {
//
//              UART_write(uartHandle2,&RMV,1);
//
//       }
       /***************************************************************/

    }



}




