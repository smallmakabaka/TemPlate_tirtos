/************************************
File_Name:Others.c
Date:2023年7月11日
Author:胡尔勤
Declaration:未经允许，禁止用于商业用途
*************************************/

/* Header files */
#include "Module_files/Others/Inc/Others.h"

/*  功能：不精确的延时函数（Ms），常用于中断回调函数里
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
