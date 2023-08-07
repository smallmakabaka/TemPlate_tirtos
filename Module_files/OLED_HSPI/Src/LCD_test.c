/*
 *	File_Name:LCD_test.c
 *	Author:胡尔勤
 *	Date:2023年7月18日
 *	Declaration:未经允许，禁止用于商业用途
 */
#include "Module_files/OLED_HSPI/Inc/HSPI.h"
#include "Module_files/OLED_HSPI/Inc/logo.h"
#include "Module_files/Others/Inc/Others.h"

void LCDTest()
{
    uint16_t j;
    LCD_Init();
//    LCD_Clear(BLACK);
    LCD_ShowPicture(0, 0, 240, 40, gImage_logo);
    LCD_ShowString(10, 56, (uint8_t *)"LCD_W:", GREEN, BLACK, 16, 0);
    LCD_ShowIntNum(58, 56, LCD_W, 3, WHITE, BLACK, 16);

    LCD_ShowString(90, 56, (uint8_t *)"LCD_H:", BLUE, BLACK, 16, 0);
    LCD_ShowIntNum(138, 56, LCD_H, 3, WHITE, BLACK, 16);

    for (j = 0; j < 5; j++)
    {
        LCD_ShowPicture(0, 120 + j * 40, 240, 40, gImage_logo);
    }
    msleep(1000);
    LCD_Fill(0, 120, 240, 320, BLACK);
}
