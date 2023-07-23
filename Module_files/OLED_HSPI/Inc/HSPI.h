/*
 *	File_Name:HSPI.h
 *	Author:������
 *	Date:2023��7��18��
 *	Declaration:δ��������ֹ������ҵ��;
 */

#ifndef MODULE_FILES_OLED_HSPI_INC_HSPI_H_
#define MODULE_FILES_OLED_HSPI_INC_HSPI_H_


#ifdef __cplusplus
}
#endif


/* Header files */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "ti_drivers_config.h"
#include "unistd.h"
#include <stdint.h>

/* TI-Drivers Header files */
#include <ti/drivers/SPI.h>
#include <ti/drivers/GPIO.h>

/* User Header files */
///

typedef struct
{
    uint16_t width;   // LCD ���
    uint16_t height;  // LCD �߶�
    uint32_t id;      // LCD ID
    uint8_t dir;      // ���������������ƣ�0��������1��������
    uint16_t wramcmd; // ��ʼдgramָ��
    uint16_t setxcmd; // ����x����ָ��
    uint16_t setycmd; // ����y����ָ��
} _lcd_dev;

// LCD����
extern _lcd_dev lcddev; // ����LCD��Ҫ����
/////////////////////////////////////�û�������///////////////////////////////////
#define USE_HORIZONTAL 0 // ����Һ����˳ʱ����ת����    0-0����ת��1-90����ת��2-180����ת��3-270����ת

//////////////////////////////////////////////////////////////////////////////////
// ����LCD�ĳߴ�
#define LCD_W 240
#define LCD_H 320

// ������ɫ
#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define BRED 0XF81F
#define GRED 0XFFE0
#define GBLUE 0X07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define GREEN 0x07E0
#define CYAN 0x7FFF
#define YELLOW 0xFFE0
#define BROWN 0XBC40 // ��ɫ
#define BRRED 0XFC07 // �غ�ɫ
#define GRAY 0X8430  // ��ɫ

// GUI��ɫ
#define DARKBLUE 0X01CF  // ����ɫ
#define LIGHTBLUE 0X7D7C // ǳ��ɫ
#define GRAYBLUE 0X5458  // ����ɫ

// ������ɫΪPANEL����ɫ
#define LIGHTGREEN 0X841F // ǳ��ɫ
#define LIGHTGRAY 0XEF5B  // ǳ��ɫ(PANNEL)
#define LGRAY 0XC618      // ǳ��ɫ(PANNEL),���屳��ɫ
#define LGRAYBLUE 0XA651  // ǳ����ɫ(�м����ɫ)
#define LBBLUE 0X2B12     // ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)


/* Variable Define */


/* Function Declaration */
void SPI_INIT();
void LCD_RESET(void);
void LCD_WR_REG(uint8_t reg);
void LCD_WR_DATA(uint8_t data);
void LCD_WriteReg(uint8_t reg, uint8_t regdata);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteData_16Bit(uint16_t Data);
void LCD_direction(uint8_t direction);
void LCD_SetWindows(uint16_t xStar, uint16_t yStar, uint16_t xEnd, uint16_t yEnd);
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
void LCD_Clear(uint16_t Color);
void LCD_Fill(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color);
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color);
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void LCD_DrawCircle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color);
void LCD_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode);
void LCD_ShowString(uint16_t x, uint16_t y, const uint8_t *p, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode);
void LCD_ShowIntNum(uint16_t x, uint16_t y, uint16_t num, uint8_t len, uint16_t fc, uint16_t bc, uint8_t sizey);
void LCD_ShowPicture(uint16_t x, uint16_t y, uint16_t length, uint16_t width, const uint8_t pic[]);

uint32_t LCD_Get_Id(void);
void LCD_Init(void);
void LCDTest();

#endif /* MODULE_FILES_OLED_HSPI_INC_HSPI_H_ */
