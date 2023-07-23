/*
 *	File_Name:uart32_thread.h
 *	Author:胡尔勤
 *	Date:2023年7月20日
 *	Declaration:未经允许，禁止用于商业用途
 */

#ifndef THREADS_UART32THREAD_INC_UART32_THREAD_H_
#define THREADS_UART32THREAD_INC_UART32_THREAD_H_

/* Structure Define */
typedef enum wheel
{
    FR=1,           /// 前右轮
    FL=2,           /// 前左轮
    BR=3,           /// 后右轮
    BL=4            /// 后左轮
}wheel;

typedef enum wheelmode
{
    position=1,     /// 位置环
    speed=2,        /// 速度环
    pwm=3           /// 设置PWM
}wheelmode;
/* Macro Declaration */
#define TX2STM_LEN 20 //数据包大小

/* Variable Declaration */
extern pthread_t           uart32thread_handler;
extern sem_t semUART32 , semUART32S , semUART32PC;
uint8_t TX2STM_BUF[TX2STM_LEN];  //数据包缓存区
uint8_t STM2RX_BUF[1];  //数据包缓存区

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
