/*
 * ultraSonar_main.h
 *
 *  Created on: 2019��11��2��
 *      Author: jiez
 */

#ifndef ULTRASONAR_MAIN_H_
#define ULTRASONAR_MAIN_H_

#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Timer.h>

/* Board Header file */
#include "Board.h"
#include <ti/drivers/UART.h>
#include "debug.h"
#include "sensors_queue.h"
#define SONIC_DATA_LENGTH 5
#define DISTANCE_LENGTH 3
#define SEND_SPEED      10
void insertionSort(uint32_t arr[], int n);

#endif /* ULTRASONAR_MAIN_H_ */


