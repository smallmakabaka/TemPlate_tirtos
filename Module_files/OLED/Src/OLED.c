/************************************
File_Name:OLED.c
Date:2023年7月11日
Author:胡尔勤
Declaration:未经允许，禁止用于商业用途
*************************************/

/* Header files */
#include "OLED.h"

/*  字母和数字库
 *
 */
uint8_t F8x16[]=
{0x00,0x00,0x00,0x30,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//".",0
        /* (8 X 16 , 宋体 ) */
0x00,0x00,0x00,0x60,0x00,0x18,0x00,0x07,0xC0,0x00,0x38,0x00,0x04,0x00,0x00,0x00,//"/",1
        /* (8 X 16 , 宋体 ) */
0x00,0x00,0xE0,0x0F,0x10,0x10,0x08,0x20,0x08,0x20,0x10,0x10,0xE0,0x0F,0x00,0x00,//"0",2
        /* (8 X 16 , 宋体 ) */
0x00,0x00,0x00,0x00,0x10,0x20,0x10,0x20,0xF8,0x3F,0x00,0x20,0x00,0x20,0x00,0x00,//"1",3
        /* (8 X 16 , 宋体 ) */
0x00,0x00,0x70,0x30,0x08,0x28,0x08,0x24,0x08,0x22,0x08,0x21,0xF0,0x30,0x00,0x00,//"2",4
        /* (8 X 16 , 宋体 ) */
0x00,0x00,0x30,0x18,0x08,0x20,0x08,0x21,0x08,0x21,0x88,0x22,0x70,0x1C,0x00,0x00,//"3",5
        /* (8 X 16 , 宋体 ) */
0x00,0x00,0x00,0x06,0x80,0x05,0x40,0x24,0x30,0x24,0xF8,0x3F,0x00,0x24,0x00,0x24,//"4",6
        /* (8 X 16 , 宋体 ) */
0x00,0x00,0xF8,0x19,0x88,0x20,0x88,0x20,0x88,0x20,0x08,0x11,0x08,0x0E,0x00,0x00,//"5",7
        /* (8 X 16 , 宋体 ) */
0x00,0x00,0xE0,0x0F,0x10,0x11,0x88,0x20,0x88,0x20,0x90,0x20,0x00,0x1F,0x00,0x00,//"6",8
        /* (8 X 16 , 宋体 ) */
0x00,0x00,0x18,0x00,0x08,0x00,0x08,0x3E,0x88,0x01,0x68,0x00,0x18,0x00,0x00,0x00,//"7",9
        /* (8 X 16 , 宋体 ) */
0x00,0x00,0x70,0x1C,0x88,0x22,0x08,0x21,0x08,0x21,0x88,0x22,0x70,0x1C,0x00,0x00,//"8",10
        /* (8 X 16 , 宋体 ) */
0x00,0x00,0xF0,0x01,0x08,0x12,0x08,0x22,0x08,0x22,0x10,0x11,0xE0,0x0F,0x00,0x00,//"9",11
        /* (8 X 16 , 宋体 ) */

};

/* 汉字库
 *
 */
uint8_t F16x16[]=
{
0x00,0x00,0x00,0x00,0xF8,0x1F,0x88,0x08,0x88,0x08,0x88,0x08,0x88,0x08,0xFF,0x7F,
0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0xF8,0x9F,0x00,0x80,0x00,0xF0,0x00,0x00,//"电",0
 /* (16 X 16 , 宋体 ) */

0x00,0x80,0x00,0x60,0xFE,0x1F,0x02,0x40,0x82,0x40,0x82,0x40,0x82,0x40,0x82,0x40,
0xFA,0x7F,0x82,0x40,0x82,0x40,0x82,0x44,0x82,0x58,0x82,0x40,0x02,0x40,0x00,0x00,//"压",1
/* (16 X 16 , 宋体 ) */

0x00,0x40,0x02,0x40,0x02,0x40,0xC2,0x7F,0x02,0x40,0x02,0x40,0x02,0x40,0xFE,0x7F,
0x82,0x40,0x82,0x40,0x82,0x40,0x82,0x40,0x82,0x40,0x02,0x40,0x00,0x40,0x00,0x00,//"正",2
/* (16 X 16 , 宋体 ) */

0x02,0x00,0xE2,0x43,0x22,0x82,0x22,0x42,0x3E,0x3E,0x00,0x00,0x08,0x21,0x88,0x71,
0x48,0x29,0x39,0x25,0x0E,0x23,0x08,0x21,0xC8,0x28,0x08,0x70,0x08,0x00,0x00,0x00,//"弦",3
/* (16 X 16 , 宋体 ) */
0x00,0x20,0x04,0x20,0x84,0x20,0x84,0x20,0x84,0x20,0x84,0x20,0x84,0x20,0x84,0x20,
0x84,0x20,0x84,0x20,0x84,0x20,0x84,0x20,0x84,0x20,0x04,0x20,0x00,0x20,0x00,0x00,//"三",4
/* (16 X 16 , 宋体 ) */

0x20,0x80,0x10,0x60,0xE8,0x1F,0x24,0x09,0x27,0x09,0x24,0x09,0x24,0x09,0xE4,0x7F,
0x24,0x09,0x34,0x09,0x2C,0x49,0x20,0x89,0xE0,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,//"角",5
/* (16 X 16 , 宋体 ) */

0x00,0x20,0x3E,0x3F,0x22,0x20,0xE2,0x1F,0x22,0x11,0x3E,0x11,0x00,0x00,0xFE,0x7F,
0x22,0x44,0x22,0x44,0x22,0x44,0x22,0x44,0x22,0x44,0xE2,0x47,0x02,0x40,0x00,0x00,//"距",6
/* (16 X 16 , 宋体 ) */

0x04,0x00,0x04,0xFE,0x04,0x02,0xF4,0x02,0x84,0x12,0xD4,0x3A,0xA5,0x16,0xA6,0x13,
0xA4,0x12,0xD4,0x1A,0x84,0x32,0xF4,0x42,0x04,0x82,0x04,0x7E,0x04,0x00,0x00,0x00,//"离",7
/* (16 X 16 , 宋体 ) */

0x00,0x00,0x00,0x00,0x00,0x36,0x00,0x36,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//"：",8
/* (16 X 16 , 宋体 ) */
};


/*  功能：计算 m 的 n 次幂
 *
 */
uint32_t oled_pow(uint8_t m,uint8_t n)
{
    uint32_t result=1;
    while(n--)result*=m;
    return result;
}

/*  功能：向SSD1106写入一个字节
 *   dat:要写入的数据/命令
 *   cmd:数据/命令标志 0,表示命令;1,表示数据;
 */
void OLED_WR_Byte(uint8_t dat,uint8_t cmd)
{
    uint8_t i;
    if(cmd)
      GPIO_write(DC,1);  //DC
    else
      GPIO_write(DC,0);
    GPIO_write(C_S,0);//拉低片选信号  C_S
    for(i=0;i<8;i++)
    {
        GPIO_write(D0,0);//拉低时钟信号 D0
        if(dat&0x80)//送进数据
           GPIO_write(D1,1);  //D1
        else
           GPIO_write(D1,0);
        GPIO_write(D0, 1);//抬高时钟信号
        dat<<=1;
    }
    GPIO_write(C_S,1);//抬高片选信号
    GPIO_write(DC,1);
}

/*  功能：设置汉字的显示位置
 *
 */
void OLED_Set_Pos_16x16(uint8_t x,uint8_t y)
{
    OLED_WR_Byte(0x21,OLED_CMD);//设置列地址;
    OLED_WR_Byte(0x00+x,OLED_CMD);//起始地址
    OLED_WR_Byte(0x00+x+15,OLED_CMD);//结束地址
    OLED_WR_Byte(0x22,OLED_CMD);//设置页地址
    OLED_WR_Byte(0x00+y,OLED_CMD);//起始地址
    OLED_WR_Byte(0x00+y+1,OLED_CMD);//结束地址

}

/*  功能：设置字符和字母的显示位置
 *
 */
void OLED_Set_Pos_8x16(uint8_t x,uint8_t y)
{

    OLED_WR_Byte(0x21,OLED_CMD);//设置列地址;
    OLED_WR_Byte(0x00+x,OLED_CMD);//起始地址
    OLED_WR_Byte(0x00+x+7,OLED_CMD);//结束地址
    OLED_WR_Byte(0x22,OLED_CMD);//设置页地址
    OLED_WR_Byte(0x00+y,OLED_CMD);//起始地址
    OLED_WR_Byte(0x00+y+1,OLED_CMD);//结束地址
}

/*  功能：开启OLED显示
 *
 */
void OLED_Display_On(void)
{

    OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
    OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
    OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON

}

/*  功能：关闭OLED显示
 *
 */
void OLED_Display_Off(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
    OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
    OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}

/*  功能：清屏
 *
 */
void OLED_Clear(void)
{
    uint8_t n,i;
    OLED_WR_Byte(0x21,OLED_CMD);
    OLED_WR_Byte(0x00,OLED_CMD);
    OLED_WR_Byte(0x7f,OLED_CMD);
    OLED_WR_Byte(0x22,OLED_CMD);
    OLED_WR_Byte(0x00,OLED_CMD);
    OLED_WR_Byte(0x07,OLED_CMD);
    //for(n=0;n<1024;n++)OLED_WR_Byte(0x00,OLED_DATA);
    for(i=0;i<8;i++)
    {
        for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA);
        ms_Delay(30);
    } //更新显示

}

/*  功能：显示字符
 *
 */
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr)
{
    uint8_t c=0,i=0;
    c=chr-'.';
    if(x>127){x=0;y=y+2;}
    OLED_Set_Pos_8x16(x,y);
    for(i=0;i<16;i++)
    {
        OLED_WR_Byte(F8x16[c*16+i],OLED_DATA);

    }
}

/*  显示整数
 *
 */
void OLED_ShowNum_int(uint8_t x,uint8_t y,uint32_t num)
{
    uint32_t t,temp,len;
    uint32_t Num=num;
    len=1;
    while(Num/10)
    {
        len++;
        Num=Num/10;
    }
    for(t=0;t<len;t++)
    {
        temp=(num/oled_pow(10,len-t-1))%10;
        OLED_ShowChar(x+8*t,y,temp+'0');//显示每一位

    }
}

/*  功能：显示浮点数
 *  x,y :起点坐标
 *  n:显示的小数部分位数
 *  num:数值
 */

void OLED_ShowNum_float(uint8_t x,uint8_t y,uint8_t n,float num)
{
    uint8_t len;
    uint32_t Num1,Num2,Num_Float;
    float num1,num2;
    Num1=Num2=(int)num;
    OLED_ShowNum_int(x,y,Num1);//整数部分
    len=1;
    while(Num1/10)
    {
        len++;
        Num1=Num1/10;
    }
    OLED_ShowChar(x+len*8,y,'.');//小数点
    num1=num-Num2;
    num2=num1*oled_pow(10,n);
    //Num_Float=(int)((num-Num2)*oled_pow(10,n));
    Num_Float=(int)num2;
    OLED_ShowNum_int(x+(len+1)*8,y,Num_Float);//小数部分

}

/*  功能：显示字符串
*   x : uint8_t 起点列坐标
*   y : uint8_t 起点行坐标
*   chr : uint8_t *字符串指针
*/
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr)
{
    uint8_t j=0;
    while (chr[j]!='\0')
    {       OLED_ShowChar(x,y,chr[j]);
            x+=8;
            if(x>120){x=0;y+=2;}//下一行
            j++;
    }
}

/*  功能：显示汉字
 *
 */
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no)
{
    uint8_t t;
     OLED_Set_Pos_16x16(x,y);
     for(t=0;t<32;t++)
     {
         OLED_WR_Byte(F16x16[32*no+t],OLED_DATA);
     }
}

/*  功能：OLED初始化
 *
 */
void OLED_Init(void)
{
    GPIO_write(RES,1);//RES
    usleep(100000);
    GPIO_write(RES,0);
    usleep(100000);
    GPIO_write(RES,1);
    OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
    OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
    OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
    OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
    OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
    OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
    OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
    OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
    OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
    OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
    OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset   Shift Mapping RAM Counter (0x00~0x3F)
    OLED_WR_Byte(0x00,OLED_CMD);//-not offset
    OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
    OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
    OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
    OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
    OLED_WR_Byte(0x12,OLED_CMD);
    OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
    OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
    OLED_WR_Byte(0x20,OLED_CMD);//-Set Vertical Mode (0x00/0x01/0x02)
    OLED_WR_Byte(0x01,OLED_CMD);//
    OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
    OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
    OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
    OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7)
    OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
    OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/
    OLED_Clear();

}




