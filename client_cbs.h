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

#ifndef __SERVER_CLIENT_CBS_H__
#define __SERVER_CLIENT_CBS_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

/* MQTT library includes                                                      */
#include <ti/net/mqtt/mqttserver.h>
#include <ti/net/mqtt/mqttclient.h>
#include <stdio.h>
//#include "debug.h"
//*****************************************************************************
// Macros
//*****************************************************************************
#define MAX_CONNECTION              1

#define PUBLISH_PUSH_BUTTON_PRESSED 1
#define PROCESS_MSG                 2
#define STATS_MSG                   3
#define TARGETCHANGE_MSG            4
//#define LOST_OBJECT_MSG             4
//#define REFIND_OBJECT_MSG           5
#define DISTANCE_MSG                6
#define DISTANCE_WARNING_MSG        7
#define MSG_RECV_BY_CLIENT          11
/* Client disconnected from remote broker       */
#define LOCAL_CLIENT_DISCONNECTION  12 
#define DISC_PUSH_BUTTON_PRESSED    14
#define THREAD_TERMINATE_REQ        15
#define STATS_PUBLISH               16

#define MSG_DATA_LENGTH             256
#define BOARD_ID_LENGTH             5
#define MSG_ID_LENGTH               6
#define TOKEN_SIZE                  30
//*****************************************************************************
// typedef enum/struct/union
//*****************************************************************************
struct publishMsgHeader
{
    uint32_t topicLen;
    uint32_t payLen;
    bool retain;
    bool dup;
    unsigned char qos;
};

struct client_info
{
    void *ctx;
};

typedef struct
{
    int32_t event;
//    void        *msgPtr;
    char msgPtr[MSG_DATA_LENGTH];
//    uint32_t retained;
    bool isRetain;
    int32_t dataLen;
    char board_id[5];
    uint8_t message_id[6];
} msgQueue_t;

typedef struct
{
    int32_t event;
    uint32_t T1_miss_num;
    uint32_t T2_miss_num;
    uint32_t T3_miss_num;
    uint8_t state;
    uint8_t detection[3];
    uint8_t color[3];
    uint8_t direction[3];
    int angle[3];
    uint32_t blockSize[3];
    uint8_t trackIndex[3];
//    uint32_t data1;
//    uint32_t data2;
//    uint32_t data3;
    uint32_t distance;
//    int angle1;
//    int angle2;
//    int angle3;
//    bool isLostSight;
//    bool needRefind;
//    int color;
    int irDistance;
    bool shortDistWarn;
} msgQueue_t2;

//******************************************************************************
// APIs
//******************************************************************************

extern void MqttClientCallback(int32_t event,
                               void * metaData,
                               uint32_t metaDateLen,
                               void *data,
                               uint32_t dataLen);
//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __SERVER_CLIENT_CBS_H__
