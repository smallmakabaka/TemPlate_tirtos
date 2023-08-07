/*
 *	File_Name:uart_thread.h
 *	Author:胡尔勤
 *	Date:2023年7月14日
 *	Declaration:未经允许，禁止用于商业用途
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
//征用为PC 调试器接口时
//extern sem_t semUART1W;

//征用为OpenMV 接口时
//extern uint8_t WMV;
//uint8_t RMV;

//距离传感器
uint8_t Disbuff[9];
uint16_t Dis;           /// 存储计算出的距离
/* Function Declaration */
extern void *uartThread(void *arg0);



#ifdef __cplusplus
}
#endif

#endif /* THREADS_UARTTHREAD_INC_UART_THREAD_H_ */
