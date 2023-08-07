/*
 *	File_Name:uart_thread.h
 *	Author:������
 *	Date:2023��7��14��
 *	Declaration:δ��������ֹ������ҵ��;
 */

/* POSIX Header files */
#include <pthread.h>
#include <mqueue.h>
#include <semaphore.h>


#ifndef THREADS_UARTTHREAD_INC_UART_THREAD_H_
#define THREADS_UARTTHREAD_INC_UART_THREAD_H_

#ifdef __cplusplus
extern "C" {
#endif




/* Macro Declaration */



/* Variable Declaration */
extern pthread_t           uartthread_handler;
extern sem_t semUART;
typedef enum RANG
{
    Rang_Off=0,
    Rang_On=1
}RANG;
RANG Rang;
//����ΪPC �������ӿ�ʱ
//extern sem_t semUART1W;

//����ΪOpenMV �ӿ�ʱ
//extern uint8_t WMV;
//uint8_t RMV;

//���봫����
uint8_t Disbuff[9];
uint16_t Dis;           /// �洢������ľ���
/* Function Declaration */
extern void *uartThread(void *arg0);



#ifdef __cplusplus
}
#endif

#endif /* THREADS_UARTTHREAD_INC_UART_THREAD_H_ */
