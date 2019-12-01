/*
 * pixy_queue.h
 *
 *  Created on: 2019Äê9ÔÂ29ÈÕ
 *      Author: jiez
 */

#ifndef PIXY_QUEUE_H_
#define PIXY_QUEUE_H_

#include <FreeRTOS.h>
#include <queue.h>
#include "debug.h"
#include "mqtt_queue.h"

#define PIXY_MSG_SZ 8
#define PIXY_QUEUE_SZ 16
#define Q1_TIME_MSG_SIG 0x12340000
#define Q1_ARMER_MSG_SIG 0x00001234
#define Q1_I2C_MSG_SIG 0x12345678
#define Q2_PIXY_MSG_SIG 0x00004545
#define ULTRA_SENSOR_MSG 0x45450000

QueueHandle_t pixy_dataQ;
QueueHandle_t pixyQ;

void createPixyQ();
int sendTimeMsgToPixyQ(unsigned int time_val);
int sendI2CMsgToPixyQ(unsigned int i2cSuccess);
int sendArmerMsgToPixyQ(unsigned int signal);
int sendPixyMsgToPixyDataQ(unsigned int message);
int recieveMsgFromPixyQ(uint32_t * sensor_pixy, uint32_t * i2cComplete);
int recieveMsgFromPixyDataQ(uint32_t * data);

#endif /* PIXY_QUEUE_H_ */
