
/*
 *  ======== main_thread.c ========
 */

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
/* Includes */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include "stdio.h"
#include "string.h"
/* XDC module Headers */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* POSIX Header Files */
#include <semaphore.h>

/* Driver Header Files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/SPI.h>
//#include <ti/display/Display.h>
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
#include <Threads/cameraThread/Inc/camera_thread.h>

#include <Module_files/Button/Inc/Button.h>
#include <Module_files/LED/Inc/LED.h>
#include <Module_files/UART/Inc/UART.h>
#include <Module_files/SPI/Inc/SPI.h>
#include <Module_files/Others/Inc/Others.h>
#include <Module_files/DataPackage/Inc/DataPackage.h>
#include <Module_files/OLED_HSPI/Inc/HSPI.h>
#include <Module_files/Host/Inc/Host.h>
#include <Module_files/I2C/Inc/I2C.h>
#include "Module_files/Ganwei/Inc/Ganwei.h"
#include "Module_files/PID/Inc/PID.h"

/* Global Variables */

extern uint8_t Rangbuff[9];
pthread_t mainthread_handler;

uint8_t data;
/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{

    /*********** IO 口上拉 ************/
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P3, GPIO_PIN7);      /// P3.7（UART1 RX） 上拉
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P9, GPIO_PIN6);      /// P3.0（PCUART RX） 上拉
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P3, GPIO_PIN2);      /// P3.2（I2C1 SDA） 上拉
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN7);      /// P2.7（I2C1 SCL） 上拉
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P6, GPIO_PIN4);      /// P6.4（I2C2 SDA） 上拉
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P6, GPIO_PIN5);      /// P6.5（I2C2 SCL） 上拉
    /**********************************/

    /*********** 初始化 ************/
    GPIO_init();
    Button_INIT();
    Led_INIT();
    UART_INIT();
    SPI_INIT();
    Host_INIT();
    LCD_Init();
    I2C_INIT();
    LCD_ShowString(100, 0, (uint8_t *)"Booting", RED, WHITE, 16, 0);

//    I2CSlave_INIT();
    /*******************************/


    /*********** 赋初值 ************/

//    i2cstatus=true;
    int i;
    for(i=0;i<8;i++)
    {
        GrayB[i]=0x55;
    }
    for(i=0;i<8;i++)
    {
        GrayW[i]=0xaa;
    }
    for(i=0;i<8;i++)
    {
        ANA_Min[i]=255;
        ANA_Max[i]=0;
    }


//    param1=Trace_PID.kp=4.96;
//    param1=Trace_PID.kp=2;                    /// Basic=40
    param1=Trace_PID.kp=5.21;                    /// Basic=40
    param2=Trace_PID.ki=0;
    param3=Trace_PID.kd=0.05;

//    TracePro_PID.kp=5.20;
    TracePro_PID.kp=3;
    TracePro_PID.ki=0;
    TracePro_PID.kd=0;
    TracePro_PID.PIDnum=0;
    pidS=PID_OFF;                    /// 开启直线PID，关闭弯道PID
    PropidS=PID_OFF;
    PID_TurnOn();
    Car=Car_Stop;
    Mode=Free_MODE;

    Mode_Change=IS_Change;
    Car_Change=IS_Change;
    ALLPolling=0;

    /*******************************/

    /********** PING  ***************/
    Ping_STM32();
    Ganwei_INIT();
    Ping_Camera();

    /*******************************/

    /********** DEINIT  ***************/
    UART3_DEINIT();
    I2C1_DEINIT();
//    Read_Camera();                  /// 开启读取摄像头数据
//    Camera_DATA(CameData , CameDataLen);
    /*********************************/

    /*********** UART1 读取距离 ************/
    UART_write(uartHandle1, Rangbuff, 9);           /// 发送距离读取请求
    UART_read(uartHandle1, Disbuff, 9);             /// 读取距离
    Rang=Rang_On;

    /*********************************/

    while (1)
    {
        int retc;
        retc = sem_trywait(&semUART32S);
        if (retc == 0)
        {
            LCD_ShowString(50, 17, (uint8_t *)"STM32 Ping SUCCESS", RED, WHITE, 16, 0);
            while(1)
            {
                retc = sem_trywait(&semGW);
                if(retc==0)
                {
                    LCD_ShowString(50, 34, (uint8_t *)"Ganwei Ping SUCCESS", RED, WHITE, 16, 0);
                    while(1)
                    {
                        retc = sem_trywait(&semCA);
                        if(retc==0)
                        {
                            LCD_ShowString(50, 51, (uint8_t *)"Camera Ping SUCCESS", RED, WHITE, 16, 0);
                            sem_post(&semPCW);
                            sem_post(&semPCR);
                            ALLPolling=1;
                            break;
                        }
                    }
                    break;
                }

            }
            break;
        }
//        msleep(100);

    }
    return NULL;

}



