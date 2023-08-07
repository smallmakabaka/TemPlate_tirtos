/*
 *	File_Name:uart32_thread.c
 *	Author:胡尔勤
 *	Date:2023年7月20日
 *	Declaration:未经允许，禁止用于商业用途
 */

/* Includes */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>

/* POSIX Header Files */
#include <semaphore.h>
#include <mqueue.h>
#include <semaphore.h>

/* Driver Header Files */
#include <ti/drivers/GPIO.h>


/* Board Header file */
#include "ti_drivers_config.h"

/* Thread Header files */
#include <Threads/callbackThread/Inc/callbacks.h>
#include <Threads/mainThread/Inc/main_thread.h>
#include <Threads/uartThread/Inc/uart_thread.h>
#include <Threads/uart32Thread/Inc/uart32_thread.h>
#include <Threads/lcdThread/Inc/lcd_thread.h>
#include <Threads/pcThread/Inc/pc_thread.h>



/* Module Header files */
#include <Module_files/Button/Inc/Button.h>
#include <Module_files/LED/Inc/LED.h>
#include <Module_files/UART/Inc/UART.h>
#include <Module_files/DataPackage/Inc/DaTaPackage.h>
#include <Module_files/Others/Inc/Others.h>
#include <Module_files/I2C/Inc/I2C.h>
#include <Module_files/Ganwei/Inc/Ganwei.h>
#include <Module_files/PID/Inc/PID.h>
#include <Module_files/Host/Inc/Host.h>
/* Global Variables */
pthread_t uart32thread_handler;
sem_t semUART32 , semUART32S , semGW;



void *uart32Thread(void *arg0)
{

    while(!ALLPolling);
//    while(!Mode);
//    if(Mode==Update_MODE)       /// 自动更新模式
//    {
//        LED_startBlinking(ledHandle1, 100, 3);
//        while(1)
//        {
//            Update_ANA();
//            msleep(5);
//            if(Mode!=Update_MODE)
//            {
//
//                break;
//            }
//        }
//    }
//    if(Mode==Trace_MODE)
//    {
//        LED_startBlinking(ledHandle2, 100, 3);
//        while(1)
//        {
//            TRACE_PID_ANA();
//            msleep(40);
//            if(Mode!=Trace_MODE)
//            {
//
//                break;
//            }
//        }
//    }


    while(1)
    {
        if(Rang==Rang_Off)
        {
            uartHandle1 = UART_open(UART1, &uartparams1);
            UART_write(uartHandle1, Rangbuff, 9);           /// 发送距离读取请求
            UART_read(uartHandle1, Disbuff, 9);             /// 读取距离
            Rang=Rang_On;
        }
        if(Mode==Update_MODE)
        {
            if(Car!=Car_Stop)
            {
                Pack2Stm(pwm , 0 , 0 , 0 , 0 , TX2STM_BUF , TX2STM_LEN);
                UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
                Car=Car_Stop;
                Car_Change=IS_Change;
            }
            pidS=PID_OFF;
            Update_ANA();
            msleep(5);
        }
        else if(Mode==Trace_MODE)
        {
            if(Car!=Car_Running)
            {
                Car=Car_Running;
                Car_Change=IS_Change;
            }
            if(pidS!=PID_ON)
            {
                pidS=PID_ON;
                PID_TurnOn();
            }
            Avoid_Abs();
            break;

//            TRACE_PID_ANA2();
//            msleep(20);
//            Avoid_Abs();
        }
        else if(Mode==Free_MODE)
        {
            if(Car!=Car_Stop)
            {
                Pack2Stm(pwm , 0 , 0 , 0 , 0 , TX2STM_BUF , TX2STM_LEN);
                UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
                Car=Car_Stop;
                Car_Change=IS_Change;
            }
            pidS=PID_OFF;
            msleep(10);
        }

    }
    return NULL;
}

/*=========== Read_Led() =============
 *  功能：读取LED值
 */
void Read_Led()
{

    LED_Buff[0]=GPIO_read(LED_L2)+48;
    LED_Buff[1]=GPIO_read(LED_L1)+48;
    LED_Buff[2]=GPIO_read(LED_M)+48;
    LED_Buff[3]=GPIO_read(LED_R1)+48;
    LED_Buff[4]=GPIO_read(LED_R2)+48;
    LED_Buff[5]=0x0A;

}



/*=========== Trace() =============
 *  功能：灰度传感器循迹
 */
void Trace()
{
    /*********** 读取传感器值 ************/


    L2=GPIO_read(LED_L2);
    L1=GPIO_read(LED_L1);
    M=GPIO_read(LED_M);
    R1=GPIO_read(LED_R1);
    R2=GPIO_read(LED_R2);


    /*********** 执行循迹动作 *************/
    if((L1==Black)&&(M==Black)&&(R1==Black))
    {
        Pack2Stm(speed , 45 , 45 , 45 , 45 , TX2STM_BUF , TX2STM_LEN);
        UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
    }
    else
    {
        if(L1==Black)                               /// 左转
        {

            Pack2Stm(speed , 40 , 10 , 40 , 10 , TX2STM_BUF , TX2STM_LEN);
            UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);

        }
        else if(L2==Black)
        {
            Pack2Stm(speed , 50 , 10 , 50 , 10 , TX2STM_BUF , TX2STM_LEN);
            UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
        }
        else if(R1==Black)                               /// 右转
        {
            Pack2Stm(speed , 10 , 40 , 10 , 40 , TX2STM_BUF , TX2STM_LEN);
            UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);

        }
        else if(R2==Black)                               /// 右转
        {
            Pack2Stm(speed , 10 , 50 , 10 , 50 , TX2STM_BUF , TX2STM_LEN);
            UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
        }
        else if(M==Black)                               /// 直走
        {
            Pack2Stm(speed , 45 , 45 , 45 , 45 , TX2STM_BUF , TX2STM_LEN);
            UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
        }
    }

}




/*========= Turn180() =======
 * 功能：转向180°，采用位置环控制各轮的移动距离来实现
 */
void Turn180()
{
//    Pack2Stm(position , 32 , -31 , 32 , -31 , TX2STM_BUF , TX2STM_LEN);           /// 四轮
    Pack2Stm(position , 19 , -18 , 19 , -18 , TX2STM_BUF , TX2STM_LEN);             /// 二轮
    UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
}

/*========= TurnL90() =======
 * 功能：左转90°，采用位置环控制各轮的移动距离来实现
 */
void TurnL90()
{
//    Pack2Stm(position , 16.5 , -15.5 , 16.5 , -15.5 , TX2STM_BUF , TX2STM_LEN); /// 四轮
    Pack2Stm(position , 9.5 , -9 , 9.5 , -9 , TX2STM_BUF , TX2STM_LEN); /// 二轮
    UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
}


/*========= TurnR90() =======
 * 功能：右转90°，采用位置环控制各轮的移动距离来实现
 */
void TurnR90()
{
    Pack2Stm(position , -9 , 9.5 , -9 , 9.5 , TX2STM_BUF , TX2STM_LEN);
    UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);

}


/*========= Pos() =======
 * 功能：采用位置环控制各轮的移动距离来实现
 */
void Pos(float x)
{
    Pack2Stm(position , x , x , x , x , TX2STM_BUF , TX2STM_LEN);
    UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
}

/*======== PID_ON() ========
 *  功能：开启PID
 */
void PID_TurnOn()
{
    Error_Last=0;
    Integral_error=0;
    BasicSp=50;
}

/*======== TRACE_PID_ANA() ========
 *  功能：模拟量PID循迹 , 不分Level
 */
void TRACE_PID_ANA()
{
    float out , error , Lspeed , Rspeed;
    uint8_t k , j;
    for(j=0;j<8;j++)
    {
        ANA_Mean[j]=0;
    }
    for(k=0;k<10;k++)
    {
        RE_ANA(ANA);
        for(j=0;j<8;j++)
        {
            ANA_Mean[j]=ANA_Mean[j]+ANA[j];
        }
        msleep(1);
    }
    for(j=0;j<8;j++)
    {
        ANA_Mean[j]=ANA_Mean[j]/10;
    }

    for(k=0;k<8;k++)
    {
        ANA_Norma[k]=(float)(ANA_Max[k]-ANA_Mean[k])/(ANA_Max[k]-ANA_Min[k]);           /// 归一化   黑最大
    }
    error=ANA_Norma[0]*(-8.0)+ANA_Norma[1]*(-4.0)+ANA_Norma[2]*(-2.0)+ANA_Norma[3]*(-1.0)+ANA_Norma[4]*(1.0)+ANA_Norma[5]*(2.0)+ANA_Norma[6]*(4.0)+ANA_Norma[7]*(8.0);
    if(PropidS==PID_OFF)
    {
        out=Position_PID(error,Trace_PID);          /// 直线循迹
//        if((error>6)||(error<-6))
//        {
//            PID_TurnOn();
//            PropidS=PID_ON;
//            pidS=PID_OFF;
//            LED_setOn(ledHandle3, 100);
//        }
    }
    else
    {
        out=Position_PID(error,TracePro_PID);       /// 弯道循迹
        TracePro_PID.PIDnum=TracePro_PID.PIDnum+1;
        if(TracePro_PID.PIDnum==20)
        {
            PID_TurnOn();
            pidS=PID_ON;    /// 开启PID
            PropidS=PID_OFF;
            TracePro_PID.PIDnum=0;
            LED_setOff(ledHandle3);
        }
    }

    Lspeed=BasicSp+out;
    Rspeed=BasicSp-out;
    Pack2Stm(speed , Rspeed , Lspeed , Rspeed , Lspeed , TX2STM_BUF , TX2STM_LEN);
    UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
    Dataf[0]=error;
    Dataf[1]=out;
    Trace_PID.kp=param1;
    Trace_PID.ki=param2;
    Trace_PID.kd=param3;

}





/*======== TRACE_PID_ANA2() ========
 *  功能：模拟量PID循迹，分Level
 */
void TRACE_PID_ANA2()
{
    float out , error , Lspeed , Rspeed;
    uint8_t k , j;
    for(j=0;j<8;j++)                                                                    /// 均值赋0
    {
        ANA_Mean[j]=0;
    }
    for(k=0;k<10;k++)                                                                   /// 读十次ANA，存储在均值中
    {
        RE_ANA(ANA);
        for(j=0;j<8;j++)
        {
            ANA_Mean[j]=ANA_Mean[j]+ANA[j];
        }
        msleep(1);
    }
    for(j=0;j<8;j++)
    {
        ANA_Mean[j]=ANA_Mean[j]/10;                                                     /// 计算均值
    }
    for(k=0;k<8;k++)
    {
        ANA_Norma[k]=(float)(ANA_Max[k]-ANA_Mean[k])/(ANA_Max[k]-ANA_Min[k]);           /// 归一化   黑最大
    }
    error=Calcu_ANA(ANA_Norma[0])*(-2.5)+Calcu_ANA(ANA_Norma[1])*(-2.0)+Calcu_ANA(ANA_Norma[2])*(-1.5)+Calcu_ANA(ANA_Norma[3])*(-0.5)+Calcu_ANA(ANA_Norma[4])*(0.5)+Calcu_ANA(ANA_Norma[5])*(1.5)+Calcu_ANA(ANA_Norma[6])*(2.0)+Calcu_ANA(ANA_Norma[7])*(2.5);

    if(PropidS==PID_OFF)
    {
        out=Position_PID(error,Trace_PID);          /// 直线循迹
//        if((error>6)||(error<-6))
//        {
//            PID_TurnOn();
//            PropidS=PID_ON;
//            pidS=PID_OFF;
//            LED_setOn(ledHandle3, 100);
//        }
    }
    else
    {
        out=Position_PID(error,TracePro_PID);       /// 弯道循迹
        TracePro_PID.PIDnum=TracePro_PID.PIDnum+1;
        if(TracePro_PID.PIDnum==20)
        {
            PID_TurnOn();
            pidS=PID_ON;    /// 开启PID
            PropidS=PID_OFF;
            TracePro_PID.PIDnum=0;
            LED_setOff(ledHandle3);
        }
    }

    Lspeed=BasicSp+out;
    Rspeed=BasicSp-out;
    Pack2Stm(speed , Rspeed , Lspeed , Rspeed , Lspeed , TX2STM_BUF , TX2STM_LEN);
    UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
    Dataf[0]=error;
    Dataf[1]=out;
    Trace_PID.kp=param1;
    Trace_PID.ki=param2;
    Trace_PID.kd=param3;
}


/*========= Calcu_ANA() ============
 *  功能：计算模拟量的Level
 */
float Calcu_ANA(float A)
{
    A=fabs(A);
    if(A<=0.33)
    {
        return 0;
    }
    else if(A<=0.66)
    {
        return A;
    }
    else
    {
        return 1;
    }

}

/*========= Avoid_Abs() ============
 *  功能：避障
 */

void Avoid_Abs()
{
//    if(Dis<=150)
//    {
        pidS=PID_OFF;
        Car=Car_Stop;
        Car_Change=IS_Change;
        Pack2Stm(pwm , 0 , 0 , 0 , 0 , TX2STM_BUF , TX2STM_LEN);        /// 先停车
        UART_write(uartHandle3, TX2STM_BUF, TX2STM_LEN);
        msleep(30);

        Car=Car_Left;
        Car_Change=IS_Change;                                           /// 左转
        TurnL90();
        sleep(2);

        Pos(30);                                                        /// 前进30cm
        sleep(2);

        Car=Car_Right;
        Car_Change=IS_Change;                                           /// 右转
        TurnR90();
        sleep(2);

        Pos(30);                                                        /// 前进30cm
        sleep(2);

        Car=Car_Right;
        Car_Change=IS_Change;                                           /// 右转
        TurnR90();
        sleep(2);

        Pos(50);                                                        /// 前进30cm
        sleep(2);

//    }
}

/*======== Update_ANA() ========
 *  功能：自动更新ANA的最大值和最小值
 */
void Update_ANA()
{
    uint8_t k;
    RE_ANA(ANA);
    for(k=0;k<8;k++)
    {
        if(ANA[k]<ANA_Min[k])           /// 更新最小值
            ANA_Min[k]=ANA[k];
        if(ANA[k]>ANA_Max[k])           /// 更新最大值
            ANA_Max[k]=ANA[k];
    }

}




/*========= Ping_32() ============
 *  功能：与STM32初始化同步
 */
void Ping_STM32()
{

    uint8_t cmd=0xAA;
    uint8_t scmd=0xA5;
    int rc;
    while(1)
    {
        UART_write(uartHandle3, &cmd, 1);
        UART_read(uartHandle3, &STM2RX_BUF, 1);
        if(STM2RX_BUF==0x66)
        {
            UART_write(uartHandle3, &scmd, 1);
            rc = sem_post(&semUART32S);                            /// 释放信号
            if (rc == -1)
            {
                while (1);
            }

            Display_printf(hosthandle, 0, 0, "STM32 Ping Success");
//            LED_startBlinking(ledHandle1, 100, 2);
            break;
        }
        msleep(10);

    }
}


/*========= Ping() ===============
 *  功能：使传感器初始化和主控初始化同步
 */
void Ping_Ganwei()
{
    uint8_t data;
    int rc;
    while(1)
    {

        WR_CMD(0xAA);
        RE_DATA(&data , 1);
        if(data==0x66)
        {
            rc = sem_post(&semGW);                            /// 释放信号
            if (rc == -1)
            {
                while (1);
            }
            Display_printf(hosthandle, 0, 0, "Ganwei Ping Success");
//            LED_startBlinking(ledHandle2, 100, 2);
            break;
        }
    }

}

/*========= Ganwei_INIT() ===============
 *  功能：感为传感器初始化
 */
void Ganwei_INIT()
{
    Ping_Ganwei();
//    SET_Gray(0xD0, GrayB);      /// 设定滞回比较器参数
//    SET_Gray(0xD1, GrayW);
    CH_EN(0xFF);                /// 传输通道使能
    CH_NOR(0x00);               /// 传输通道归一化使能
//    RE_ERROR();                 /// 读取错误信息
//    RE_DIG(&DIG);               /// 读取数字信号
    RE_ANA(ANA);                /// 读取模拟信号

}




