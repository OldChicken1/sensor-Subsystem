/*
 * mqtt_queue.h
 *
 *  Created on: 2019Äê10ÔÂ13ÈÕ
 *      Author: jiez
 */

#ifndef MQTT_QUEUE_H_
#define MQTT_QUEUE_H_

#include <FreeRTOS.h>
#include <queue.h>
#include "client_cbs.h"
#include "debug.h"
#include "pixy_queue.h"

#define Q1_MSG_SZ sizeof(msgQueue_t2)
#define Q2_MSG_SZ sizeof(msgQueue_t)
#define Q1_QUEUE_SZ 16
#define Q2_QUEUE_SZ 16

#define MQTT_CREATED_COMPLETE 0x87654321

QueueHandle_t mqtt_queue;
QueueHandle_t rover_queue;
QueueHandle_t stat_queue;

void createMqttQ();
void createRoverQ();
void createStatQ();
int sendMqttFinishToSensorQ();
int32_t sendMsgToMqtt( msgQueue_t2 *queueElement);
int32_t sendMsgToRoverQueue(msgQueue_t* queueElement);
int32_t sendMsgToStatQueue(msgQueue_t * queueElement);
void recieveMsgFromMqtt( msgQueue_t2 *queueElement);
void recieveMsgFromRoverQ(msgQueue_t* queueElement);
void recieveMsgFromStatQueue( msgQueue_t *result);

#endif /* MQTT_QUEUE_H_ */
