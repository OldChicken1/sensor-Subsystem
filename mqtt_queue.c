/*
 * pixy_queue.c
 *
 *  Created on: 2019Äê9ÔÂ29ÈÕ
 *      Author: jiez
 */


#include "mqtt_queue.h"
#include "sensors_queue.h"


void createMqttQ()
{
    mqtt_queue = xQueueCreate(Q1_QUEUE_SZ, Q1_MSG_SZ);
    if(mqtt_queue == NULL){
        dbgTerminalError();
    }
}

void createRoverQ()
{
    rover_queue = xQueueCreate(Q2_QUEUE_SZ, Q2_MSG_SZ);
    if(rover_queue == NULL){
        dbgTerminalError();
    }
}

void createStatQ()
{
    stat_queue = xQueueCreate(Q2_QUEUE_SZ, Q2_MSG_SZ);
    if (stat_queue == NULL)
    {
        dbgTerminalError();
    }
}
int sendMqttFinishToSensorQ()
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    msgQueue_sensor msg;
    msg.dataType = MQTT_CREATED_COMPLETE;
    BaseType_t err = xQueueSendToBackFromISR(sensor_queue, &msg, &xHigherPriorityTaskWoken);
    if (err != pdPASS) {
        //dbgTerminalError();
        while(1);
    }
    //dbgOutputLoc(SEND_TIME_POST_LOC);
    return 1;
}
int32_t sendMsgToMqtt( msgQueue_t2 *queueElement)
{
//    dbgOutputLoc(SEND_TO_QUEUE1_PRE_LOC);

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t err = xQueueSendToBackFromISR(mqtt_queue, queueElement, &xHigherPriorityTaskWoken);
    if (err != pdPASS) {
        //dbgTerminalError();
        dbgTerminalError();
    }
//    dbgOutputLoc(SEND_TO_QUEUE1_POST_LOC);
    //dbgOutputLoc(SEND_TIME_POST_LOC);
    return 1;
}

int32_t sendMsgToRoverQueue(msgQueue_t * queueElement)
{
//    dbgOutputLoc(SEND_TO_QUEUE2_PRE_LOC);
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t err = xQueueSendToBackFromISR(rover_queue, queueElement, &xHigherPriorityTaskWoken);
    if (err != pdPASS) {
        //dbgTerminalError();
        dbgTerminalError();
    }
//    dbgOutputLoc(SEND_TO_QUEUE2_POST_LOC);
    //dbgOutputLoc(SEND_TIME_POST_LOC);
    return 1;
}

int32_t sendMsgToStatQueue(msgQueue_t * queueElement)
{
    //dbgOutputLoc(SEND_TO_QUEUE2_PRE_LOC);
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t err = xQueueSendToBackFromISR(stat_queue, queueElement, &xHigherPriorityTaskWoken);
    if (err != pdPASS) {
        //dbgTerminalError();
        dbgTerminalError();
    }
    //dbgOutputLoc(SEND_TO_QUEUE2_POST_LOC);
    //dbgOutputLoc(SEND_TIME_POST_LOC);
    return 1;
}
void recieveMsgFromMqtt( msgQueue_t2 *result)
{
 //   dbgOutputLoc(RECIEVE_PRE_LOC);
//    dbgOutputLoc(RECV_FROM_QUEUE1_PRE_LOC);
    BaseType_t err = xQueueReceive(mqtt_queue, result, portMAX_DELAY);

    if (err == pdFALSE) {
        dbgTerminalError();
    }
//    dbgOutputLoc(RECV_FROM_QUEUE1_POST_LOC);

}

void recieveMsgFromRoverQ(msgQueue_t* queueElement)
{
//    dbgOutputLoc(RECV_FROM_QUEUE2_PRE_LOC);
    BaseType_t err = xQueueReceive(rover_queue, queueElement, portMAX_DELAY);

    if (err == pdFALSE) {
        dbgTerminalError();
    }
//    dbgOutputLoc(RECV_FROM_QUEUE2_POST_LOC);
}

void recieveMsgFromStatQueue( msgQueue_t *result)
{
 //   dbgOutputLoc(RECIEVE_PRE_LOC);
//    dbgOutputLoc(RECV_FROM_QUEUE1_PRE_LOC);
    BaseType_t err = xQueueReceive(stat_queue, result, portMAX_DELAY);

    if (err == pdFALSE) {
        dbgTerminalError();
    }
//    dbgOutputLoc(RECV_FROM_QUEUE1_POST_LOC);

}
