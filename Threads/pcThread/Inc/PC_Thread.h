/*
 *	File_Name:PC_Draw.h
 *	Author:������
 *	Date:2023��7��17��
 *	Declaration:δ��������ֹ������ҵ��;
 */

/* POSIX Header files */
#include <pthread.h>

#ifndef THREADS_PCTHREAD_INC_PC_THREAD_H_
#define THREADS_PCTHREAD_INC_PC_THREAD_H_

#ifdef __cplusplus
extern "C" {
#endif
/* Macro Define */
#define DataLen 31          /// �������ݰ�����
#define ParamLen 31         /// ���ղ���������

/* Variable Declaration */
extern pthread_t           pcthread_handler;
extern sem_t semPCW,semPCR;
char Databuff[DataLen],Parambuff[ParamLen];             /// �������ݰ��ͽ��ղ�����
float Dataf[3];                                         /// �������ݰ��еĸ�����
float param1,param2,param3,paramn1,paramn2,paramn3;     /// ����
/* Function Declaration */
extern void *pcThread(void *arg0);


#endif /* THREADS_PCTHREAD_INC_PC_THREAD_H_ */
