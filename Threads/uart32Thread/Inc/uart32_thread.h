/*
 *	File_Name:uart32_thread.h
 *	Author:������
 *	Date:2023��7��20��
 *	Declaration:δ����������ֹ������ҵ��;
 */

#ifndef THREADS_UART32THREAD_INC_UART32_THREAD_H_
#define THREADS_UART32THREAD_INC_UART32_THREAD_H_

/* Structure Define */
typedef enum wheel
{
    FR=1,           /// ǰ����
    FL=2,           /// ǰ����
    BR=3,           /// ������
    BL=4            /// ������
}wheel;

typedef enum wheelmode
{
    position=1,     /// λ�û�
    speed=2,        /// �ٶȻ�
    pwm=3           /// ����PWM
}wheelmode;
/* Macro Declaration */
#define TX2STM_LEN 20 //���ݰ���С

/* Variable Declaration */
extern pthread_t           uart32thread_handler;
extern sem_t semUART32 , semUART32S , semUART32PC;
uint8_t TX2STM_BUF[TX2STM_LEN];  //���ݰ�������
uint8_t STM2RX_BUF[1];  //���ݰ�������

wheel w;
wheelmode wm;
float wf;



/* Function Declaration */
extern void *uart32Thread(void *arg0);
void Trace();
void Treasure();
void Read_Led();
void Turn180();
void TurnL90();
void TurnR90();
void Pos(float x);

#endif /* THREADS_UART32THREAD_INC_UART32_THREAD_H_ */