/*
 * sensors_queue.c
 *
 *  Created on: 2019Äê11ÔÂ3ÈÕ
 *      Author: jiez
 */


#include "sensors_queue.h"

void createSensorQ()
{
    sensor_queue = xQueueCreate(SENSOR_QUEUE_SIZE, SENSOR_MSG_SIZE);
    if(sensor_queue == NULL){
        dbgTerminalError();
    }
}

int sendMsgToSensorQ(msgQueue_sensor * aStruct)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    BaseType_t err = xQueueSendToBackFromISR(sensor_queue, aStruct, &xHigherPriorityTaskWoken);
    if (err != pdPASS) {
        dbgTerminalError();
        //while(1);
    }
    //dbgOutputLoc(SEND_TIME_POST_LOC);
    return 1;
}

int recieveMsgFromSensorQ( msgQueue_sensor *result)
{
 //   dbgOutputLoc(RECIEVE_PRE_LOC);
//    dbgOutputLoc(RECV_FROM_QUEUE1_PRE_LOC);
    BaseType_t err = xQueueReceive(sensor_queue, result, portMAX_DELAY);

    if (err == pdFALSE) {
        dbgTerminalError();
    }
    switch(result->dataType){
    case PIXY_MSG_TYPE:{
        return 0;
    }
    case ULTRA_MSG_TYPE:{
        return 1;
    }
    case ROVER_MSG_TYPE:{
        return 2;
    }
    case ARM_MSG_TYPE:{
        return 3;
    }
    case MQTT_CREATED_COMPLETE:{
        return 4;
    }
    default:
        return -1;
    }

//    dbgOutputLoc(RECV_FROM_QUEUE1_POST_LOC);

}



