/*
 * pixy_state.c
 *
 *  Created on: 2019��9��29��
 *      Author: jiez
 */

#include "sensors_state.h"

#define ROTATE_LEFT 1
#define ROTATE_RIGHT 2
#define LINE_UP 3
#define NONE 0

const uint32_t lookup[10] = { 841000, 770000, 669000, 596000, 534000, 498000,
                              455000, 417000, 399000, 366000 };
const double correspond[10] = { 12, 14, 16, 18, 20, 22, 24, 26, 28, 30 };

int sensor_fsm(sensor_state_fsm* aFsm, msgQueue_sensor* dataRecv)
{
    msgQueue_t2 dataToSend;

    uint8_t sensorData[SENSOR_DATA_LENGTH];
    int distance = 0;
//    uint8_t trackingIndex = 0;
    int targetCount = 0;
    uint8_t isDetected[3] = { 0, 0, 0 };
    uint32_t blockSize[3] = { 0, 0, 0 };
    int block_target[3] = { -1, -1, -1 };
    uint8_t trackingIndex[3] = { 0, 0, 0 };
    uint8_t direction[3] = { NONE, NONE, NONE };
    uint8_t color[3] = { 0, 0, 0 };
    int blockAngle[3] = { 0, 0, 0 };
    memcpy(sensorData, dataRecv->data, sizeof(sensorData));
    switch (aFsm->state)
    {
    case OBJECT_FINDING:
    {

        if (dataRecv->dataType == PIXY_MSG_TYPE)
        {
            if (sensorData[0] != 175 || sensorData[1] != 193)
            //  || sensorData[PIXY_BLOCKNUM_LOC] == 0)
            {
                break;
            }
            //detected something
            int blockCount = sensorData[PIXY_BLOCKNUM_LOC] / 14;
            int i;
            for (i = 0; i < blockCount; i++)
            {
                if ((sensorData[PIXY_SIG_LOC + i * 14] != 11
                        && sensorData[PIXY_SIG_LOC + i * 14] != 10
                        && sensorData[PIXY_SIG_LOC + i * 14] != 12)) //10 = blue green,  28 = red purple
                {
                    continue;
                }
                if (isDetected[0] == 0)
                {
                    isDetected[0] = 1;
                    block_target[0] = 0;
                    targetCount++;
                }
                else if (isDetected[1] == 0)
                {
                    isDetected[1] = 1;
                    block_target[1] = 1;
                    targetCount++;
                }
                else if (isDetected[2] == 0)
                {
                    isDetected[2] = 1;
                    block_target[2] = 2;
                    targetCount++;
                }

            }
            int j;
            for (j = 0; j < 3; j++)
            {
                double angle = 0;
                if (isDetected[j])
                {
                    blockSize[j] = sensorData[PIXY_WIDTH_LOC + j * 14]
                            * sensorData[PIXY_HEIGHT_LOC + j * 14];
                    trackingIndex[j] = sensorData[PIXY_TRACK_LOC
                            + block_target[j] * 14];
                    uint16_t object_x = sensorData[PIXY_XCOR_LOC
                            + block_target[j] * 14];
                    uint8_t object_x2 = sensorData[PIXY_XCOR_LOC + 1
                            + block_target[j] * 14];
                    if (object_x2 != 0)
                    {
                        object_x = object_x2 << 8 | object_x;
                    }
                    int32_t x_err = X_CENTER - object_x; //about 30cm away from the object
                    angle = ANGLE_MULTIPLE * x_err;
                    angle = angle + ANGLE_CONSTANT;
                    blockAngle[j] = (int) (angle + 0.5);
                    if (dataToSend.angle[j] < -2)
                    {
                        direction[j] = ROTATE_LEFT;
                    }
                    else if (dataToSend.angle[j] > 2)
                    {
                        direction[j] = ROTATE_RIGHT;
                    }
                    else
                    {
                        direction[j] = LINE_UP;
                        uint16_t adcValue0;
                        uint16_t res = ADC_convert(aFsm->adc, &adcValue0);
                        uint32_t adcValue0MicroVolt =
                        ADC_convertRawToMicroVolts(aFsm->adc, adcValue0);
                        int index;
                        for (index = 0;
                                index < sizeof(lookup) / sizeof(lookup[0]) - 1;
                                index++)
                        {
                            if (index == 0
                                    && lookup[index] < adcValue0MicroVolt)
                            {
                                distance = 10;
                                break;
                            }
                            if (index == sizeof(lookup) / sizeof(lookup[0]) - 2
                                    && lookup[index] > adcValue0MicroVolt)
                            {
                                distance = 32;
                                break;
                            }
                            if (lookup[index] >= adcValue0MicroVolt
                                    && lookup[index + 1] <= adcValue0MicroVolt)
                            {
                                uint32_t total = lookup[index + 1]
                                        - lookup[index];
                                uint32_t diff = adcValue0MicroVolt
                                        - lookup[index];
                                double portion = diff / total;
                                distance =
                                        (int) (portion * correspond[index]
                                                + (1 - portion)
                                                        * correspond[index + 1]);
                                break;
                            }
                        }

                        aFsm->reportUltra = true;

                    }
                    if (sensorData[PIXY_SIG_LOC + block_target[j] * 14] == 11)
                    {
                        color[j] = PURPLE_RED;
                    }
                    else if (sensorData[PIXY_SIG_LOC + block_target[j] * 14]
                            == 10)
                    {
                        color[j] = GREEN_PURPLE;
                    }
                    else if (sensorData[PIXY_SIG_LOC + block_target[j] * 14]
                            == 12)
                    {
                        color[j] = YELLOW_PURPLE;
                    }
//                    final_msg = OBJECT_FINDING_SIG << 24 | isDetected << 16
//                            | color << 8 | direction;
                }
            }
            dataToSend.event = PROCESS_MSG;
            dataToSend.state = OBJECT_FINDING;
            dataToSend.shortDistWarn = aFsm->distWarn;
            dataToSend.irDistance = distance;
            memcpy(dataToSend.color, color, sizeof(color));
            memcpy(dataToSend.direction, direction, sizeof(direction));
            memcpy(dataToSend.angle, blockAngle, sizeof(blockAngle));
            memcpy(dataToSend.blockSize, blockSize, sizeof(blockSize));
            memcpy(dataToSend.detection, isDetected, sizeof(isDetected));
            memcpy(dataToSend.trackIndex, trackingIndex, sizeof(trackingIndex));
            sendMsgToMqtt(&dataToSend);

        }

        else if (dataRecv->dataType == ULTRA_MSG_TYPE)
        {
            uint32_t dist;
            sscanf(sensorData, "%d", &dist);
            dataToSend.distance = (uint8_t) sensorData[0] << 16
                    | (uint8_t) sensorData[1] << 8 | (uint8_t) sensorData[2];
            if (dist <= 10)
            {
                aFsm->distWarn = true;
            }
            else
            {
                aFsm->distWarn = false;
            }
            if (aFsm->reportUltra)
            {
                dataToSend.event = DISTANCE_MSG;
                dataToSend.state = OBJECT_FINDING;
                if (dist <= 10)
                {
                    dataToSend.shortDistWarn = true;
                }
                else
                {
                    dataToSend.shortDistWarn = false;
                }
                sendMsgToMqtt(&dataToSend);
                aFsm->reportUltra = false;
            }
//
        }
        else if (dataRecv->dataType == ARM_MSG_TYPE)
        {
            aFsm->state = DROPAREA_FINDING;
            aFsm->reportUltra = false;
        }
        break;
    }
    case DROPAREA_FINDING:
        if (dataRecv->dataType == PIXY_MSG_TYPE)
        {
            if (sensorData[0] != 175 || sensorData[1] != 193)
            //  || sensorData[PIXY_BLOCKNUM_LOC] == 0)
            {
                break;
            }
            //detected something
            int blockCount = sensorData[PIXY_BLOCKNUM_LOC] / 14;
            int i;
            for (i = 0; i < blockCount; i++)
            {
                if (sensorData[PIXY_SIG_LOC + i * 14] != 19) //10 = blue green,  28 = red purple
                {
                    continue;
                }
                if (isDetected[0] == 0)
                {
                    isDetected[0] = 1;
                    block_target[0] = 0;
                    block_target[1] = 0;
                    block_target[2] = 0;
                    isDetected[1] = 0;
                    isDetected[2] = 0;
                    targetCount++;
                }
//                else if (isDetected[1] == 0)
//                {
//                    isDetected[1] = 1;
//                    block_target[1] = 1;
//                    targetCount++;
//                }
//                else if (isDetected[2] == 0)
//                {
//                    isDetected[2] = 1;
//                    block_target[2] = 2;
//                    targetCount++;
//                }

            }
            int j = 0;
            double angle = 0;
            if (isDetected[j])
            {
                blockSize[j] = sensorData[PIXY_WIDTH_LOC + j * 14]
                        * sensorData[PIXY_HEIGHT_LOC + j * 14];
                trackingIndex[j] = sensorData[PIXY_TRACK_LOC
                        + block_target[j] * 14];
                uint16_t object_x = sensorData[PIXY_XCOR_LOC
                        + block_target[j] * 14];
                uint8_t object_x2 = sensorData[PIXY_XCOR_LOC + 1
                        + block_target[j] * 14];
                if (object_x2 != 0)
                {
                    object_x = object_x2 << 8 | object_x;
                }
                int32_t x_err = X_CENTER - object_x; //about 30cm away from the object
                angle = ANGLE_MULTIPLE * x_err;
                angle = angle + ANGLE_CONSTANT;
                blockAngle[j] = (int) (angle + 0.5);
                if (dataToSend.angle[j] < -2)
                {
                    direction[j] = ROTATE_LEFT;
                }
                else if (dataToSend.angle[j] > 2)
                {
                    direction[j] = ROTATE_RIGHT;
                }
                else
                {
                    direction[j] = LINE_UP;
                    aFsm->reportUltra = true;
                    uint16_t adcValue0;
                    uint16_t res = ADC_convert(aFsm->adc, &adcValue0);
                    uint32_t adcValue0MicroVolt =
                    ADC_convertRawToMicroVolts(aFsm->adc, adcValue0);
                    int index;
                    for (index = 0;
                            index < sizeof(lookup) / sizeof(lookup[0]) - 1;
                            index++)
                    {
                        if (index == 0 && lookup[index] < adcValue0MicroVolt)
                        {
                            distance = 10;
                            break;
                        }
                        if (index == sizeof(lookup) / sizeof(lookup[0]) - 2
                                && lookup[index] > adcValue0MicroVolt)
                        {
                            distance = 32;
                            break;
                        }
                        if (lookup[index] >= adcValue0MicroVolt
                                && lookup[index + 1] <= adcValue0MicroVolt)
                        {
                            uint32_t total = lookup[index + 1] - lookup[index];
                            uint32_t diff = adcValue0MicroVolt - lookup[index];
                            double portion = diff / total;
                            distance = (int) (portion * correspond[index]
                                    + (1 - portion) * correspond[index + 1]);
                            break;
                        }
                    }
                }
                if (sensorData[PIXY_SIG_LOC + block_target[j] * 14] == 19)
                {
                    color[j] = GREEN_RED;
                }
            }
//            int j;
//            for (j = 0; j < 3; j++)
//            {
//                double angle = 0;
//                if (isDetected[j])
//                {
//                    blockSize[j] = sensorData[PIXY_WIDTH_LOC + j * 14]
//                            * sensorData[PIXY_HEIGHT_LOC + j * 14];
//                    trackingIndex[j] = sensorData[PIXY_TRACK_LOC
//                            + block_target[j] * 14];
//                    uint16_t object_x = sensorData[PIXY_XCOR_LOC
//                            + block_target[j] * 14];
//                    uint8_t object_x2 = sensorData[PIXY_XCOR_LOC + 1
//                            + block_target[j] * 14];
//                    if (object_x2 != 0)
//                    {
//                        object_x = object_x2 << 8 | object_x;
//                    }
//                    int32_t x_err = X_CENTER - object_x; //about 30cm away from the object
//                    angle = ANGLE_MULTIPLE * x_err;
//                    angle = angle + ANGLE_CONSTANT;
//                    blockAngle[j] = (int) (angle + 0.5);
//                    if (dataToSend.angle[j] < -2)
//                    {
//                        direction[j] = ROTATE_LEFT;
//                    }
//                    else if (dataToSend.angle[j] > 2)
//                    {
//                        direction[j] = ROTATE_RIGHT;
//                    }
//                    else
//                    {
//                        direction[j] = LINE_UP;
//                        aFsm->reportUltra = true;
//                        uint16_t adcValue0;
//                        uint16_t res = ADC_convert(aFsm->adc, &adcValue0);
//                        uint32_t adcValue0MicroVolt =
//                        ADC_convertRawToMicroVolts(aFsm->adc, adcValue0);
//                        int index;
//                        for (index = 0;
//                                index < sizeof(lookup) / sizeof(lookup[0]) - 1;
//                                index++)
//                        {
//                            if (index == 0
//                                    && lookup[index] < adcValue0MicroVolt)
//                            {
//                                distance = 10;
//                                break;
//                            }
//                            if (index == sizeof(lookup) / sizeof(lookup[0]) - 2
//                                    && lookup[index] > adcValue0MicroVolt)
//                            {
//                                distance = 32;
//                                break;
//                            }
//                            if (lookup[index] >= adcValue0MicroVolt
//                                    && lookup[index + 1] <= adcValue0MicroVolt)
//                            {
//                                uint32_t total = lookup[index + 1]
//                                        - lookup[index];
//                                uint32_t diff = adcValue0MicroVolt
//                                        - lookup[index];
//                                double portion = diff / total;
//                                distance =
//                                        (int) (portion * correspond[index]
//                                                + (1 - portion)
//                                                        * correspond[index + 1]);
//                                break;
//                            }
//                        }
//                    }
//                    if (sensorData[PIXY_SIG_LOC + block_target[j] * 14] == 19)
//                    {
//                        color[j] = GREEN_RED;
//                    }
                    //                    final_msg = OBJECT_FINDING_SIG << 24 | isDetected << 16
                    //                            | color << 8 | direction;
//                }
//            }
            dataToSend.event = PROCESS_MSG;
            dataToSend.state = DROPAREA_FINDING;
            dataToSend.shortDistWarn = aFsm->distWarn;
            dataToSend.irDistance = distance;
            memcpy(dataToSend.color, color, sizeof(color));
            memcpy(dataToSend.direction, direction, sizeof(direction));
            memcpy(dataToSend.angle, blockAngle, sizeof(blockAngle));
            memcpy(dataToSend.blockSize, blockSize, sizeof(blockSize));
            memcpy(dataToSend.detection, isDetected, sizeof(isDetected));
            memcpy(dataToSend.trackIndex, trackingIndex, sizeof(trackingIndex));
            sendMsgToMqtt(&dataToSend);
        }
        else if (dataRecv->dataType == ULTRA_MSG_TYPE)
        {
            uint32_t dist;
            sscanf(sensorData, "%d", &dist);
            dataToSend.distance = (uint8_t) sensorData[0] << 16
                    | (uint8_t) sensorData[1] << 8 | (uint8_t) sensorData[2];
            if (dist <= 10)
            {
                aFsm->distWarn = true;
            }
            else
            {
                aFsm->distWarn = false;
            }
            if (aFsm->reportUltra)
            {
                dataToSend.event = DISTANCE_MSG;
                dataToSend.state = OBJECT_FINDING;
                if (dist <= 10)
                {
                    dataToSend.shortDistWarn = true;
                }
                else
                {
                    dataToSend.shortDistWarn = false;
                }
                sendMsgToMqtt(&dataToSend);
                aFsm->reportUltra = false;

            }
            //
        }
        else if (dataRecv->dataType == ARM_MSG_TYPE)
        {
            aFsm->state = OBJECT_FINDING;
            aFsm->reportUltra = false;
        }
        break;
    }

    return 0;
}
