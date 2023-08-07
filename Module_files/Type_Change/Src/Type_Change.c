/*
 *	File_Name:Type_Change.c
 *	Author:������
 *	Date:2023��7��17��
 *	Declaration:δ��������ֹ������ҵ��;
 */


/* Header files */
#include "Module_files/Type_Change/Inc/Type_Change.h"
#include "math.h"


/*======= Int_to_byte ===============
 * ���ܣ�����ת��Ϊ�ֽ� LSB����
 */
void Int_to_Byte(int i,uint8_t *byte)
{

  unsigned long longdata = 0;
  longdata = *(unsigned long*)&i;
  byte[3] = (longdata & 0xFF000000) >> 24;  /// �߰�λ
  byte[2] = (longdata & 0x00FF0000) >> 16;
  byte[1] = (longdata & 0x0000FF00) >> 8;
  byte[0] = (longdata & 0x000000FF);        /// �Ͱ�λ

}

/*======= Float_to_byte ===============
 * ���ܣ�������ת��Ϊ�ֽ�
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
 * ���ܣ�������ת��Ϊ�ֽ�
 */
void Short_to_Byte(short s,uint8_t *byte)
{

  byte[1] = (s & 0xFF00) >> 8;
  byte[0] = (s & 0xFF);
}





/*====== Num2Char =======
 * ���ܣ���0X00-0X09 0x0A-0X0F ת��Ϊ�ַ�'0-9' 'A-F'
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
 * ���ܣ���һ��ʮ���������е�0-9 A-F ת��Ϊ�ַ���
 *
 */
void Hex2String(uint8_t H,char * str)
{
    uint8_t High,Low;           /// ����λ�͵���λ
    High=H&0XF0;
    High=High>>4;
    Low=H&0X0F;
    Num2Char(High,str);
    Num2Char(Low,(str+1));
}

/*====== HexN2String() =======
 *  ���ܣ�������λ����ʮ���������е�0-9 A-F ת��Ϊ�ַ�����ƴ��
 *  HN:ʮ��������
 *  N:ʮ�����������ֽ���
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
 *  ���ܣ���ʮ���Ƹ����͵�С�����ֵ�λ��
 *
 *
 */
uint8_t FracPart_Len(float f)
{
    uint8_t i;
    float fp=f-(int)f;          /// ��С������
    for(i=0;;i++)
    {
        fp=fp*10;
        if(fp-(int)fp==0)
            break;
    }
    return i+1;
}


/*====== IntPart_Len() =======
 *  ���ܣ���ʮ���Ƹ����͵��������ֵ�λ��
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
 *  ���ܣ���ʮ���Ƹ�����ת��Ϊ�ַ���
 *  f:��ת���ĸ�����
 *  N:�����͵��������ֵĳ���
 *  str:ת������ַ�����ָ��
 *  L:ת�����������͵�С����λ���������㣬������ȥ
 *  ����Float     L       result
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
        *(str)=45;                  /// �������-
        f=abs(f);
        i=1;
    }
    else
    {
        *(str)=43;                  /// �������+
        i=1;
    }
    Ip=(int)f;                      /// ��������
    Fp=f-(int)f;                    /// С������
    while(Ip)                       /// ������ÿ��λ����ת��
    {
        Bit=Ip%10;
        *(str+N-1-i)=Bit+48;
        Ip=Ip/10;
        i++;
    }
    *(str+i)=46;                    /// ���С����
    j=i+1;
    while((Fp==0)||(j-i-1==L))        /// С����ÿ��λ����ת��
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


