/************************************
File_Name:UART.c
Date:2023年7月11日
Author:胡尔勤
Declaration:未经允许，禁止用于商业用途
*************************************/

/* Header files */
#include "Module_files/UART/Inc/UART.h"
#include "Module_files/LED/Inc/LED.h"
#include "Module_files/Others/Inc/Others.h"

/********注意
 * 1. 当接收采用TEXT和NEWLINE模式时，数据中一定要加上换行符，当数据未满但有换行符时也会进入中断
 *    TEXT模式在接收时会将回车换行（0D 0A）、回车(0D)、换行(0A)统一替换成换行(0A)
 */
/*  功能：串口初始化
 *
 */

void UART_INIT()
{
    UART_init();
    UART_Params_init(&uartparams1);
    /*************** 串口1 用于与激光传感器*************************/
    uartparams1.baudRate = 9600;                        /// 波特率
    uartparams1.readMode = UART_MODE_CALLBACK;          /// 读模式
    uartparams1.writeMode = UART_MODE_BLOCKING;         /// 写模式
    uartparams1.readCallback = ReadUART1_Callback;      /// 读回调函数
    uartparams1.writeDataMode = UART_DATA_BINARY;       /// 写数据模式（不做处理）
    uartparams1.readDataMode = UART_DATA_TEXT;          /// 读数据模式（做处理）
    uartparams1.readReturnMode = UART_RETURN_NEWLINE;   /// 返回模式（收到换行符时回调）
    uartparams1.readEcho = UART_ECHO_OFF;               /// 回显关闭
    uartparams1.readTimeout = UART_WAIT_FOREVER;        /// 超时时间
    uartparams1.writeTimeout = UART_WAIT_FOREVER;                     /// 超时时间
    uartHandle1 = UART_open(UART1, &uartparams1);
    /******************************************************************/

    /***************** 串口1 征用为PC调试口***************************/
//    uartparams1.baudRate = 115200;                      /// 波特率
//    uartparams1.readMode = UART_MODE_CALLBACK;          /// 读模式
//    uartparams1.writeMode = UART_MODE_CALLBACK;         /// 写模式
//    uartparams1.readCallback = ReadUART1_Callback;      /// 读回调函数
//    uartparams1.writeCallback = WriteUART1_Callback;    /// 写回调函数
//    uartparams1.writeDataMode = UART_DATA_BINARY;       /// 写数据模式（不做处理）
//    uartparams1.readDataMode = UART_DATA_TEXT;          /// 读数据模式（做处理）
//    uartparams1.readReturnMode = UART_RETURN_NEWLINE;   /// 返回模式（收到换行符时回调）
//    uartparams1.readEcho = UART_ECHO_OFF;               /// 回显关闭
//    uartparams1.readTimeout = UART_WAIT_FOREVER;        /// 超时时间
//    uartparams1.writeTimeout = UART_WAIT_FOREVER;       /// 超时时间
//    uartHandle1 = UART_open(UART1, &uartparams1);
    /*****************************************************************/

    /***************** 串口1 征用为OpenMV接口 ***************************/
//    uartparams1.baudRate = 115200;                      /// 波特率
//    uartparams1.readMode = UART_MODE_CALLBACK;          /// 读模式
//    uartparams1.writeMode = UART_MODE_BLOCKING;         /// 写模式
//    uartparams1.readCallback = ReadUART1_Callback;      /// 读回调函数
//    uartparams1.writeDataMode = UART_DATA_BINARY;       /// 写数据模式（不做处理）
//    uartparams1.readDataMode = UART_DATA_TEXT;          /// 读数据模式（做处理）
//    uartparams1.readReturnMode = UART_RETURN_NEWLINE;   /// 返回模式（收到换行符时回调）
//    uartparams1.readEcho = UART_ECHO_OFF;               /// 回显关闭
//    uartparams1.readTimeout = UART_WAIT_FOREVER;        /// 超时时间
//    uartparams1.writeTimeout = UART_WAIT_FOREVER;       /// 超时时间
//    uartHandle1 = UART_open(UART1, &uartparams1);
    /*****************************************************************/

    /*************** 串口2 用于PC调试*************************/
    UART_Params_init(&uartparams2);
    uartparams2.baudRate = 115200;                      /// 波特率
    uartparams2.readMode = UART_MODE_CALLBACK;          /// 读模式
    uartparams2.writeMode = UART_MODE_CALLBACK;         /// 写模式
    uartparams2.readCallback = ReadUART2_Callback;      /// 读回调函数
    uartparams2.writeCallback = WriteUART2_Callback;    /// 写回调函数
    uartparams2.writeDataMode = UART_DATA_BINARY;       /// 写数据模式（不做处理）
    uartparams2.readDataMode = UART_DATA_TEXT;          /// 读数据模式（做处理）
    uartparams2.readReturnMode = UART_RETURN_NEWLINE;   /// 返回模式（收到换行符时回调）
    uartparams2.readEcho = UART_ECHO_OFF;               /// 回显关闭
    uartparams2.readTimeout = UART_WAIT_FOREVER;        /// 超时时间
    uartparams2.writeTimeout = UART_WAIT_FOREVER;       /// 超时时间
    uartHandle2 = UART_open(PC_UART, &uartparams2);


    /******************UART3 用于STM32通信 ****************************/
    UART_Params_init(&uartparams3);
    uartparams3.baudRate = 115200;                      /// 波特率
    uartparams3.readMode = UART_MODE_BLOCKING;          /// 读模式
    uartparams3.writeMode = UART_MODE_BLOCKING;         /// 写模式(阻塞)
    uartparams3.readEcho = UART_ECHO_OFF;               /// 回显关闭
    uartparams3.readTimeout  = 10;        /// 超时时间
    uartparams3.writeTimeout = 100;       /// 超时时间
    uartHandle3 = UART_open(UART3, &uartparams3);

}


void UART3_DEINIT()
{
    UART_close(uartHandle3);
    msleep(10);
    uartparams3.baudRate = 115200;                      /// 波特率
    uartparams3.readMode = UART_MODE_CALLBACK;          /// 读模式
    uartparams3.writeMode = UART_MODE_BLOCKING;         /// 写模式(阻塞)
    uartparams3.readCallback = ReadUART3_Callback;      /// 读回调函数
    uartparams3.writeDataMode = UART_DATA_BINARY;       /// 写数据模式（不做处理）
    uartparams3.readDataMode = UART_DATA_TEXT;          /// 读数据模式（做处理）
    uartparams3.readReturnMode = UART_RETURN_NEWLINE;   /// 返回模式（收到换行符时回调）
    uartparams3.readEcho = UART_ECHO_OFF;               /// 回显关闭
    uartparams3.readTimeout = UART_WAIT_FOREVER;        /// 超时时间
    uartparams3.writeTimeout = UART_WAIT_FOREVER;       /// 超时时间
    uartHandle3 = UART_open(UART3, &uartparams3);
}




/*  功能：串口1读回调函数
 *  read_status: 1 表示接收完成，0 表示接收未完成
 *  close_status: 1 表示串口关闭，0 表示串口打开
 */


/*  功能：循环接收，阻塞
 *
 */
void Read_Circle_Poll()
{
    while(read_status==0);
    uartHandle1 = UART_open(UART1, &uartparams1);
    UART_write(uartHandle1, readbuffer, 10);
    UART_read(uartHandle1, readbuffer, 10);
    read_status=0;
    close_status=0;
}

void Read_Circle()
{
    if(read_status==1)
    {
        UART_read(uartHandle1, readbuffer, 10);
    }
}



