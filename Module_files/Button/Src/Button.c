/************************************
File_Name:Button.c
Date:2023年7月11日
Author:胡尔勤
Declaration:未经允许，禁止用于商业用途
*************************************/

/* Header files */
#include "Button.h"

/*  功能:按键初始化
 *
 */
void Button_INIT()
{
    Button_init();
    Button_Params_init(&buttonparams);
    buttonparams.longPressDuration=2000;                /// 长按检测时间 2s
    buttonparams.doublePressDetectiontimeout=2500;      /// 双按检测超时时间 2s
    buttonhandle1 = Button_open(BUTTON_1, buttonCallbackFxn1, &buttonparams);
    buttonhandle2 = Button_open(BUTTON_2, buttonCallbackFxn2, &buttonparams);
    Mode=0;                                             /// 初始模式设为0

}

/*  功能：按键1的回调函数
 *
 */
void buttonCallbackFxn1(Button_Handle handle, Button_EventMask events)
{
    if (events & Button_EV_CLICKED)         ///短按事件
    {

    }

    if (events & Button_EV_LONGCLICKED)     ///长按事件
    {

    }
    if (events & Button_EV_DOUBLECLICKED)   ///双按事件
    {

    }

}

/*  功能：按键2的回调函数
 *
 */
void buttonCallbackFxn2(Button_Handle handle, Button_EventMask events)
{
    if (events & Button_EV_CLICKED)         ///短按事件
    {

    }

    if (events & Button_EV_LONGCLICKED)     ///长按事件
    {

    }
    if (events & Button_EV_DOUBLECLICKED)   ///双按事件
    {

    }

}
