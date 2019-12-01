/*
 * readFromQueueThread.c
 *
 *  Created on: 2019Äê10ÔÂ14ÈÕ
 *      Author: jiez
 */

#include "readFromQueueThread.h"

#define MSG_TO_ROVER "\n\rMessage recieved from Board: \n\r"
void *readFromQueue(void *arg0)
{
    UART_Handle uart;
    /*Configure the UART                                                     */
    uart = init_debug();
    char print_buf[64];
    char data_recv[MSG_DATA_LENGTH];
    msgQueue_t recv;
    while (1)
    {
        recieveMsgFromRoverQ(&recv);
//        memcpy((data_recv), recv.msgPtr, MSG_DATA_LENGTH);
//        sprintf(print_buf, MSG_TO_ROVER);
//        int i;
//        for (i = 0; i < sizeof(MSG_TO_ROVER); i++)
//        {
//            dbgUARTVal(uart, print_buf[i]);
//        }
//        sprintf(print_buf, "Board id and message id: %s, %d.\r\n",
//                recv.board_id, recv.message_id);
//        for (i = 0; i < sizeof(MSG_TO_ROVER); i++)
//        {
//            dbgUARTVal(uart, print_buf[i]);
//        }
////        int start = recv.topLen + 12;
//        int end = recv.dataLen + 1;
//        int j;
//        for (j = 0; j < end; j++)
//        {
//            dbgUARTVal(uart, data_recv[j]);
//        }
////        UART_write(uart, &(recv.board_id), 1);
//        dbgOutputLoc(PRINT_THREAD_WHILE_ENTER);

    }
}
