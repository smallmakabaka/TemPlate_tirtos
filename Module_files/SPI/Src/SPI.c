/*
 *	File_Name:SPI.c
 *	Author:������
 *	Date:2023��7��20��
 *	Declaration:δ��������ֹ������ҵ��;
 */

/*======== SPI_INIT() ==========
 *  ���ܣ�SPI��ʼ��
 *  ����SPI��CS�������
 *  ���ţ�SPI��MOSI��MISO��SCL����GPIO(RES��CS��DC�����������л�����BLK��������ƣ�)
 */

#include "SPI.h"
void SPI_INIT()
{

    SPI_init();                                 // Initialize the SPI driver
    SPI_Params_init(&spiParams);                // Initialize SPI parameters
    spiParams.mode=SPI_MASTER;                  // ��ģʽ
    spiParams.frameFormat= SPI_POL0_PHA0;       // ���� 1 ��λ 1
    spiParams.dataSize = 8;                     // 8λ����֡
    spiParams.transferMode=SPI_MODE_BLOCKING;   // ����
    spihandle1 = SPI_open(SPI_1, &spiParams);
    if (spihandle1 == NULL)
    {
        while (1);  // SPI_open() failed
    }


    spiParams.mode=SPI_MASTER;                  // ��ģʽ
    spiParams.frameFormat= SPI_POL0_PHA0;       // ���� 1 ��λ 1
    spiParams.dataSize = 8;                     // 8λ����֡
    spiParams.transferMode=SPI_MODE_BLOCKING;   // ����
    spihandle2 = SPI_open(SPI_2, &spiParams);
    if (spihandle2 == NULL)
    {
        while (1);  // SPI_open() failed
    }

}
