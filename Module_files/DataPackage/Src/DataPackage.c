/*
 *	File_Name:DataPackage.c
 *	Author:胡尔勤
 *	Date:2023年7月17日
 *	Declaration:未经允许，禁止用于商业用途
 */

/* Header files */
#include "string.h"
#include "stdio.h"
#include "Module_files/Type_Change/Inc/Type_Change.h"
#include "Module_files/DataPackage/Inc/DataPackage.h"
#include "Module_files/UART/Inc/UART.h"
/*======== DATApack() ==========
 *  功能：浮点型数据打包成字符串，末尾加\n
 *  f：输入浮点型数组
 *  N：浮点型数组的长度
 *  L：对应浮点型数组的整数的长度数组
 *  示例："，-10.5，-20.4，-30.6，\n"
 */
void DATApack(float * f,uint8_t N,uint8_t * L,char * str)
{
    uint8_t i,l,lp;
    lp=0;
    for(i=0;i<N;i++)
    {
        l=*(L+i);
        *(str+lp)=44;                               /// 添加逗号
        Float2String(*(f+i), l , str+lp+1 , decL);
        lp=l+4+1+lp;
    }
    *(str+lp)=44;                                   /// 添加逗号
    *(str+lp+1)=0X0A;                              /// 添加换行符
}



/*======== ble_packup =========
 * 功能：打包数据
 */
//void packup32(uint8_t boolnum,uint8_t bytenum,uint8_t shortnum,uint8_t intnum, uint8_t floatnum,uint8_t *bl,uint8_t *by, short *sh, int *in, float *fl)
//{
//    USART_TX_BUF[0] = 0xA5;                 /// 包头
//    USART_TX_BUF[USART_TX_LEN-2]= 0;        /// 校验和（所有位的和取低八位）
//    USART_TX_BUF[USART_TX_LEN-1] = 0x5A;    /// 包尾
//    if(boolnum+bytenum+shortnum*2+intnum*4+floatnum*4+3!=USART_TX_LEN)
//    {
////      printf('error');
//    }
//    else
//    {
//        int i;
//        for(i=0;i<boolnum;i++)
//        {
//            USART_TX_BUF[0+i+1]=bl[i];
//        }
//        for(i=0;i<bytenum;i++)
//        {
//            USART_TX_BUF[boolnum+i+1]=by[i];
//        }
//        for(i=0;i<shortnum;i++)
//        {
//            Short_to_Byte(sh[i],&USART_TX_BUF[boolnum+bytenum+i+1]);
//        }
//        for(i=0;i<intnum;i++)
//        {
//            Int_to_Byte(in[i],&USART_TX_BUF[boolnum+bytenum+shortnum*2+i+1]);
//        }
//        for(i=0;i<floatnum;i++)
//        {
//            Float_to_Byte(fl[i],&USART_TX_BUF[boolnum+bytenum+shortnum*2+intnum*4+i+1]);
//        }
//        for(i=1;i<USART_TX_LEN-2;i++)
//        {
//             USART_TX_BUF[USART_TX_LEN-2]=USART_TX_BUF[USART_TX_LEN-2]+USART_TX_BUF[i];
//        }
//        USART_TX_BUF[USART_TX_LEN-2]=(uint8_t)(USART_TX_BUF[USART_TX_LEN-2]&0xff);
//    }
//
//}

void Pack2Stm(uint8_t wm , float f1 , float f2 , float f3 , float f4 , uint8_t * txbuff , uint8_t len)
{
    uint8_t i;
    *(txbuff)= 0xA5;                 /// 包头
    *(txbuff+len-2)= 0;             /// 校验和（所有位的和取低八位）
    *(txbuff+len-1) = 0x5A;         /// 包尾
    *(txbuff+1)=wm;                 /// 依次赋字节
    Float_to_Byte(f1,txbuff+2);     /// 浮点型赋字节
    Float_to_Byte(f2,txbuff+6);
    Float_to_Byte(f3,txbuff+10);
    Float_to_Byte(f4,txbuff+14);
    for(i=1;i<len-2;i++)
    {
         *(txbuff+len-2)=*(txbuff+len-2)+*(txbuff+i);
    }
    *(txbuff+len-2)=(uint8_t)((*(txbuff+len-2))&0xff);

}


