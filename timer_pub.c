///*
// * timer_pixy.c
// *
// *  Created on: 2019Äê9ÔÂ28ÈÕ
// *      Author: jiez
// */
//#include <stddef.h>
////#include <ti/drivers/Timer.h>
//
///* Board Header file */
//#include "Board.h"
//#include <ti/drivers/I2C.h>
//#include "timer_pub.h"
//
//TimerHandle_t init_timer()
//{
//    return xTimerCreate("mqtt_timer", TIMER_MQTT_MS_TIME, pdTRUE, (void*)0, timerCallback);
//
////    if (Timer_start(*timer0) == Timer_STATUS_ERROR) {
////        /* Failed to start timer */
////        while (1) {}
////    }
//}
//
//void timerCallback(TimerHandle_t myHandle)
//{
//    msgQueue_t2 queueElement;
//    queueElement.event = TIMER_MSG;
////    dbgOutputLoc(ISR_TIMER_PRE_LOC);
//    if(sendMsgToMqtt(&queueElement)<=0){
//        dbgTerminalError();
//    }
////    dbgOutputLoc(ISR_TIMER_POST_LOC);
//}

