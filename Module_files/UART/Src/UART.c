/************************************
File_Name:UART.c
Date:2023��7��11��
Author:������
Declaration:δ��������ֹ������ҵ��;
*************************************/

/* Header files */
#include "UART.h"
#include "LED.h"

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
//    uartparams1.baudRate = 9600;                      /// ������
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
    uartparams1.baudRate = 115200;                      /// ������
    uartparams1.readMode = UART_MODE_CALLBACK;          /// ��ģʽ
    uartparams1.writeMode = UART_MODE_BLOCKING;         /// дģʽ
    uartparams1.readCallback = ReadUART1_Callback;      /// ���ص�����
    uartparams1.writeDataMode = UART_DATA_BINARY;       /// д����ģʽ����������
    uartparams1.readDataMode = UART_DATA_TEXT;          /// ������ģʽ��������
    uartparams1.readReturnMode = UART_RETURN_NEWLINE;   /// ����ģʽ���յ����з�ʱ�ص���
    uartparams1.readEcho = UART_ECHO_OFF;               /// ���Թر�
    uartparams1.readTimeout = UART_WAIT_FOREVER;        /// ��ʱʱ��
    uartparams1.writeTimeout = UART_WAIT_FOREVER;       /// ��ʱʱ��
    uartHandle1 = UART_open(UART1, &uartparams1);
    /*****************************************************************/

    uartparams1.baudRate = 115200;                      /// ������
    uartparams1.readMode = UART_MODE_CALLBACK;          /// ��ģʽ
    uartparams1.writeMode = UART_MODE_CALLBACK;         /// дģʽ
    uartparams1.readCallback = ReadUART2_Callback;      /// ���ص�����
    uartparams1.writeCallback = WriteUART2_Callback;    /// д�ص�����
    uartparams1.writeDataMode = UART_DATA_BINARY;       /// д����ģʽ����������
    uartparams1.readDataMode = UART_DATA_TEXT;          /// ������ģʽ��������
    uartparams1.readReturnMode = UART_RETURN_NEWLINE;   /// ����ģʽ���յ����з�ʱ�ص���
    uartparams1.readEcho = UART_ECHO_OFF;               /// ���Թر�
    uartparams1.readTimeout = UART_WAIT_FOREVER;        /// ��ʱʱ��
    uartparams1.writeTimeout = UART_WAIT_FOREVER;       /// ��ʱʱ��
    uartHandle2 = UART_open(PC_UART, &uartparams1);

    uartparams1.baudRate = 115200;                      /// ������
    uartparams1.readMode = UART_MODE_CALLBACK;          /// ��ģʽ
    uartparams1.writeMode = UART_MODE_BLOCKING;         /// дģʽ(����)
    uartparams1.readCallback = ReadUART3_Callback;      /// ���ص�����
    uartparams1.writeDataMode = UART_DATA_BINARY;       /// д����ģʽ����������
    uartparams1.readDataMode = UART_DATA_TEXT;          /// ������ģʽ��������
    uartparams1.readReturnMode = UART_RETURN_NEWLINE;   /// ����ģʽ���յ����з�ʱ�ص���
    uartparams1.readEcho = UART_ECHO_OFF;               /// ���Թر�
    uartparams1.readTimeout = UART_WAIT_FOREVER;        /// ��ʱʱ��
    uartparams1.writeTimeout = UART_WAIT_FOREVER;       /// ��ʱʱ��
    uartHandle3 = UART_open(UART3, &uartparams1);


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



