/**
 * main.c
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"

#define XTAL 16000000

void InitUART(void);


int main(void)
{

    SysCtlClockSet(
            SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN
                    | SYSCTL_XTAL_16MHZ);
    InitUART();

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,
    GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    while (1)
    {



    }
    //return 0;
}


void InitUART(void){


    /*Enable the GPIO Port A*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    /*Enable the peripheral UART Module 0*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);


    /* Make the UART pins be peripheral controlled. */
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    /* Sets the configuration of a UART. */
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
    (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    //UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

    UARTCharPut(UART0_BASE,'H');
    UARTCharPut(UART0_BASE,'o');
    UARTCharPut(UART0_BASE,'l');
    UARTCharPut(UART0_BASE,'a');
    UARTCharPut(UART0_BASE,' ');
    UARTCharPut(UART0_BASE,'M');
    UARTCharPut(UART0_BASE,'u');
    UARTCharPut(UART0_BASE,'n');
    UARTCharPut(UART0_BASE,'d');
    UARTCharPut(UART0_BASE,'o');

}

