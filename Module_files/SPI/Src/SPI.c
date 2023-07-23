/*
 *	File_Name:SPI.c
 *	Author:胡尔勤
 *	Date:2023年7月20日
 *	Declaration:未经允许，禁止用于商业用途
 */

/*======== SPI_INIT() ==========
 *  功能：SPI初始化
 *  三线SPI，CS软件控制
 *  引脚：SPI（MOSI、MISO、SCL）、GPIO(RES、CS、DC（命令数据切换）、BLK（背光控制）)
 */

#include "SPI.h"
void SPI_INIT()
{

    SPI_init();                                 // Initialize the SPI driver
    SPI_Params_init(&spiParams);                // Initialize SPI parameters
    spiParams.mode=SPI_MASTER;                  // 主模式
    spiParams.frameFormat= SPI_POL0_PHA0;       // 极性 1 相位 1
    spiParams.dataSize = 8;                     // 8位数据帧
    spiParams.transferMode=SPI_MODE_BLOCKING;   // 阻塞
    spihandle1 = SPI_open(SPI_1, &spiParams);
    if (spihandle1 == NULL)
    {
        while (1);  // SPI_open() failed
    }


    spiParams.mode=SPI_MASTER;                  // 主模式
    spiParams.frameFormat= SPI_POL0_PHA0;       // 极性 1 相位 1
    spiParams.dataSize = 8;                     // 8位数据帧
    spiParams.transferMode=SPI_MODE_BLOCKING;   // 阻塞
    spihandle2 = SPI_open(SPI_2, &spiParams);
    if (spihandle2 == NULL)
    {
        while (1);  // SPI_open() failed
    }

}
