/*
 *	File_Name:PC_Draw.h
 *	Author:胡尔勤
 *	Date:2023年7月17日
 *	Declaration:未经允许，禁止用于商业用途
 */

/* POSIX Header files */
#include <pthread.h>

#ifndef THREADS_PCTHREAD_INC_PC_THREAD_H_
#define THREADS_PCTHREAD_INC_PC_THREAD_H_

#ifdef __cplusplus
extern "C" {
#endif
/* Macro Define */
#define DataLen 31          /// 发送数据包长度
#define ParamLen 31         /// 接收参数包长度

/* Variable Declaration */
extern pthread_t           pcthread_handler;
extern sem_t semPCW,semPCR;
char Databuff[DataLen],Parambuff[ParamLen];             /// 发送数据包和接收参数包
float Dataf[3];                                         /// 发送数据包中的浮点数
float param1,param2,param3,paramn1,paramn2,paramn3;     /// 参数
/* Function Declaration */
extern void *pcThread(void *arg0);


#endif /* THREADS_PCTHREAD_INC_PC_THREAD_H_ */
