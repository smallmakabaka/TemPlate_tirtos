
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

/* Board Header file */
#include "ti_drivers_config.h"

/* User Header Files */
#include "callbacks.h"
//#include "led_thread.h"
#include <Threads/callbackThread/Inc/callbacks.h>
#include <Threads/ledThread/Inc/led_thread.h>
#include <Threads/mainThread/Inc/main_thread.h>
#include <Threads/uartThread/Inc/uart_thread.h>
#include <Threads/pcThread/Inc/PC_thread.h>
#include <Threads/uart32Thread/Inc/uart32_thread.h>

#include <Module_files/Button/Inc/Button.h>
#include <Module_files/LED/Inc/LED.h>
#include <Module_files/UART/Inc/UART.h>
#include <Module_files/SPI/Inc/SPI.h>
#include <Module_files/Others/Inc/Others.h>
#include <Module_files/DataPackage/Inc/DataPackage.h>
#include <Module_files/OLED_HSPI/Inc/HSPI.h>
/* Global Variables */

uint8_t Rangbuff[9]={0x62,0x33,0x09,0xFF,0xFF,0x00,0x00,0x00,0x58};
pthread_t mainthread_handler;


/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{

    /*********** 初始化 ************/
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P3, GPIO_PIN7);      /// P3.7（UART1 RX） 上拉
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P3, GPIO_PIN0);      /// P3.0（UART2 RX） 上拉
    GPIO_init();
    Button_INIT();
    Led_INIT();
    UART_INIT();
    SPI_INIT();
    LCDTest();
    /*******************************/

    /*********** 赋初值 ************/
    Dataf[0]=-12.1;
    Dataf[1]=30.3;
    Dataf[2]=-51.2;
    w=FR;                           /// 轮子
    wm=position;                    /// 轮子模式
    wf=30;
    /*******************************/

    /********** 上电检测 **************/
    LED_startBlinking(ledHandle2, 100, 2);
    /**********************************/

    /********** 开始与32的通信 ********/
    UART_read(uartHandle3, STM2RX_BUF, 1);
    /**********************************/

    /*********** UART1 读取距离 ************/
//    UART_write(uartHandle1, Rangbuff, 9);           /// 发送距离读取请求
//    UART_read(uartHandle1, Disbuff, 9);             /// 读取距离
    /*********************************/

    /*********** UART1 征用为OpenMV接口时****/
    UART_read(uartHandle1, &RMV, 1);
    /***************************************/
    /*
     * 发起PC端调试
     */
    /******************************************************************/
    /************** PC数据可视化，远程调试***************************/
//    memset(Databuff,0,sizeof(Databuff));
//    sprintf(Databuff,"A5,%7.2f,%7.2f,%7.2f,5A\r\n",Dataf[0],Dataf[1],Dataf[2]);
//    UART_write(uartHandle2, Databuff, DataLen);
//    UART_read(uartHandle2,Parambuff,ParamLen);

    /************* 将LED传感器的信息发送到PC ************************/
//    UART_write(uartHandle2,LED_Buff,6);

    /************* 将从STM32接收的信息发送到PC ************************/

    UART_write(uartHandle2,&RMV,1);

    /*****************************************************************/

    /******************* 左右转向定角测试 ***************************/

    /****************************************************************/
    while (1)
    {

        sleep(1);

//        spiTransaction2.count = SPIcount;
//        spiTransaction2.txBuf = SPI2Tx;
//        spiTransaction2.rxBuf = SPI2Rx;
//        transferOK2 = SPI_transfer(spihandle2, &spiTransaction2);
//        if (!transferOK2)
//        {
//            // Error in SPI or transfer already in progress.
//            while (1);
//        }

    }
    return NULL;

}



