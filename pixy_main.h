/*
 * pixy_main.h
 *
 *  Created on: 2019Äê10ÔÂ30ÈÕ
 *      Author: jiez
 */

#ifndef PIXY_MAIN_H_
#define PIXY_MAIN_H_
#include <stddef.h>
#include <pthread.h>
#include <stdbool.h>
/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Timer.h>
//#include "queue.h"
/* Board Header file */
#include "Board.h"
#include <ti/drivers/I2C.h>
#include "timer_pixy.h"
#include "pixy_queue.h"
#include <ti/drivers/UART.h>
#include "sensors_queue.h"
#include "debug.h"
#include "sensors_state.h"

#define BAUD 115200
#define PIXY_MSG_SZ 8
#define PIXY_QUEUE_SZ 16
#define TXBUFFERSIZE  6
#define RXBUFFERSIZE  48

void *pixyRead(void *arg0);



#endif /* PIXY_MAIN_H_ */
