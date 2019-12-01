/*
 * process_main.c
 *
 *  Created on: 2019Äê11ÔÂ3ÈÕ
 *      Author: jiez
 */

#include "process_main.h"
#include "client_cbs.h"
void *processObject(void * arg0)
{
//    createSensorQ();
    sensor_state_fsm myFsm;
    ADC_Params   params;
    ADC_Params_init(&params);
    ADC_Handle adc = ADC_open(Board_ADC0, &params);
    myFsm.adc = adc;
    myFsm.reportUltra = false;
    myFsm.state = OBJECT_FINDING;
    myFsm.distWarn = false;
    msgQueue_sensor msgRecv;
    bool isMqttReady = false;
    while (1)
    {
        int res = recieveMsgFromSensorQ(&msgRecv);
        if (res < 0)
        {
            dbgTerminalError();
        }
        if (res == 4)
        {
            isMqttReady = true;
        }
        if (isMqttReady)
        {
            if (res == 0|| res == 3)
            {
                //pixy data
                sensor_fsm(&myFsm, &msgRecv);

            }
            else if (res == 1)
            {
                //ultrasonic data
                sensor_fsm(&myFsm, &msgRecv);
            }
        }

    }
    return (NULL);
}

