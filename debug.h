
#ifndef DEBUG_H_
#define DEBUG_H_
#include <FreeRTOS.h>
#include <task.h>
#include "Board.h"
#include <ti/drivers/UART.h>

#define TERMINAL_LED_CNTR 0x32DCD5

UART_Handle init_debug();
void dbgUARTVal(UART_Handle uart, unsigned char out_val);
void dbgOutputLoc(unsigned int out_loc);
void dbgTerminalError();

#define BAUD 115200

/*****************************************************************************/
/*                             Debug LOC Markers                             */
/*****************************************************************************/
#define TERMINAL_LOC          31

#define MQTT_STOP_PRE_SEND_LOC    1
#define MAIN_TASK_WHILE_LOC    2
#define MQTT_START_PRE_LOC     3
#define MQTT_START_POST_LOC    4
#define MQTT_CLIENT_PRE_LOC    5
#define MQTT_CLIENT_POST_LOC   6
#define MQTT_CLIENT_START_PRE_LOC 7
#define MQTT_CLIENT_START_POST_LOC 8
#define MQTT_CLIENT_THREAD_PRE_LOC 9
#define MQTT_CLIENT_THREAD_POST_LOC 10
#define SEND_TO_QUEUE1_PRE_LOC 11
#define SEND_TO_QUEUE1_POST_LOC 12
#define MQTT_CALLBACK_PRE_LOC   13
#define MQTT_CALLBACK_POST_LOC  14
#define MQTT_CALLBACK_RECV_PRE_LOC  15
#define MQTT_CALLBACK_RECV_POST_LOC 16
#define SEND_TO_QUEUE2_PRE_LOC 17
#define SEND_TO_QUEUE2_POST_LOC 18
#define RECV_FROM_QUEUE1_PRE_LOC 19
#define RECV_FROM_QUEUE1_POST_LOC 20
#define RECV_FROM_QUEUE2_PRE_LOC  21
#define RECV_FROM_QUEUE2_POST_LOC 22
#define MAIN_TASK_WHILE_NEAR_END_LOC 23
#define PRINT_THREAD_WHILE_ENTER 24
#define MAIN_MSG_EVENT_ENTER_LOC 25
#define MAIN_RECV_EVENT_ENTER_LOC 26
#define MAIN_DEFAULT_EVENT_LOC    27
#define MAIN_MSG_EVENT_OUT_LOC    28
#define PUBLISH_STATS_LOC         29
#define PUBLISH_TI_LOC            30
//#define SEND_TIME_PRE_LOC      5
//#define SEND_TIME_POST_LOC     6
//#define SEND_SENSOR_PRE_LOC    7
//#define SEND_SENSOR_POST_LOC   8
//#define ISR_TIMER_1_PRE_LOC    9
//#define ISR_TIMER_1_POST_LOC  10
//#define ISR_TIMER_2_PRE_LOC   11
//#define ISR_TIMER_2_POST_LOC  12
#endif
