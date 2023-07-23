/************************************
File_Name:LED.c
Date:2023��7��11��
Author:������
Declaration:δ��������ֹ������ҵ��;
*************************************/
/* Header files */
#include "LED.h"

/******************************************************************************
 LED��˸��LED_startBlinking(ledHandle, blinkPeriod(Ms), blinkCount);
 LEDֹͣ��˸��LED_stopBlinking(ledHandle)��
 LED������LED_setOn(ledHandle,brightness)��
 LED��LED_setOff(ledHandle)��
 ********************************************************************************/


/*���ܣ�LED��ʼ��
 *
 */
void Led_INIT()
{
    LED_Params_init(&ledParams);                        /// ����Ĭ��
    ledHandle1 = LED_open(LED_Red1, &ledParams);
    ledHandle2 = LED_open(LED_Red2, &ledParams);
    ledHandle3 = LED_open(LED_Green,&ledParams);
    ledHandle4 = LED_open(LED_Blue, &ledParams);
}
