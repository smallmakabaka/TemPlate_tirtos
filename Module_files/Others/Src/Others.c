/************************************
File_Name:Others.c
Date:2023��7��11��
Author:������
Declaration:δ��������ֹ������ҵ��;
*************************************/

/* Header files */
#include "Module_files/Others/Inc/Others.h"

/*  ���ܣ�����ȷ����ʱ������Ms�����������жϻص�������
 *
 */
void ms_Delay(uint32_t t_ms)
{
    while(t_ms--)
    {
        uint32_t t=4000;
        while(t--);
    }
}
void msleep(uint32_t ms)
{
    while(ms--)
    {
        usleep(1000);
    }
}
