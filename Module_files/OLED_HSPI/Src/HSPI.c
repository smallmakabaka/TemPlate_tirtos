/*
 *	File_Name:HSPI.c
 *	Author:胡尔勤
 *	Date:2023年7月18日
 *	Declaration:未经允许，禁止用于商业用途
 */

/* Header files */
#include "Module_files/SPI/Inc/SPI.h"
#include "Module_files/OLED_HSPI/Inc/HSPI.h"
#include "Module_files/OLED_HSPI/Inc/lcdfont.h"
#include "Module_files/Others/Inc/Others.h"
#include "Module_files/Host/Inc/Host.h"


#define LCD_CS_CLR GPIO_write(SPI_0CS, 0)
#define LCD_CS_SET GPIO_write(SPI_0CS, 1)
#define LCD_DC_CLR GPIO_write(SPI_0DC, 0)
#define LCD_DC_SET GPIO_write(SPI_0DC, 1)
#define LCD_RES_CLR GPIO_write(SPI_0RES, 0)
#define LCD_RES_SET GPIO_write(SPI_0RES, 1)

_lcd_dev lcddev;



/*======== SPI1Transmit() ==========
 *  功能：SPI1发送数据
 */
void SPI1Transmit(uint8_t * transmit , uint16_t count)
{
//    Display_printf(handle, 0, 0, "SPI Start");
    spiTransaction.count = count;
    spiTransaction.txBuf = transmit;
    spiTransaction.rxBuf = (void *)NULL;
    transferOK = SPI_transfer(spihandle1, &spiTransaction);
    if (!transferOK)
    {
        // Error in SPI or transfer already in progress.
        Display_printf(hosthandle, 0, 0, "%d" ,spiTransaction.status );
        while (1);

    }
//    else
//    {
//        Display_printf(handle, 0, 0, "%d" ,spiTransaction.status );
//    }

}

/*======== SPI1Transmit() ==========
 *  功能：SPI0发送数据
 */
void SPI1Receive(uint8_t * receive , uint16_t count)
{
    spiTransaction.count = count;
    spiTransaction.rxBuf = receive;
    transferOK = SPI_transfer(spihandle1, &spiTransaction);
    if (!transferOK)
    {
        // Error in SPI or transfer already in progress.
        while (1);
    }
}

/*======== LCD_RESET() ==========
 *  功能：复位
 */
void LCD_RESET(void)
{
    LCD_RES_CLR;
    msleep(100);
    LCD_RES_SET;
    msleep(50);
}
/*======== LCD_WR_REG() ==========
 *  功能：写命令
 */
void LCD_WR_REG(uint8_t reg)
{
    LCD_DC_CLR;                 /// 切换至命令
    LCD_CS_CLR;                 /// 拉低片选
    SPI1Transmit(&reg, 1);
    LCD_CS_SET;                 /// 拉高片选
}

/*======== LCD_WR_DATA() ==========
 *  功能：写数据
 */
void LCD_WR_DATA(uint8_t data)
{
    LCD_DC_SET;                 /// 切换至数据
    LCD_CS_CLR;                 /// 拉低片选
    SPI1Transmit(&data, 1);
    LCD_CS_SET;                 /// 拉高片选
}

/*======== LCD_ReadData() ==========
 *  功能：读数据
 */
void LCD_ReadData(uint8_t *data, uint16_t length)
{
    LCD_DC_SET;                 /// 切换至数据
    LCD_CS_CLR;                 /// 拉低片选
    SPI1Receive(data, length);
    LCD_CS_SET;                 /// 拉高片选
}

/*======== LCD_WriteReg() ==========
 *  功能：写一组命令和数据
 */
void LCD_WriteReg(uint8_t reg, uint8_t regdata)
{
    LCD_WR_REG(reg);
    LCD_WR_DATA(regdata);
}

/*======== LCD_WriteRAM_Prepare() ==========
 *  功能：写GRAM
 */
void LCD_WriteRAM_Prepare(void)
{
    LCD_WR_REG(lcddev.wramcmd);
}

/*======== LCD_WriteData_16Bit() ==========
 *  功能：写2字节数据
 */
void LCD_WriteData_16Bit(uint16_t Data)
{
    uint8_t buf[2];
    LCD_CS_CLR;
    LCD_DC_SET;
    buf[0] = Data >> 8;
    buf[1] = Data & 0xff;
    SPI1Transmit(buf, 2);
    LCD_CS_SET;
}


/*======== LCD_direction() ==========
 *  功能：配置LCD方向
 */
void LCD_direction(uint8_t direction)
{
    lcddev.setxcmd = 0x2A;
    lcddev.setycmd = 0x2B;
    lcddev.wramcmd = 0x2C;
    switch (direction)
    {
    case 0:
        lcddev.width = LCD_W;
        lcddev.height = LCD_H;
        LCD_WriteReg(0x36, (1 << 3) | (0 << 6) | (0 << 7)); // BGR==1,MY==0,MX==0,MV==0
        break;
    case 1:
        lcddev.width = LCD_H;
        lcddev.height = LCD_W;
        LCD_WriteReg(0x36, (1 << 3) | (0 << 7) | (1 << 6) | (1 << 5)); // BGR==1,MY==1,MX==0,MV==1
        break;
    case 2:
        lcddev.width = LCD_W;
        lcddev.height = LCD_H;
        LCD_WriteReg(0x36, (1 << 3) | (1 << 6) | (1 << 7)); // BGR==1,MY==0,MX==0,MV==0
        break;
    case 3:
        lcddev.width = LCD_H;
        lcddev.height = LCD_W;
        LCD_WriteReg(0x36, (1 << 3) | (1 << 7) | (1 << 5)); // BGR==1,MY==1,MX==0,MV==1
        break;
    default:
        break;
    }
}


/*======== LCD_SetWindows() ==========
 *  功能：配置LCD窗口
 */
void LCD_SetWindows(uint16_t xStar, uint16_t yStar, uint16_t xEnd, uint16_t yEnd)
{
    LCD_WR_REG(lcddev.setxcmd);
    LCD_WR_DATA(xStar >> 8);
    LCD_WR_DATA(0x00FF & xStar);
    LCD_WR_DATA(xEnd >> 8);
    LCD_WR_DATA(0x00FF & xEnd);

    LCD_WR_REG(lcddev.setycmd);
    LCD_WR_DATA(yStar >> 8);
    LCD_WR_DATA(0x00FF & yStar);
    LCD_WR_DATA(yEnd >> 8);
    LCD_WR_DATA(0x00FF & yEnd);

    LCD_WriteRAM_Prepare(); // 开始写入GRAM
}

/*======== LCD_SetCursor() ==========
 *  功能：设置光标
 */
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
    LCD_SetWindows(Xpos, Ypos, Xpos, Ypos);
}

/*======== LCD_Clear() ==========
 *  功能：清屏
 */
void LCD_Clear(uint16_t Color)
{
//    SPI_Transaction spiTransaction;
    unsigned int i, k , m;
    uint8_t buf[80];

    for (i = 0; i < 40; i++)
    {
        buf[2 * i] = Color >> 8;
        buf[2 * i + 1] = Color & 0xff;
    }

    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);
    LCD_CS_CLR;
    LCD_DC_SET;
    for (i = 0; i < lcddev.height; i++)
    {
        for (m = 0; m < lcddev.width;)
        {
            m += 40;
            for(k=0;k<80;k=k+8)
            {
                SPI1Transmit(buf+k, 8);
            }

        }
    }
    LCD_CS_SET;
}

/******************************************************************************
      函数说明：在指定区域填充颜色
      入口数据：xsta,ysta   起始坐标
                xend,yend   终止坐标
                                color       要填充的颜色
      返回值：  无
******************************************************************************/
void LCD_Fill(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color)
{
    uint16_t i, j;
    LCD_SetWindows(xsta, ysta, xend - 1, yend - 1); // 设置显示范围
    for (i = ysta; i < yend; i++)
    {
        for (j = xsta; j < xend; j++)
        {
            LCD_WriteData_16Bit(color);
        }
    }
}

/******************************************************************************
      函数说明：在指定位置画点
      入口数据：x,y 画点坐标
                color 点的颜色
      返回值：  无
******************************************************************************/
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
    LCD_SetWindows(x, y, x, y); // 设置光标位置
    LCD_WriteData_16Bit(color);
}

/******************************************************************************
      函数说明：画线
      入口数据：x1,y1   起始坐标
                x2,y2   终止坐标
                color   线的颜色
      返回值：  无
******************************************************************************/
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = x2 - x1; // 计算坐标增量
    delta_y = y2 - y1;
    uRow = x1; // 画线起点坐标
    uCol = y1;
    if (delta_x > 0)
        incx = 1; // 设置单步方向
    else if (delta_x == 0)
        incx = 0; // 垂直线
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)
        incy = 1;
    else if (delta_y == 0)
        incy = 0; // 水平线
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }
    if (delta_x > delta_y)
        distance = delta_x; // 选取基本增量坐标轴
    else
        distance = delta_y;
    for (t = 0; t < distance + 1; t++)
    {
        LCD_DrawPoint(uRow, uCol, color); // 画点
        xerr += delta_x;
        yerr += delta_y;
        if (xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }
        if (yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
}

/******************************************************************************
      函数说明：画矩形
      入口数据：x1,y1   起始坐标
                x2,y2   终止坐标
                color   矩形的颜色
      返回值：  无
******************************************************************************/
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    LCD_DrawLine(x1, y1, x2, y1, color);
    LCD_DrawLine(x1, y1, x1, y2, color);
    LCD_DrawLine(x1, y2, x2, y2, color);
    LCD_DrawLine(x2, y1, x2, y2, color);
}

/******************************************************************************
      函数说明：画圆
      入口数据：x0,y0   圆心坐标
                r       半径
                color   圆的颜色
      返回值：  无
******************************************************************************/
void LCD_DrawCircle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color)
{
    int a, b;
    a = 0;
    b = r;
    while (a <= b)
    {
        LCD_DrawPoint(x0 - b, y0 - a, color); // 3
        LCD_DrawPoint(x0 + b, y0 - a, color); // 0
        LCD_DrawPoint(x0 - a, y0 + b, color); // 1
        LCD_DrawPoint(x0 - a, y0 - b, color); // 2
        LCD_DrawPoint(x0 + b, y0 + a, color); // 4
        LCD_DrawPoint(x0 + a, y0 - b, color); // 5
        LCD_DrawPoint(x0 + a, y0 + b, color); // 6
        LCD_DrawPoint(x0 - b, y0 + a, color); // 7
        a++;
        if ((a * a + b * b) > (r * r)) // 判断要画的点是否过远
        {
            b--;
        }
    }
}

/******************************************************************************
      函数说明：显示单个字符
      入口数据：x,y显示坐标
                num 要显示的字符
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
    uint8_t temp, sizex, t, m = 0;
    uint16_t i, TypefaceNum; // 一个字符所占字节大小
    uint16_t x0 = x;
    sizex = sizey / 2;
    TypefaceNum = (sizex / 8 + ((sizex % 8) ? 1 : 0)) * sizey;
    num = num - ' ';                                    // 得到偏移后的值
    LCD_SetWindows(x, y, x + sizex - 1, y + sizey - 1); // 设置光标位置
    for (i = 0; i < TypefaceNum; i++)
    {
        if (sizey == 12)
            temp = ascii_1206[num][i]; // 调用6x12字体
        else if (sizey == 16)
            temp = ascii_1608[num][i]; // 调用8x16字体
        else if (sizey == 24)
            temp = ascii_2412[num][i]; // 调用12x24字体
        else if (sizey == 32)
            temp = ascii_3216[num][i]; // 调用16x32字体
        else
            return;
        for (t = 0; t < 8; t++)
        {
            if (!mode) // 非叠加模式
            {
                if (temp & (0x01 << t))
                    LCD_WriteData_16Bit(fc);
                else
                    LCD_WriteData_16Bit(bc);
                m++;
                if (m % sizex == 0)
                {
                    m = 0;
                    break;
                }
            }
            else // 叠加模式
            {
                if (temp & (0x01 << t))
                    LCD_DrawPoint(x, y, fc); // 画一个点
                x++;
                if ((x - x0) == sizex)
                {
                    x = x0;
                    y++;
                    break;
                }
            }
        }
    }
}

/******************************************************************************
      函数说明：显示字符串
      入口数据：x,y显示坐标
                *p 要显示的字符串
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowString(uint16_t x, uint16_t y, const uint8_t *p, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
    while (*p != '\0')
    {
        LCD_ShowChar(x, y, *p, fc, bc, sizey, mode);
        x += sizey / 2;
        p++;
    }
}

/******************************************************************************
      函数说明：显示数字
      入口数据：m底数，n指数
      返回值：  无
******************************************************************************/
uint32_t mypow(uint8_t m, uint8_t n)
{
    uint32_t result = 1;
    while (n--)
        result *= m;
    return result;
}

/******************************************************************************
      函数说明：显示整数变量
      入口数据：x,y显示坐标
                num 要显示整数变量
                len 要显示的位数
                fc 字的颜色
                bc 字的背景色
                sizey 字号
      返回值：  无
******************************************************************************/
void LCD_ShowIntNum(uint16_t x, uint16_t y, uint16_t num, uint8_t len, uint16_t fc, uint16_t bc, uint8_t sizey)
{
    uint8_t t, temp;
    uint8_t enshow = 0;
    uint8_t sizex = sizey / 2;
    for (t = 0; t < len; t++)
    {
        temp = (num / mypow(10, len - t - 1)) % 10;
        if (enshow == 0 && t < (len - 1))
        {
            if (temp == 0)
            {
                LCD_ShowChar(x + t * sizex, y, ' ', fc, bc, sizey, 0);
                continue;
            }
            else
                enshow = 1;
        }
        LCD_ShowChar(x + t * sizex, y, temp + 48, fc, bc, sizey, 0);
    }
}

/******************************************************************************
      函数说明：显示两位小数变量
      入口数据：x,y显示坐标
                num 要显示小数变量
                len 要显示的位数
                fc 字的颜色
                bc 字的背景色
                sizey 字号
      返回值：  无
******************************************************************************/
void LCD_ShowFloatNum1(uint16_t x, uint16_t y, float num, uint8_t len, uint16_t fc, uint16_t bc, uint8_t sizey)
{
    uint8_t t, temp, sizex;
    uint16_t num1;
    sizex = sizey / 2;
    num1 = num * 100;
    for (t = 0; t < len; t++)
    {
        temp = (num1 / mypow(10, len - t - 1)) % 10;
        if (t == (len - 2))
        {
            LCD_ShowChar(x + (len - 2) * sizex, y, '.', fc, bc, sizey, 0);
            t++;
            len += 1;
        }
        LCD_ShowChar(x + t * sizex, y, temp + 48, fc, bc, sizey, 0);
    }
}

/******************************************************************************
      函数说明：显示图片
      入口数据：x,y起点坐标
                length 图片长度
                width  图片宽度
                pic[]  图片数组
      返回值：  无
******************************************************************************/
void LCD_ShowPicture(uint16_t x, uint16_t y, uint16_t length, uint16_t width, const uint8_t pic[])
{
    uint16_t i, j;
    uint32_t k = 0;
    LCD_SetWindows(x, y, x + length - 1, y + width - 1);
    for (i = 0; i < length; i++)
    {
        for (j = 0; j < width; j++)
        {
            LCD_WR_DATA(pic[k * 2]);
            LCD_WR_DATA(pic[k * 2 + 1]);
            k++;
        }
    }
}

uint32_t LCD_Get_Id(void)
{
    uint32_t id;
    id = 0;
    // get_id cmd
    uint8_t buf;
    buf = 0x04;
    LCD_DC_CLR;
    LCD_CS_CLR;
    SPI1Transmit(&buf, 1);
    LCD_DC_SET;
    SPI1Receive((uint8_t *)&id, 3);
    LCD_CS_SET;

    return id;
}

static void _st7789_init(void)
{
    //--------------------------------ST7789S Frame rate setting-------------------------
    LCD_WR_REG(0xb2);
    LCD_WR_DATA(0x0c);
    LCD_WR_DATA(0x0c);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x33);
    LCD_WR_DATA(0x33);
    LCD_WR_REG(0xb7);
    LCD_WR_DATA(0x35);

    //---------------------------------ST7789S Power setting-----------------------------
    LCD_WR_REG(0xbb);
    LCD_WR_DATA(0x35);
    LCD_WR_REG(0xc0);
    LCD_WR_DATA(0x0c); // XOR RGB setting in command 36h.
    LCD_WR_REG(0xc2);
    LCD_WR_DATA(0x01);
    LCD_WR_REG(0xc3);
    LCD_WR_DATA(0x13);
    LCD_WR_REG(0xc4);
    LCD_WR_DATA(0x20);
    LCD_WR_REG(0xc6);
    LCD_WR_DATA(0x0f);
    LCD_WR_REG(0xca);
    LCD_WR_DATA(0x0f);
    LCD_WR_REG(0xc8);
    LCD_WR_DATA(0x08);
    LCD_WR_REG(0x55);
    LCD_WR_DATA(0x90);
    LCD_WR_REG(0xd0);
    LCD_WR_DATA(0xa4);
    LCD_WR_DATA(0xa1);

    LCD_WR_REG(0x36); // Memory Access Control
    LCD_WR_DATA(0x00);

    LCD_WR_REG(0x3A);
    LCD_WR_DATA(0x05);

    //--------------------------------ST7789S gamma setting------------------------------
    LCD_WR_REG(0xe0);
    LCD_WR_DATA(0xd0);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x06);
    LCD_WR_DATA(0x09);
    LCD_WR_DATA(0x0b);
    LCD_WR_DATA(0x2a);
    LCD_WR_DATA(0x3c);
    LCD_WR_DATA(0x55);
    LCD_WR_DATA(0x4b);
    LCD_WR_DATA(0x08);
    LCD_WR_DATA(0x16);
    LCD_WR_DATA(0x14);
    LCD_WR_DATA(0x19);
    LCD_WR_DATA(0x20);
    LCD_WR_REG(0xe1);
    LCD_WR_DATA(0xd0);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x06);
    LCD_WR_DATA(0x09);
    LCD_WR_DATA(0x0b);
    LCD_WR_DATA(0x29);
    LCD_WR_DATA(0x36);
    LCD_WR_DATA(0x54);
    LCD_WR_DATA(0x4b);
    LCD_WR_DATA(0x0d);
    LCD_WR_DATA(0x16);
    LCD_WR_DATA(0x14);
    LCD_WR_DATA(0x21);
    LCD_WR_DATA(0x20);
    LCD_WR_REG(0x29);
}

static void _ili9341_init(void)
{
    //************* Start Initial Sequence **********//
    LCD_WR_REG(0xCF);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0xD9);
    LCD_WR_DATA(0X30);

    LCD_WR_REG(0xED);
    LCD_WR_DATA(0x64);
    LCD_WR_DATA(0x03);
    LCD_WR_DATA(0X12);
    LCD_WR_DATA(0X81);

    LCD_WR_REG(0xE8);
    LCD_WR_DATA(0x85);
    LCD_WR_DATA(0x10);
    LCD_WR_DATA(0x78);

    LCD_WR_REG(0xCB);
    LCD_WR_DATA(0x39);
    LCD_WR_DATA(0x2C);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x34);
    LCD_WR_DATA(0x02);

    LCD_WR_REG(0xF7);
    LCD_WR_DATA(0x20);

    LCD_WR_REG(0xEA);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);

    LCD_WR_REG(0xC0);  // Power control
    LCD_WR_DATA(0x21); // VRH[5:0]

    LCD_WR_REG(0xC1);  // Power control
    LCD_WR_DATA(0x12); // SAP[2:0];BT[3:0]

    LCD_WR_REG(0xC5); // VCM control
    LCD_WR_DATA(0x32);
    LCD_WR_DATA(0x3C);

    LCD_WR_REG(0xC7); // VCM control2
    LCD_WR_DATA(0XC1);

    LCD_WR_REG(0x36); // Memory Access Control
    LCD_WR_DATA(0xA8);

    LCD_WR_REG(0x3A);
    LCD_WR_DATA(0x55);

    LCD_WR_REG(0xB1);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x18);

    LCD_WR_REG(0xB6); // Display Function Control
    LCD_WR_DATA(0x0A);
    LCD_WR_DATA(0xA2);

    LCD_WR_REG(0xF2); // 3Gamma Function Disable
    LCD_WR_DATA(0x00);

    LCD_WR_REG(0x26); // Gamma curve selected
    LCD_WR_DATA(0x01);

    LCD_WR_REG(0xE0); // Set Gamma
    LCD_WR_DATA(0x0F);
    LCD_WR_DATA(0x20);
    LCD_WR_DATA(0x1E);
    LCD_WR_DATA(0x09);
    LCD_WR_DATA(0x12);
    LCD_WR_DATA(0x0B);
    LCD_WR_DATA(0x50);
    LCD_WR_DATA(0XBA);
    LCD_WR_DATA(0x44);
    LCD_WR_DATA(0x09);
    LCD_WR_DATA(0x14);
    LCD_WR_DATA(0x05);
    LCD_WR_DATA(0x23);
    LCD_WR_DATA(0x21);
    LCD_WR_DATA(0x00);

    LCD_WR_REG(0XE1); // Set Gamma
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x19);
    LCD_WR_DATA(0x19);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x12);
    LCD_WR_DATA(0x07);
    LCD_WR_DATA(0x2D);
    LCD_WR_DATA(0x28);
    LCD_WR_DATA(0x3F);
    LCD_WR_DATA(0x02);
    LCD_WR_DATA(0x0A);
    LCD_WR_DATA(0x08);
    LCD_WR_DATA(0x25);
    LCD_WR_DATA(0x2D);
    LCD_WR_DATA(0x0F);
    LCD_WR_REG(0x29);
}

void LCD_Init(void)
{
    LCD_RESET(); // LCD Hardware Reset

    //************* Start Initial Sequence **********//
    LCD_WR_REG(0x11); // Sleep out
    msleep(120);       // Delay 120ms

    lcddev.id = LCD_Get_Id();

    if (lcddev.id != 0)
    {
        _st7789_init();
    }
    else
    {
        _ili9341_init();
    }

    LCD_direction(USE_HORIZONTAL); // 设置LCD显示方向
    // LCD_Clear(BLACK);               //清全屏白色
    LCD_Clear(BLACK);
}

