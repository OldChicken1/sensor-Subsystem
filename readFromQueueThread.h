/*
 * readFromQueueThread.h
 *
 *  Created on: 2019��10��14��
 *      Author: jiez
 */

#ifndef READFROMQUEUETHREAD_H_
#define READFROMQUEUETHREAD_H_

#include <ti/drivers/UART.h>
#include "debug.h"
#include "client_cbs.h"

void *readFromQueue(void *arg0);


#endif /* READFROMQUEUETHREAD_H_ */
