/*
 * sensors_queue.h
 *
 *  Created on: 2019Äê11ÔÂ3ÈÕ
 *      Author: jiez
 */

#ifndef SENSORS_QUEUE_H_
#define SENSORS_QUEUE_H_

#include <FreeRTOS.h>
#include <queue.h>
#include "debug.h"
#include "mqtt_queue.h"
#define SENSOR_DATA_LENGTH 48
#define SENSOR_QUEUE_SIZE 16
#define SENSOR_MSG_SIZE sizeof(msgQueue_sensor)
#define PIXY_MSG_TYPE   0
#define ULTRA_MSG_TYPE  1
#define ROVER_MSG_TYPE  2
#define ARM_MSG_TYPE    3


QueueHandle_t sensor_queue;

typedef struct
{
    uint8_t data[SENSOR_DATA_LENGTH];
    int dataType;

} msgQueue_sensor;


void createSensorQ();
int sendMsgToSensorQ(msgQueue_sensor * aStruct);
int recieveMsgFromSensorQ( msgQueue_sensor *result);

#endif /* SENSORS_QUEUE_H_ */
