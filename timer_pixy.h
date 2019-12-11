/*
 * timer_pixy.h
 *
 *  Created on: 2019Äê9ÔÂ29ÈÕ
 *      Author: jiez
 */

#ifndef TIMER_PIXY_H_
#define TIMER_PIXY_H_

#include <ti/drivers/Timer.h>
#include "debug.h"
#define PIXY_CHECKSUM_SYNC                   0xc1af
#define PIXY_NO_CHECKSUM_SYNC                0xc1ae
#define PIXY_SEND_HEADER_SIZE                4
#define CCC_SIG_ALL                          0xff

#define PIXY_ADDR           0x54
#define TIMER_PIXY_MS_TIME 200
#define I2C_SUCCESS_SIG 1
#define I2C_FAIL_SIG 0



void pixyTimerCallback(Timer_Handle myHandle);
void i2cCallback(I2C_Handle myHandle, I2C_Transaction* myTransaction, bool result);
I2C_Handle init_I2C();
void read_I2C(I2C_Handle* i2c, I2C_Transaction* i2cTransaction);
Timer_Handle init_timerPixy();
void init_I2C_transaction(I2C_Transaction* i2cTransaction, uint8_t* txBufferStart, int txLength,
                          uint8_t* rxBufferStart, int rxLength);



#endif /* TIMER_PIXY_H_ */
