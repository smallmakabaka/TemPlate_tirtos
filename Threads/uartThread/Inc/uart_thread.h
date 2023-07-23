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

/* 消息类型 */
typedef struct UartMsg {
    void *buffer;
} UartMsg;

/* Macro Declaration */



/* Variable Declaration */
extern pthread_t           uartthread_handler;
extern sem_t semUART , semUART1W;
extern mqd_t  mqUART;
extern uint8_t WMV;
uint8_t RMV;


/* Function Declaration */
extern void *uartThread(void *arg0);



#ifdef __cplusplus
}
#endif

#endif /* THREADS_UARTTHREAD_INC_UART_THREAD_H_ */
