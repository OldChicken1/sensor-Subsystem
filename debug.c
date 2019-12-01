
#include "debug.h"

#define GPIO_PRINT_BIT(val, pos) \
    GPIO_write(Board_dbgLOC_##pos, ((val >> pos) & 0x1))

UART_Handle init_debug(void)
{

/*****************************************************************************/
/*                                 UART Setup                                */
/*****************************************************************************/
    UART_Params uart_params;

    UART_Params_init(&uart_params);
    uart_params.writeDataMode = UART_DATA_BINARY;
    uart_params.readDataMode = UART_DATA_BINARY;
    uart_params.readReturnMode = UART_RETURN_FULL;
    uart_params.readEcho = UART_ECHO_OFF;
    uart_params.baudRate = BAUD;
    return (UART_open(Board_UART0, &uart_params));
}

void dbgUARTVal(UART_Handle uart,unsigned char out_val)
{
    UART_write(uart, &out_val, 1);
}

void dbgOutputLoc(unsigned int out_loc)
{
    if (out_loc > 32) {
        dbgTerminalError();
    }
    GPIO_PRINT_BIT(out_loc, 0);
    GPIO_PRINT_BIT(out_loc, 1);
    GPIO_PRINT_BIT(out_loc, 2);
//    GPIO_PRINT_BIT(out_loc, 3);
//    GPIO_PRINT_BIT(out_loc, 4);
}

void dbgTerminalError()
{
    taskDISABLE_INTERRUPTS();
//
    //GPIO_write(Board_GPIO_LED0, 0);
//    GPIO_write(Board_GPIO_LED1, 0);
//    GPIO_write(Board_GPIO_LED2, 0);

    uint8_t led_cnt = 0;

    while (1) {
        dbgOutputLoc(TERMINAL_LOC);
        int i = 0;
        for(i = 0; i < TERMINAL_LED_CNTR; ++i) {}
        ++led_cnt;

//        switch (led_cnt) {
//            case 1:
//                GPIO_toggle(Board_GPIO_LED1);
//                break;
//            case 2:
//                GPIO_toggle(Board_GPIO_LED2);
//                led_cnt = 0;
//                break;
//        }
    }
}
