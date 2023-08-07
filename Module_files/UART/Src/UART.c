/************************************
File_Name:UART.c
Date:2023��7��11��
Author:������
Declaration:δ��������ֹ������ҵ��;
*************************************/

/* Header files */
#include "Module_files/UART/Inc/UART.h"
#include "Module_files/LED/Inc/LED.h"
#include "Module_files/Others/Inc/Others.h"

/********ע��
 * 1. �����ղ���TEXT��NEWLINEģʽʱ��������һ��Ҫ���ϻ��з���������δ�����л��з�ʱҲ������ж�
 *    TEXTģʽ�ڽ���ʱ�Ὣ�س����У�0D 0A�����س�(0D)������(0A)ͳһ�滻�ɻ���(0A)
 */
/*  ���ܣ����ڳ�ʼ��
 *
 */

void UART_INIT()
{
    UART_init();
    UART_Params_init(&uartparams1);
    /*************** ����1 �����뼤�⴫����*************************/
    uartparams1.baudRate = 9600;                        /// ������
    uartparams1.readMode = UART_MODE_CALLBACK;          /// ��ģʽ
    uartparams1.writeMode = UART_MODE_BLOCKING;         /// дģʽ
    uartparams1.readCallback = ReadUART1_Callback;      /// ���ص�����
    uartparams1.writeDataMode = UART_DATA_BINARY;       /// д����ģʽ����������
    uartparams1.readDataMode = UART_DATA_TEXT;          /// ������ģʽ��������
    uartparams1.readReturnMode = UART_RETURN_NEWLINE;   /// ����ģʽ���յ����з�ʱ�ص���
    uartparams1.readEcho = UART_ECHO_OFF;               /// ���Թر�
    uartparams1.readTimeout = UART_WAIT_FOREVER;        /// ��ʱʱ��
    uartparams1.writeTimeout = UART_WAIT_FOREVER;                     /// ��ʱʱ��
    uartHandle1 = UART_open(UART1, &uartparams1);
    /******************************************************************/

    /***************** ����1 ����ΪPC���Կ�***************************/
//    uartparams1.baudRate = 115200;                      /// ������
//    uartparams1.readMode = UART_MODE_CALLBACK;          /// ��ģʽ
//    uartparams1.writeMode = UART_MODE_CALLBACK;         /// дģʽ
//    uartparams1.readCallback = ReadUART1_Callback;      /// ���ص�����
//    uartparams1.writeCallback = WriteUART1_Callback;    /// д�ص�����
//    uartparams1.writeDataMode = UART_DATA_BINARY;       /// д����ģʽ����������
//    uartparams1.readDataMode = UART_DATA_TEXT;          /// ������ģʽ��������
//    uartparams1.readReturnMode = UART_RETURN_NEWLINE;   /// ����ģʽ���յ����з�ʱ�ص���
//    uartparams1.readEcho = UART_ECHO_OFF;               /// ���Թر�
//    uartparams1.readTimeout = UART_WAIT_FOREVER;        /// ��ʱʱ��
//    uartparams1.writeTimeout = UART_WAIT_FOREVER;       /// ��ʱʱ��
//    uartHandle1 = UART_open(UART1, &uartparams1);
    /*****************************************************************/

    /***************** ����1 ����ΪOpenMV�ӿ� ***************************/
//    uartparams1.baudRate = 115200;                      /// ������
//    uartparams1.readMode = UART_MODE_CALLBACK;          /// ��ģʽ
//    uartparams1.writeMode = UART_MODE_BLOCKING;         /// дģʽ
//    uartparams1.readCallback = ReadUART1_Callback;      /// ���ص�����
//    uartparams1.writeDataMode = UART_DATA_BINARY;       /// д����ģʽ����������
//    uartparams1.readDataMode = UART_DATA_TEXT;          /// ������ģʽ��������
//    uartparams1.readReturnMode = UART_RETURN_NEWLINE;   /// ����ģʽ���յ����з�ʱ�ص���
//    uartparams1.readEcho = UART_ECHO_OFF;               /// ���Թر�
//    uartparams1.readTimeout = UART_WAIT_FOREVER;        /// ��ʱʱ��
//    uartparams1.writeTimeout = UART_WAIT_FOREVER;       /// ��ʱʱ��
//    uartHandle1 = UART_open(UART1, &uartparams1);
    /*****************************************************************/

    /*************** ����2 ����PC����*************************/
    UART_Params_init(&uartparams2);
    uartparams2.baudRate = 115200;                      /// ������
    uartparams2.readMode = UART_MODE_CALLBACK;          /// ��ģʽ
    uartparams2.writeMode = UART_MODE_CALLBACK;         /// дģʽ
    uartparams2.readCallback = ReadUART2_Callback;      /// ���ص�����
    uartparams2.writeCallback = WriteUART2_Callback;    /// д�ص�����
    uartparams2.writeDataMode = UART_DATA_BINARY;       /// д����ģʽ����������
    uartparams2.readDataMode = UART_DATA_TEXT;          /// ������ģʽ��������
    uartparams2.readReturnMode = UART_RETURN_NEWLINE;   /// ����ģʽ���յ����з�ʱ�ص���
    uartparams2.readEcho = UART_ECHO_OFF;               /// ���Թر�
    uartparams2.readTimeout = UART_WAIT_FOREVER;        /// ��ʱʱ��
    uartparams2.writeTimeout = UART_WAIT_FOREVER;       /// ��ʱʱ��
    uartHandle2 = UART_open(PC_UART, &uartparams2);


    /******************UART3 ����STM32ͨ�� ****************************/
    UART_Params_init(&uartparams3);
    uartparams3.baudRate = 115200;                      /// ������
    uartparams3.readMode = UART_MODE_BLOCKING;          /// ��ģʽ
    uartparams3.writeMode = UART_MODE_BLOCKING;         /// дģʽ(����)
    uartparams3.readEcho = UART_ECHO_OFF;               /// ���Թر�
    uartparams3.readTimeout  = 10;        /// ��ʱʱ��
    uartparams3.writeTimeout = 100;       /// ��ʱʱ��
    uartHandle3 = UART_open(UART3, &uartparams3);

}


void UART3_DEINIT()
{
    UART_close(uartHandle3);
    msleep(10);
    uartparams3.baudRate = 115200;                      /// ������
    uartparams3.readMode = UART_MODE_CALLBACK;          /// ��ģʽ
    uartparams3.writeMode = UART_MODE_BLOCKING;         /// дģʽ(����)
    uartparams3.readCallback = ReadUART3_Callback;      /// ���ص�����
    uartparams3.writeDataMode = UART_DATA_BINARY;       /// д����ģʽ����������
    uartparams3.readDataMode = UART_DATA_TEXT;          /// ������ģʽ��������
    uartparams3.readReturnMode = UART_RETURN_NEWLINE;   /// ����ģʽ���յ����з�ʱ�ص���
    uartparams3.readEcho = UART_ECHO_OFF;               /// ���Թر�
    uartparams3.readTimeout = UART_WAIT_FOREVER;        /// ��ʱʱ��
    uartparams3.writeTimeout = UART_WAIT_FOREVER;       /// ��ʱʱ��
    uartHandle3 = UART_open(UART3, &uartparams3);
}




/*  ���ܣ�����1���ص�����
 *  read_status: 1 ��ʾ������ɣ�0 ��ʾ����δ���
 *  close_status: 1 ��ʾ���ڹرգ�0 ��ʾ���ڴ�
 */


/*  ���ܣ�ѭ�����գ�����
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



