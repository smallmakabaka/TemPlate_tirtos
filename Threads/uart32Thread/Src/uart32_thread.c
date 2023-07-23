/*
 *	File_Name:uart32_thread.c
 *	Author:胡尔勤
 *	Date:2023年7月20日
 *	Declaration:未经允许，禁止用于商业用途
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
#include <Threads/ledThread/Inc/led_thread.h>
#include <Threads/mainThread/Inc/main_thread.h>
#include <Threads/uartThread/Inc/uart_thread.h>
#include <Threads/uart32Thread/Inc/uart32_thread.h>



/* Module Header files */
#include <Module_files/Button/Inc/Button.h>
#include <Module_files/LED/Inc/LED.h>
#include <Module_files/UART/Inc/UART.h>
#include <Module_files/DataPackage/Inc/DaTaPackage.h>
#include <Module_files/Others/Inc/Others.h>
/* Global Variables */
pthread_t uart32thread_handler;
sem_t semUART32 , semUART32S , semUART32PC;
mqd_t  mqUART32;


uint8_t SPI2Tx[SPIcount]={0x01,0x02,0x03,0x04,0x05,0x06};
uint8_t SPI2Rx[SPIcount];

void *uart32Thread(void *arg0)
{
    int retc;
    retc = sem_wait(&semUART32S);
    if (retc == 0)
    {
        while(1)
        {
            /************* 开启循迹 **************/
//            Trace();
//            msleep(10);
            /*************************************/
            Treasure();
            msleep(10);

        }
    }
    return NULL;

}

/*=========== Read_Led() =============
 *  功能：读取LED值
 */
void Read_Led()
{

    LED_Buff[0]=GPIO_read(LED_L2)+48;
    LED_Buff[1]=GPIO_read(LED_L1)+48;
    LED_Buff[2]=GPIO_read(LED_M)+48;
    LED_Buff[3]=GPIO_read(LED_R1)+48;
    LED_Buff[4]=GPIO_read(LED_R2)+48;
    LED_Buff[5]=0x0A;

}



/*=========== Trace() =============
 *  功能：灰度传感器循迹
 */
void Trace()
{
    /*********** 读取传感器值 ************/


    L2=GPIO_read(LED_L2);
    L1=GPIO_read(LED_L1);
    M=GPIO_read(LED_M);
    R1=GPIO_read(LED_R1);
    R2=GPIO_read(LED_R2);


    /*********** 执行循迹动作 *************/
    if((L1==Black)&&(M==Black)&&(R1==Black))
    {
        Pack2Stm(speed , 45 , 45 , 45 , 45 , TX2STM_BUF , TX2STM_LEN);
        UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
    }
    else
    {
        if(L1==Black)                               /// 左转
        {

            Pack2Stm(speed , 40 , 10 , 40 , 10 , TX2STM_BUF , TX2STM_LEN);
            UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);

        }
        else if(L2==Black)
        {
            Pack2Stm(speed , 50 , 10 , 50 , 10 , TX2STM_BUF , TX2STM_LEN);
            UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
        }
        else if(R1==Black)                               /// 右转
        {
            Pack2Stm(speed , 10 , 40 , 10 , 40 , TX2STM_BUF , TX2STM_LEN);
            UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);

        }
        else if(R2==Black)                               /// 右转
        {
            Pack2Stm(speed , 10 , 50 , 10 , 50 , TX2STM_BUF , TX2STM_LEN);
            UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
        }
        else if(M==Black)                               /// 直走
        {
            Pack2Stm(speed , 45 , 45 , 45 , 45 , TX2STM_BUF , TX2STM_LEN);
            UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
        }
    }

}


/*=========== Treasure() =============
 *  功能：寻宝
 */
void Treasure()
{
    /*********** 读取传感器值 ************/


    L2=GPIO_read(LED_L2);
    L1=GPIO_read(LED_L1);
    M=GPIO_read(LED_M);
    R1=GPIO_read(LED_R1);
    R2=GPIO_read(LED_R2);

    /*********** 执行循迹动作 *************/
    if(R2==Black)                                       /// 可以右转
    {
        Pack2Stm(pwm , 0 , 0 , 0 , 0 , TX2STM_BUF , TX2STM_LEN);
        UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
        sleep(1);
        Pos(5);                                        /// 向前20
        sleep(1);


        TurnR90();
        msleep(100);
        while(1)
        {
            L1=GPIO_read(LED_L1);
            M=GPIO_read(LED_M);
            R1=GPIO_read(LED_R1);
            if((L1==Black)||(M==Black)||(R1==Black))
            {
                Pack2Stm(pwm , 0 , 0 , 0 , 0 , TX2STM_BUF , TX2STM_LEN);
                UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
                break;
            }
        }

        sleep(1);
        if(L1==Black)                               /// 左转
        {

            Pack2Stm(speed , 40 , 10 , 40 , 10 , TX2STM_BUF , TX2STM_LEN);
            UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);

        }
        else if(R1==Black)                               /// 右转
        {
            Pack2Stm(speed , 10 , 40 , 10 , 40 , TX2STM_BUF , TX2STM_LEN);
            UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);

        }
        else if(M==Black)                               /// 直走
        {
            Pack2Stm(speed , 25 , 25 , 25 , 25 , TX2STM_BUF , TX2STM_LEN);
            UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
        }

    }
    else if(L2==Black)                                  /// 直行或左转
    {
        Pack2Stm(pwm , 0 , 0 , 0 , 0 , TX2STM_BUF , TX2STM_LEN);
        UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
        sleep(1);
        Pos(10);                                        /// 向前20
        sleep(1);
        L2=GPIO_read(LED_L2);
        L1=GPIO_read(LED_L1);
        M=GPIO_read(LED_M);
        R1=GPIO_read(LED_R1);
        R2=GPIO_read(LED_R2);
        if((L1==White)&&(M==White)&&(R1==White))        /// 不能直行
        {
            Pos(-5);                                   /// 向后20
            sleep(1);
            TurnL90();                                  /// 左转

            while(1)
            {
                L1=GPIO_read(LED_L1);
                M=GPIO_read(LED_M);
                R1=GPIO_read(LED_R1);
                if((L1==Black)||(M==Black)||(R1==Black))
                {
                    Pack2Stm(pwm , 0 , 0 , 0 , 0 , TX2STM_BUF , TX2STM_LEN);
                    UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
                    break;

                }
            }

            sleep(1);
            if(L1==Black)                               /// 左转
            {

                Pack2Stm(speed , 40 , 10 , 40 , 10 , TX2STM_BUF , TX2STM_LEN);
                UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);

            }
            else if(R1==Black)                               /// 右转
            {
                Pack2Stm(speed , 10 , 40 , 10 , 40 , TX2STM_BUF , TX2STM_LEN);
                UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);

            }
            else if(M==Black)                               /// 直走
            {
                Pack2Stm(speed , 25 , 25 , 25 , 25 , TX2STM_BUF , TX2STM_LEN);
                UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
            }


        }

    }
    else
    {
        int retc;
        retc = sem_trywait(&semUART1W);
        if (retc == 0)
        {
            Pack2Stm(pwm , 0 , 0 , 0 , 0 , TX2STM_BUF , TX2STM_LEN);
            UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
            sleep(1);
            Turn180();
            sleep(1);           /// 掉头
            UART_write(uartHandle1, &WMV, 1);
            msleep(10);
            UART_read(uartHandle1, &RMV, 1);
        }
        else
        {
            if(L1==Black)                               /// 左转
            {

                Pack2Stm(speed , 40 , 10 , 40 , 10 , TX2STM_BUF , TX2STM_LEN);
                UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);

            }
            else if(R1==Black)                               /// 右转
            {
                Pack2Stm(speed , 10 , 40 , 10 , 40 , TX2STM_BUF , TX2STM_LEN);
                UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);

            }
            else if(M==Black)                               /// 直走
            {
                Pack2Stm(speed , 25 , 25 , 25 , 25 , TX2STM_BUF , TX2STM_LEN);
                UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
            }
            else if((L1==White)&&(M==White)&&(R1==White))
            {
                Pack2Stm(pwm , 0 , 0 , 0 , 0 , TX2STM_BUF , TX2STM_LEN);
                UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
                sleep(1);
                Turn180();
                sleep(1);           /// 掉头
            }
        }
    }

}


/*========= Turn180() =======
 * 功能：转向180°，采用位置环控制各轮的移动距离来实现
 */
void Turn180()
{
//    int retc;
    Pack2Stm(position , 32 , -31 , 32 , -31 , TX2STM_BUF , TX2STM_LEN);
//    retc = sem_wait(&semUART32);
//    if (retc == 0)
//    {
    UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
//    }

}

/*========= TurnL90() =======
 * 功能：左转90°，采用位置环控制各轮的移动距离来实现
 */
void TurnL90()
{
//    int retc;
    Pack2Stm(position , 16.5 , -15.5 , 16.5 , -15.5 , TX2STM_BUF , TX2STM_LEN);
//    retc = sem_wait(&semUART32);
//    if (retc == 0)
//    {
    UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
//    }

}


/*========= TurnR90() =======
 * 功能：右转90°，采用位置环控制各轮的移动距离来实现
 */
void TurnR90()
{
//    int retc;
    Pack2Stm(position , -15.5 , 16.5 , -15.5 , 16.5 , TX2STM_BUF , TX2STM_LEN);
//    retc = sem_wait(&semUART32);
//    if (retc == 0)
//    {
    UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
//    }


}


/*========= Pos() =======
 * 功能：采用位置环控制各轮的移动距离来实现
 */
void Pos(float x)
{
//    int retc;
    Pack2Stm(position , x , x , x , x , TX2STM_BUF , TX2STM_LEN);
//    retc = sem_wait(&semUART32);
//    if (retc == 0)
//    {
    UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
//    }

}




