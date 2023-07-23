/*
 * Copyright (c) 2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== led_thread.c ========
 */

/* Includes */
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <ti/devices/msp432p4xx/inc/msp.h>

/* POSIX Header files */
#include <pthread.h>
#include <mqueue.h>
#include <semaphore.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/PWM.h>
#include <ti/drivers/Timer.h>

/* Board Header file */
#include "ti_drivers_config.h"

/* Local Header Files */
#include <Threads/callbackThread/Inc/callbacks.h>
#include <Threads/ledThread/Inc/led_thread.h>
#include <Threads/mainThread/Inc/main_thread.h>
#include <Threads/uartThread/Inc/uart_thread.h>


/* Global Variables */
pthread_t ledthread_handler;
sem_t semLED;
mqd_t  mqLED;




/*
 *  ======== ledThread ========
 *  Creates the PWM modules for RGB color setting.
 *  Creates individual threads for changing the blink
 *   rate, color and ON/OFF state of the LED.
 */
void *ledThread(void *arg0)
{

    LedMsg msg;
    int retc;

    while (1)
    {
        /* Wait for a change to occur */
        retc = sem_wait(&semLED);
        if (retc == 0)
        {
            retc = mq_receive(mqLED, (char *)&msg, sizeof(msg), NULL);
            if (retc != -1)
            {


            }
        }
    }
}
