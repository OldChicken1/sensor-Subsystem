/*
 * timer_pixy.c
 *
 *  Created on: 2019Äê9ÔÂ28ÈÕ
 *      Author: jiez
 */
#include <stddef.h>
//#include <ti/drivers/Timer.h>

/* Board Header file */
#include "Board.h"
#include <ti/drivers/I2C.h>
#include "timer_pixy.h"
#include <ti/drivers/Timer.h>



I2C_Handle init_I2C()
{
    I2C_Params i2cParams;
    I2C_Params_init(&i2cParams);
    i2cParams.transferMode = I2C_MODE_CALLBACK;
    i2cParams.bitRate = I2C_400kHz;
    i2cParams.transferCallbackFxn = i2cCallback;
    return I2C_open(Board_I2C0, &i2cParams);

}
void init_I2C_transaction(I2C_Transaction* i2cTransaction, uint8_t* txBufferStart, int txLength,
                          uint8_t* rxBufferStart, int rxLength){
     i2cTransaction->writeBuf   = txBufferStart;
     i2cTransaction->writeCount = txLength;
     i2cTransaction->readBuf    = rxBufferStart;
     i2cTransaction->readCount  = rxLength;
     i2cTransaction->slaveAddress = PIXY_ADDR;
}
void read_I2C(I2C_Handle* i2c, I2C_Transaction* i2cTransaction){
     if (!I2C_transfer(*i2c, i2cTransaction)) {
         //while(1){}
         dbgTerminalError();
     }
}

//void read_I2C_data(I2C_Handle* i2c, I2C_Transaction* i2cTransaction, int txLength,
//                     uint8_t* rxBufferStart, int rxLength ){
//    uint8_t junkWrite[txLength];
//    i2cTransaction->writeBuf = junkWrite;
//    i2cTransaction->writeCount = txLength;
//    i2cTransaction->readBuf    = rxBufferStart;
//    i2cTransaction->readCount  = rxLength;
//    if (!I2C_transfer(*i2c, i2cTransaction)) {
//         while(1);
//     }
//}
Timer_Handle init_timerPixy()
{
    Timer_init();
    Timer_Handle timerPixy;
    Timer_Params params;
    Timer_Params_init(&params);
    params.period = TIMER_PIXY_MS_TIME * 1000;
    params.periodUnits = Timer_PERIOD_US;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = pixyTimerCallback;

    return Timer_open(Board_TIMER0, &params);

}

void pixyTimerCallback(Timer_Handle myHandle)
{
//    dbgOutputLoc(ISR_TIMER_PRE_LOC);
    if(sendTimeMsgToPixyQ(TIMER_PIXY_MS_TIME) <= 0){
        dbgTerminalError();
    }
//    dbgOutputLoc(ISR_TIMER_POST_LOC);
}


void i2cCallback(I2C_Handle myHandle, I2C_Transaction* myTransaction, bool result){
    if(result){

        if(sendI2CMsgToPixyQ(I2C_SUCCESS_SIG) <= 0){
            dbgTerminalError();
        }
//        dbgOutputLoc(I2C_TRAN_POST_LOC);
    }
//    else{
//        if(sendI2CMsgToPixyQ(I2C_FAIL_SIG) <= 0){
//            while(1);
//        }
//    }
}
