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

uint32_t clock1ms = XTAL / 1000;
uint32_t i;
void delay(uint32_t msec);
void delay1ms(void);
void delay2(uint32_t msec);

void InitUART(void);


int main(void)
{

    SysCtlClockSet(
            SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN
                    | SYSCTL_XTAL_16MHZ);




    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,
    GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    InitUART();
    while (1)
    {

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
        delay2(500);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
        GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
        delay2(500);

    }
    //return 0;
}

void delay(uint32_t msec)
{
    for (i = 0; i < msec; i++)
     {
    delay1ms();
    }

}

void delay1ms(void)
{

    SysTickPeriodSet(16000 - 1);
    SysTickEnable();
    while (SysTickValueGet() != 0)
        ;

}

void delay2(uint32_t msec)
{

    // 1) Disable SysTick during initialization.
    NVIC_ST_CTRL_R = 0;

    // 2) Set the RELOAD register to establish a modulo RELOAD + 1 decrement counter
    NVIC_ST_RELOAD_R = 0x00FFFFFF;

    // 3) Clear the accumulator
    NVIC_ST_CURRENT_R = 0;

    // 4) Set clock source to core clock and enable
    NVIC_ST_CTRL_R = NVIC_ST_CTRL_CLK_SRC | NVIC_ST_CTRL_ENABLE;

    for (i = 0; i < msec; i++)
    {
        // Delay in number of bus cycle period units
        NVIC_ST_RELOAD_R = 16000 - 1;

        // Clear CURRENT
        NVIC_ST_CURRENT_R = 0;

        // Wait for COUNT flag to be set upon rollover.
        while ((NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT) == 0)
        {
        }

    }

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

