/************************************
File_Name:LED.c
Date:2023年7月11日
Author:胡尔勤
Declaration:未经允许，禁止用于商业用途
*************************************/
/* Header files */
#include "LED.h"

/******************************************************************************
 LED闪烁：LED_startBlinking(ledHandle, blinkPeriod(Ms), blinkCount);
 LED停止闪烁：LED_stopBlinking(ledHandle)；
 LED点亮：LED_setOn(ledHandle,brightness)；
 LED灭：LED_setOff(ledHandle)；
 ********************************************************************************/


/*功能：LED初始化
 *
 */
void Led_INIT()
{
    LED_Params_init(&ledParams);                        /// 参数默认
    ledHandle1 = LED_open(LED_Red1, &ledParams);
    ledHandle2 = LED_open(LED_Red2, &ledParams);
    ledHandle3 = LED_open(LED_Green,&ledParams);
    ledHandle4 = LED_open(LED_Blue, &ledParams);
}
