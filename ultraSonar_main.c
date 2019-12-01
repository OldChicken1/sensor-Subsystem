/*
 * ultraSonar_main.c
 *
 *  Created on: 2019Äê11ÔÂ2ÈÕ
 *      Author: jiez
 */

#include "ultraSonar_main.h"


UART_Handle initUart()
{
    UART_Params uartParams;
    uartParams.readMode = UART_MODE_BLOCKING;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.baudRate = 9600;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.stopBits = UART_STOP_ONE;
    uartParams.parityType = UART_PAR_NONE;
    uartParams.dataLength = UART_LEN_8;
    return UART_open(Board_UART0, &uartParams);
}

void insertionSort(uint32_t arr[], int n)
{
    int i, key, j;
    for(i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while(j >= 0 && arr[j] > key)
        {
            arr[j+1] = arr[j];
            j = j - 1;
        }
        arr[j+1] = key;
    }
}
void *sonarRead(void *arg0)
{
    UART_Handle ultra_uart = initUart();
    uint8_t data[SONIC_DATA_LENGTH];
    int count = 0;

    uint32_t arr[10];
    char dataNeeded[DISTANCE_LENGTH];
    if(ultra_uart == NULL){
        dbgTerminalError();
    }
    while(1)
    {
        UART_read(ultra_uart, data, sizeof(data));
        if(data[0] == 'R'){
            dataNeeded[0] = data[1];
            dataNeeded[1] = data[2];
            dataNeeded[2] = data[3];
            uint32_t cur;
            sscanf(dataNeeded, "%d", &cur);
            arr[count] = cur;
            count++;
        }
        if (count == SEND_SPEED)
        {
            insertionSort(arr, sizeof(arr)/sizeof(arr[0]));
            uint32_t sum = 0;
            int i;
            for(i = 2; i < 8; i++){
                sum += arr[i];
            }
            msgQueue_sensor msgUltra;
            uint32_t final = sum / (SEND_SPEED - 4);
            snprintf(dataNeeded[0], sizeof(dataNeeded[0]), final >> 16);
            snprintf(dataNeeded[1], sizeof(dataNeeded[1]), final >> 8);
            snprintf(dataNeeded[2], sizeof(dataNeeded[2]), final);
//            snprintf(dataNeeded, sizeof(dataNeeded), "%d", final);
//            dataNeeded[2] = dataNeeded[1];
//            dataNeeded[1] = dataNeeded[0];
//            dataNeeded[0] = '0';
            memcpy(msgUltra.data, dataNeeded, sizeof(dataNeeded));
            msgUltra.dataType = ULTRA_MSG_TYPE;
            sendMsgToSensorQ(&msgUltra);
            count = 0;
            sum = 0;
        }
    }
    return (NULL);
}
