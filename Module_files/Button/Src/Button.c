/************************************
File_Name:Button.c
Date:2023��7��11��
Author:������
Declaration:δ��������ֹ������ҵ��;
*************************************/

/* Header files */
#include "Module_files/Button/Inc/Button.h"
#include "Module_files/LED/Inc/LED.h"
#include "Module_files/UART/Inc/UART.h"
#include "Threads/uartThread/Inc/uart_thread.h"

/*  ����:������ʼ��
 *
 */
void Button_INIT()
{
    Button_init();
    Button_Params_init(&buttonparams);
    buttonparams.longPressDuration=2000;                /// �������ʱ�� 2s
    buttonparams.doublePressDetectiontimeout=2500;      /// ˫����ⳬʱʱ�� 2.5s
    buttonhandle1 = Button_open(BUTTON_1, buttonCallbackFxn1, &buttonparams);
    buttonhandle2 = Button_open(BUTTON_2, buttonCallbackFxn2, &buttonparams);
    Mode=Free_MODE;                                             /// ��ʼģʽ��Ϊ0

}

/*  ���ܣ�����1�Ļص�����
 *
 */
void buttonCallbackFxn1(Button_Handle handle, Button_EventMask events)
{
    if (events & Button_EV_CLICKED)         ///�̰��¼�
    {
        UART_writeCancel(uartHandle1);
        UART_readCancel(uartHandle1);
        UART_close(uartHandle1);
        sem_trywait(&semUART);
        Rang=Rang_Off;
        LED_startBlinking(ledHandle1, 100, 2);
        Mode_Change=IS_Change;
         Mode=Update_MODE;                  /// �Զ�����ģʽ
    }

    if (events & Button_EV_LONGCLICKED)     ///�����¼�
    {
        UART_writeCancel(uartHandle1);
        UART_readCancel(uartHandle1);
        UART_close(uartHandle1);
        sem_trywait(&semUART);
        Rang=Rang_Off;
        LED_startBlinking(ledHandle1, 100, 2);
        Mode_Change=IS_Change;
         Mode=Free_MODE;
    }
    if (events & Button_EV_DOUBLECLICKED)   ///˫���¼�
    {

    }

}

/*  ���ܣ�����2�Ļص�����
 *
 */
void buttonCallbackFxn2(Button_Handle handle, Button_EventMask events)
{
    if (events & Button_EV_CLICKED)         ///�̰��¼�
    {
        UART_writeCancel(uartHandle1);
        UART_readCancel(uartHandle1);
        UART_close(uartHandle1);
        sem_trywait(&semUART);
        Rang=Rang_Off;
        LED_startBlinking(ledHandle1, 100, 2);
        Mode_Change=IS_Change;
        Mode=Trace_MODE;                  /// ѭ��ģʽ
    }

    if (events & Button_EV_LONGCLICKED)     ///�����¼�
    {

    }
    if (events & Button_EV_DOUBLECLICKED)   ///˫���¼�
    {

    }

}
