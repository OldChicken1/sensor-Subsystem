/*
 * pixy_state.h
 *
 *  Created on: 2019Äê9ÔÂ29ÈÕ
 *      Author: jiez
 */

#ifndef SENSORS_STATE_H_
#define SENSORS_STATE_H_

#include <stdint.h>
#include <stdbool.h>
#include <ti/drivers/I2C.h>
#include "sensors_queue.h"
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <ti/drivers/GPIO.h>
#include "Board.h"
#include <ti/drivers/ADC.h>
#include "timer_pixy.h"
#include "client_cbs.h"
#include "pixy_queue.h"
#define ARMER_PICKUP_SIG        0x00000000
#define ARMER_DROP_SIC          0x00000001
#define TIMER_MSG_SIG           1
#define ARMER_MSG_SIG           2
#define PURPLE_RED              1
#define GREEN_PURPLE             2
#define YELLOW_PURPLE            3
#define GREEN_RED                4

#define PIXY_BLOCKNUM_LOC       3
#define PIXY_SIG_LOC            6
#define PIXY_XCOR_LOC           8
#define PIXY_YCOR_LOC           10
#define PIXY_WIDTH_LOC          12
#define PIXY_HEIGHT_LOC         14
#define PIXY_TRACK_LOC          18
#define PIXY_AGE_LOC            19
#define X_CENTER                159
#define Y_CEMTER                100
#define OBJECT_FINDING_SIG      0
#define DROPAREA_FINDING_SIG    1
#define COMPLETE_SIG 2
#define ANGLE_MULTIPLE          -0.2127
#define ANGLE_CONSTANT          1.7623


enum sensor_state{
    OBJECT_FINDING = 0,
    DROPAREA_FINDING = 1,
    COMPLETE = 2
};

typedef struct{
    enum sensor_state state;
//    bool ultraReadOnce;
//    bool pixyReadOnce;
//    uint8_t last_ultra[3];
    int trackIndex;
    int lastSigniture;
    bool reportUltra;
    bool isLostSight;
    int lostSightCnt;
    bool distWarn;
    ADC_Handle adc;

}sensor_state_fsm;

int sensor_fsm(sensor_state_fsm* aFsm, msgQueue_sensor* dataRecv);
#endif /* SENSORS_STATE_H_ */
