/*
 * Copyright (c) 2016, Texas Instruments Incorporated
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

//*****************************************************************************
//
//! \addtogroup mqtt_server
//! @{
//
//*****************************************************************************
/* Standard includes                                                         */
#include <stdlib.h>

/* Kernel (Non OS/Free-RTOS/TI-RTOS) includes                                */
#include "pthread.h"
#include "mqueue.h"

/* Common interface includes                                                 */
#include "uart_term.h"

/* Application includes                                                      */
#include "client_cbs.h"
#include "mqtt_queue.h"
#include "debug.h"
#include "jsmn.h"
#include <ti/drivers/dpl/HwiP.h>
#include "sensors_queue.h"
//extern bool gResetApplication;

//*****************************************************************************
//                          LOCAL DEFINES
//*****************************************************************************
#define APP_PRINT               Report

#define OS_WAIT_FOREVER         (0xFFFFFFFF)
#define OS_NO_WAIT              (0)
#define OS_OK                   (0)

#define MQTTClientCbs_ConnackRC(data) (data & 0xff) 
/**< CONNACK: Return Code (LSB) */

//*****************************************************************************
//                 GLOBAL VARIABLES
//*****************************************************************************

/* Message Queue                                                              */
//extern mqd_t g_PBQueue;
//extern char *topic[];

struct client_info client_info_table[MAX_CONNECTION];

//*****************************************************************************
//                 Queue external function
//*****************************************************************************
//extern int32_t MQTT_SendMsgToQueue(struct msgQueue *queueElement);


static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
  if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
      strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
    return 0;
  }
  return -1;
}

//****************************************************************************
//                      CLIENT CALLBACKS
//****************************************************************************

//*****************************************************************************
//
//! Callback in case of various event (for clients connection with remote
//! broker)
//!
//! \param[in]  event       - is a event occurred
//! \param[in]  metaData    - is the pointer for the message buffer
//!                           (for this event)
//! \param[in]  metaDateLen - is the length of the message buffer
//! \param[in]  data        - is the pointer to the buffer for data
//!                           (for this event)
//! \param[in]  dataLen     - is the length of the buffer data
//!
//! return none
//
//*****************************************************************************
void MqttClientCallback(int32_t event,
                        void * metaData,
                        uint32_t metaDateLen,
                        void *data,
                        uint32_t dataLen)
{
    bool test;
    test = HwiP_inISR();
    TaskHandle_t testHandle = xTaskGetCurrentTaskHandle();
    int32_t i = 0;
//    dbgOutputLoc(MQTT_CALLBACK_PRE_LOC);
    switch((MQTTClient_EventCB)event)
    {
    case MQTTClient_OPERATION_CB_EVENT:
    {
        switch(((MQTTClient_OperationMetaDataCB *)metaData)->messageType)
        {
        case MQTTCLIENT_OPERATION_CONNACK:
        {
            uint16_t *ConnACK = (uint16_t*) data;
            //APP_PRINT("CONNACK:\n\r");
            /* Check if Conn Ack return value is Success (0) or       */
            /* Error - Negative value                                 */
            if(0 == (MQTTClientCbs_ConnackRC(*ConnACK)))
            {
                //APP_PRINT("Connection Success\n\r");
            }
            else
            {
                //APP_PRINT("Connection Error: %d\n\r", *ConnACK);
            }
            break;
        }

        case MQTTCLIENT_OPERATION_EVT_PUBACK:
        {
            char *PubAck = (char *) data;
//            APP_PRINT("PubAck:\n\r");
//            APP_PRINT("%s\n\r", PubAck);
            break;
        }

        case MQTTCLIENT_OPERATION_SUBACK:
        {
//            APP_PRINT("Sub Ack:\n\r");
//            APP_PRINT("Granted QoS Levels are:\n\r");
            for(i = 0; i < dataLen; i++)
            {
                //APP_PRINT("%s :QoS %d\n\r", topic[i],
                   //       ((unsigned char*) data)[i]);
            }
            break;
        }

        case MQTTCLIENT_OPERATION_UNSUBACK:
        {
            char *UnSub = (char *) data;
//            APP_PRINT("UnSub Ack \n\r");
//            APP_PRINT("%s\n\r", UnSub);
            break;
        }

        default:
            break;
        }
        break;
    }
    case MQTTClient_RECV_CB_EVENT:
    {
//        dbgOutputLoc(MQTT_CALLBACK_RECV_PRE_LOC);
        char msg_board[BOARD_ID_LENGTH];
        char message_ID[MSG_ID_LENGTH];
        char message_content[MSG_DATA_LENGTH];//should be 256 or bigger. but currently 128
//        char pubBuff[MSG_DATA_LENGTH];//MSG_DATA_LENGTH 256
//        memcpy((void*) (pubBuff), (const void*)data , dataLen);
        int i;
        int r;
        jsmn_parser p;
        jsmntok_t t[TOKEN_SIZE]; /* We expect no more than 128 tokens */

        jsmn_init(&p);
        r = jsmn_parse(&p, (char*)data, dataLen, t,
                       sizeof(t) / sizeof(t[0]));
        if (r < 1){
            dbgTerminalError();
            break;
        }
        uint32_t data_length;
        uint32_t msgID_length;
        for (i = 1; i < r; i++)
        {
            if (jsoneq(data, &t[i], "PUB_Board_ID") == 0)
            {
                /* We may use strndup() to fetch string value */
                memcpy((void*) msg_board, (const void *)(data+t[i+1].start), t[i+1].end - t[i+1].start);
//                memset((void*) (msg_board+ t[i+1].end - t[i+1].start + 1), '\0', 1);
                i++;
            }
            else if (jsoneq(data, &t[i], "Message_ID") == 0)
            {
                msgID_length = t[i+1].end - t[i+1].start;
                /* We may want to do strtol() here to get numeric value */
                memcpy((void*) (message_ID), (const void *)data + t[i+1].start, t[i+1].end - t[i+1].start);
                //memset((void*) (message_ID + t[i+1].end - t[i+1].start + 1), '\0', 1);
                i++;
            }
            else if (jsoneq(data, &t[i], "Message_Content") == 0)
            {
                data_length = t[i+1].end - t[i+1].start;
                memcpy((void*) (message_content), (const void *)data + t[i+1].start, t[i+1].end - t[i+1].start);
                //memset((void*) (message_content + t[i+1].end - t[i+1].start + 1), '\0', 1);
                i++;
            }
        }
        MQTTClient_RecvMetaDataCB *recvMetaData =
                (MQTTClient_RecvMetaDataCB *) metaData;
        msgQueue_t queueElem;
        /* filling the queue element details                              */
        queueElem.event = MSG_RECV_BY_CLIENT;
        memcpy((queueElem.msgPtr), message_content, sizeof(message_content));
        queueElem.dataLen = data_length;
        memcpy((queueElem.board_id), msg_board,  BOARD_ID_LENGTH);
        memcpy((queueElem.message_id), message_ID, msgID_length);
        memset((void*) (queueElem.message_id + msgID_length), '\0', 1);
        //queueElem.message_id = message_ID;
        /* signal to the main task                                        */
        if (recvMetaData->retain)
        {
            //APP_PRINT("Retained\n\r");
            queueElem.isRetain = true;
        }
        else
        {
            queueElem.isRetain = false;
        }

        if (recvMetaData->dup)
        {
            //APP_PRINT("Duplicate\n\r");
        }
        sendMsgToStatQueue(&queueElem);
        if(strncmp(msg_board, "rocky", 5) == 0){
            msgQueue_sensor armToSensors;
            armToSensors.dataType = ARM_MSG_TYPE;
            sendMsgToSensorQ(&armToSensors);
        }
        //sendMsgToRoverQueue(&queueElem);



//        dbgOutputLoc(MQTT_CALLBACK_RECV_POST_LOC);
        break;
    }
    case MQTTClient_DISCONNECT_CB_EVENT:
    {
        //gResetApplication = true;
        //APP_PRINT("BRIDGE DISCONNECTION\n\r");
        break;
    }
    }
//    dbgOutputLoc(MQTT_CALLBACK_POST_LOC);
}


//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
