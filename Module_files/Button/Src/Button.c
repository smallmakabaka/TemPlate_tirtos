/************************************
File_Name:Button.c
Date:2023��7��11��
Author:������
Declaration:δ��������ֹ������ҵ��;
*************************************/

/* Header files */
#include "Button.h"

/*  ����:������ʼ��
 *
 */
void Button_INIT()
{
    Button_init();
    Button_Params_init(&buttonparams);
    buttonparams.longPressDuration=2000;                /// �������ʱ�� 2s
    buttonparams.doublePressDetectiontimeout=2500;      /// ˫����ⳬʱʱ�� 2s
    buttonhandle1 = Button_open(BUTTON_1, buttonCallbackFxn1, &buttonparams);
    buttonhandle2 = Button_open(BUTTON_2, buttonCallbackFxn2, &buttonparams);
    Mode=0;                                             /// ��ʼģʽ��Ϊ0

}

/*  ���ܣ�����1�Ļص�����
 *
 */
void buttonCallbackFxn1(Button_Handle handle, Button_EventMask events)
{
    if (events & Button_EV_CLICKED)         ///�̰��¼�
    {

    }

    if (events & Button_EV_LONGCLICKED)     ///�����¼�
    {

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

    }

    if (events & Button_EV_LONGCLICKED)     ///�����¼�
    {

    }
    if (events & Button_EV_DOUBLECLICKED)   ///˫���¼�
    {

    }

}
