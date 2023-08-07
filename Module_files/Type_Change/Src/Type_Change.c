/*
 *	File_Name:Type_Change.c
 *	Author:胡尔勤
 *	Date:2023年7月17日
 *	Declaration:未经允许，禁止用于商业用途
 */


/* Header files */
#include "Module_files/Type_Change/Inc/Type_Change.h"
#include "math.h"


/*======= Int_to_byte ===============
 * 功能：整型转换为字节 LSB优先
 */
void Int_to_Byte(int i,uint8_t *byte)
{

  unsigned long longdata = 0;
  longdata = *(unsigned long*)&i;
  byte[3] = (longdata & 0xFF000000) >> 24;  /// 高八位
  byte[2] = (longdata & 0x00FF0000) >> 16;
  byte[1] = (longdata & 0x0000FF00) >> 8;
  byte[0] = (longdata & 0x000000FF);        /// 低八位

}

/*======= Float_to_byte ===============
 * 功能：浮点型转换为字节
 */
void Float_to_Byte(float f,uint8_t *byte)
{

  unsigned long longdata = 0;
  longdata = *(unsigned long*)&f;
  byte[3] = (longdata & 0xFF000000) >> 24;
  byte[2] = (longdata & 0x00FF0000) >> 16;
  byte[1] = (longdata & 0x0000FF00) >> 8;
  byte[0] = (longdata & 0x000000FF);

}

/*======= Short_to_byte ===============
 * 功能：短整型转换为字节
 */
void Short_to_Byte(short s,uint8_t *byte)
{

  byte[1] = (s & 0xFF00) >> 8;
  byte[0] = (s & 0xFF);
}





/*====== Num2Char =======
 * 功能：将0X00-0X09 0x0A-0X0F 转换为字符'0-9' 'A-F'
 *
 */
void Num2Char(uint8_t num,char * c)
{
    if(num<=9)
    {
        *c=num+48;
    }
    if(num<=15&&num>=10)
    {
        *c=num+55;
    }
}

/*====== Hex2String() =======
 * 功能：将一个十六进制数中的0-9 A-F 转换为字符串
 *
 */
void Hex2String(uint8_t H,char * str)
{
    uint8_t High,Low;           /// 高四位和低四位
    High=H&0XF0;
    High=High>>4;
    Low=H&0X0F;
    Num2Char(High,str);
    Num2Char(Low,(str+1));
}

/*====== HexN2String() =======
 *  功能：将给定位数的十六进制数中的0-9 A-F 转换为字符串并拼接
 *  HN:十六进制数
 *  N:十六进制数的字节数
 */
void HexN2String(uint8_t * HN,uint16_t N,char * strs)
{
    uint8_t i;
    for(i=0;i<N;i++)
    {
        Hex2String(*(HN+i),strs+2*i);
    }
}

/*====== FracPart_Len() =======
 *  功能：求十进制浮点型的小数部分的位数
 *
 *
 */
uint8_t FracPart_Len(float f)
{
    uint8_t i;
    float fp=f-(int)f;          /// 求小数部分
    for(i=0;;i++)
    {
        fp=fp*10;
        if(fp-(int)fp==0)
            break;
    }
    return i+1;
}


/*====== IntPart_Len() =======
 *  功能：求十进制浮点型的整数部分的位数
 *
 *
 */
uint8_t IntPart_Len(float f)
{
    uint8_t i;
    i=0;
    int Ip=(int)f;
    while(Ip)
    {
        Ip=Ip/10;
        i++;
    }
    return i;
}

/*====== Float2String() =======
 *  功能：将十进制浮点型转换为字符串
 *  f:需转换的浮点型
 *  N:浮点型的整数部分的长度
 *  str:转换后的字符串的指针
 *  L:转换保留浮点型的小数的位数，少则补零，多则舍去
 *  例：Float     L       result
 *      3.314     2       3.31
 *      3.314     4       3.3140
 */
void Float2String(float f,uint8_t N,char * str,uint8_t L)
{
    uint8_t i,j,Bit;
    int Ip;
    float Fp;

    if(f<0)
    {
        *(str)=45;                  /// 负数添加-
        f=abs(f);
        i=1;
    }
    else
    {
        *(str)=43;                  /// 正数添加+
        i=1;
    }
    Ip=(int)f;                      /// 整数部分
    Fp=f-(int)f;                    /// 小数部分
    while(Ip)                       /// 整数的每个位依次转换
    {
        Bit=Ip%10;
        *(str+N-1-i)=Bit+48;
        Ip=Ip/10;
        i++;
    }
    *(str+i)=46;                    /// 添加小数点
    j=i+1;
    while((Fp==0)||(j-i-1==L))        /// 小数的每个位依次转换
    {
        Fp=Fp*10;
        Bit=(int)Fp;
        *(str+j)=Bit+48;
        Fp=Fp-(int)Fp;
        j++;

    }
    while(j-i-1<L)
    {
        *(str+j)=48;
        j++;
    }

}


