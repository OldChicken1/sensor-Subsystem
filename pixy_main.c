/*
 * pixy_main.c
 *
 *  Created on: 2019Äê10ÔÂ30ÈÕ
 *      Author: jiez
 */

#include "pixy_main.h"


void *pixyRead(void *arg0)
{

//    GPIO_write(Board_dbgLOC_0, 0);
//    GPIO_write(Board_dbgLOC_1, 0);
//    GPIO_write(Board_dbgLOC_2, 0);
//    GPIO_write(Board_dbgLOC_3, 0);
//    GPIO_write(Board_dbgLOC_4, 0);
//    GPIO_write(Board_dbgLOC_5, 0);
//    GPIO_write(Board_dbgLOC_6, 0);
//    GPIO_write(Board_dbgLOC_7, 0);
//    dbgOutputLoc(MAIN_TASK_ENTER_LOC);
//    I2C_init();
//    GPIO_init();
//    Timer_init();

    I2C_Handle i2c;
    I2C_Transaction i2cTransaction;
    uint8_t txBuffer[TXBUFFERSIZE];
    uint8_t rxBuffer[RXBUFFERSIZE];
    uint8_t m_type = 0x20;
    uint8_t m_length = 2;
    txBuffer[0] = 0xae;
    txBuffer[1] = 0xc1;
    txBuffer[2] = m_type;
    txBuffer[3] = m_length;
    txBuffer[4] = CCC_SIG_ALL;
    txBuffer[5] = 0xff;
//    createPixyQ();
    //   init_debug();
    i2c=init_I2C();
    init_I2C_transaction(&i2cTransaction, txBuffer, sizeof(txBuffer), rxBuffer,
                         sizeof(rxBuffer));

    Timer_Handle timerPixy = init_timerPixy();

    if (timerPixy == NULL)
    {
        dbgTerminalError();
    }
    if (Timer_start(timerPixy) == Timer_STATUS_ERROR)
    {
        dbgTerminalError();
    }

    uint32_t sensor_pixy = 0;
    uint32_t i2c_val = 0;
    while (1)
    {
//        dbgOutputLoc(I2C_TRAN_PRE_LOC);
        int res = recieveMsgFromPixyQ(&sensor_pixy,&i2c_val);
        if (res < 0)
        {
            dbgTerminalError();
        }
        if (res == 1)
        {
            read_I2C(&i2c, &i2cTransaction);
        }
        if (res == 2)
        {
            msgQueue_sensor msgPixy;
            memcpy(msgPixy.data, rxBuffer, sizeof(rxBuffer));
            msgPixy.dataType = PIXY_MSG_TYPE;
            sendMsgToSensorQ(&msgPixy);
        }

    }
    return (NULL);
}

