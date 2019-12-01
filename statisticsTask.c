/*
 * statisticsTask.c
 *
 *  Created on: 2019年10月18日
 *      Author: jiez
 */

/*
 * readFromQueueThread.c
 *
 *  Created on: 2019年10月14日
 *      Author: jiez
 */

#include "statisticsTask.h"

void *statisticsTask(void *pvParameters)
{
    uint32_t T1_cur_ID = 0;
    uint32_t T1_last_ID = 0;
    uint32_t T2_cur_ID = 0;
    uint32_t T2_last_ID = 0;
    uint32_t T3_cur_ID = 0;
    uint32_t T3_last_ID = 0;
    uint32_t T1_missed = 0;
    uint32_t T2_missed = 0;
    uint32_t T3_missed = 0;
    msgQueue_t queueElemRecv;
    msgQueue_t2 toSend;
    for (;;)
    {
        recieveMsgFromStatQueue(&queueElemRecv);
        switch (queueElemRecv.event)
        {
        case MSG_RECV_BY_CLIENT:
            dbgOutputLoc(MAIN_RECV_EVENT_ENTER_LOC);
            //           tmpBuff =  ((char *) queueElemRecv.msgPtr + 12);
            //           char msg_id[6] = queueElemRecv.message_id;
            uint32_t msg_id_int;
            sscanf(queueElemRecv.message_id, "%d", &msg_id_int);
            if (strncmp(queueElemRecv.board_id, "rocky", 5) == 0)
            {
                if(queueElemRecv.isRetain){
                    T1_last_ID =  msg_id_int;
                    T1_cur_ID = msg_id_int;
                }
                else
                {
                    T1_cur_ID = msg_id_int;
                    T1_missed += T1_cur_ID - T1_last_ID - 1;
                    T1_last_ID = T1_cur_ID;
                }

            }
//            else if (strncmp(queueElemRecv.board_id, "jacob", 5) == 0)
            else if (strncmp(queueElemRecv.board_id, "ahmed", 5) == 0)
            {
                if(queueElemRecv.isRetain){
                    T2_last_ID =  msg_id_int;
                    T2_cur_ID = msg_id_int;
                }
                else
                {
                    T2_cur_ID = msg_id_int;
                    T2_missed += T2_cur_ID - T2_last_ID - 1;
                    T2_last_ID = T2_cur_ID;
                }

            }
            else if (strncmp(queueElemRecv.board_id, "jacob", 5) == 0)
            {
                if(queueElemRecv.isRetain){
                    T3_last_ID =  msg_id_int;
                    T3_cur_ID = msg_id_int;
                }
                else
                {
                    T3_cur_ID = msg_id_int;
                    T3_missed += T3_cur_ID - T3_last_ID - 1;
                    T3_last_ID = T3_cur_ID;
                }

            }
            break;
//            data_to_rover.event = queueElemRecv.event;
//            data_to_rover.dataLen = queueElemRecv.dataLen;
//            memcpy((data_to_rover.msgPtr), queueElemRecv.msgPtr,
//            MSG_DATA_LENGTH);
//            sendMsgToRoverQueue(&data_to_rover);
//            break;
        case STATS_PUBLISH:
            toSend.event = STATS_MSG;
            toSend.T1_miss_num = T1_missed;
            toSend.T2_miss_num = T2_missed;
            toSend.T3_miss_num = T3_missed;
            sendMsgToMqtt(&toSend);
            break;
        }

    }
}
