/*
 * pixy_queue.c
 *
 *  Created on: 2019Äê9ÔÂ29ÈÕ
 *      Author: jiez
 */


#include "pixy_queue.h"



void createPixyQ()
{
    pixyQ = xQueueCreate(PIXY_QUEUE_SZ, PIXY_MSG_SZ);
    if(pixyQ == NULL){
        //while(1);
        dbgTerminalError();
    }
}

int sendTimeMsgToPixyQ(unsigned int time_val)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    uint32_t msg [2];
    msg[0] = Q1_TIME_MSG_SIG;
    msg[1] = time_val;
    BaseType_t err = xQueueSendToBackFromISR(pixyQ, msg, &xHigherPriorityTaskWoken);
    if (err != pdPASS) {
        dbgTerminalError();
        //while(1);
    }
    //dbgOutputLoc(SEND_TIME_POST_LOC);
    return 1;
}

int sendI2CMsgToPixyQ(unsigned int i2cSuccess)
{
//    dbgOutputLoc(ISR_I2C_PRE_LOC);
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    uint32_t msg [2];
    msg[0] = Q1_I2C_MSG_SIG;
    msg[1] = i2cSuccess;
    BaseType_t err = xQueueSendToBackFromISR(pixyQ, msg, &xHigherPriorityTaskWoken);
    if (err != pdPASS) {
        dbgTerminalError();
        //while(1);
    }
//    dbgOutputLoc(ISR_I2C_POST_LOC);
    return 1;
}


int sendArmerMsgToPixyQ(unsigned int signal)
{
//    dbgOutputLoc(SEND_ARM_PRE_LOC);
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    uint32_t msg [2];
    msg[0] = Q1_ARMER_MSG_SIG;
    msg[1] = signal;
    BaseType_t err = xQueueSendToBackFromISR(pixyQ, msg, &xHigherPriorityTaskWoken);
    if (err != pdPASS) {
        dbgTerminalError();
        //while(1);
    }
//    dbgOutputLoc(SEND_ARM_POST_LOC);
    return 1;
}

int sendPixyMsgToPixyDataQ(unsigned int message)
{
//    dbgOutputLoc(SEND_PIXY_PRE_LOC);
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    uint32_t msg [2];
    msg[0] = Q2_PIXY_MSG_SIG;
    msg[1] = message;
    BaseType_t err = xQueueSendToBackFromISR(pixy_dataQ, msg, &xHigherPriorityTaskWoken);
    if (err != pdPASS) {
        dbgTerminalError();
        //while(1);
    }
//    dbgOutputLoc(SEND_PIXY_POST_LOC);
    return 1;
}
int recieveMsgFromPixyQ(uint32_t * sensor_pixy, uint32_t * i2cComplete)
{
//    dbgOutputLoc(RECIEVE_PRE_LOC);
    uint32_t result [2];

    BaseType_t err = xQueueReceive(pixyQ, result, portMAX_DELAY);

    if (err == pdFALSE) {
        dbgTerminalError();
    }
    switch(result[0]){
    case Q1_TIME_MSG_SIG:{
        *sensor_pixy = 0;
        *i2cComplete = 0;
//        dbgOutputLoc(RECIEVE_POST_LOC);
        return 1;
    }
    case Q1_I2C_MSG_SIG:{
        *sensor_pixy = 0;
        *i2cComplete = result[1];
//        dbgOutputLoc(RECIEVE_POST_LOC);
        return 2;
    }
//    case MQTT_CREATED_COMPLETE:{
//        *time = 0;
//        *sensor_pixy = 0;
//        *i2cComplete = 0;
//        *sensor_ultra = 0;
//        *isMqttReady = true;
//        return 4;
//    }
//    case ULTRA_SENSOR_MSG:{
//        *time = 0;
//        *sensor_pixy = 0;
//        *i2cComplete = 0;
//        *sensor_ultra = result[1];
//        return 5;
//    }
    default:
        return -1;
    }

}
int recieveMsgFromPixyDataQ(uint32_t * data)
{
    uint32_t result [2];

    BaseType_t err = xQueueReceive(pixy_dataQ, result, portMAX_DELAY);

    if (err == pdFALSE) {
        //dbgTerminalError();
    }
    switch(result[0]){
    case Q2_PIXY_MSG_SIG:{
        *data = result[1];
        return 1;
    }
    default:
        return -1;
    }

}


