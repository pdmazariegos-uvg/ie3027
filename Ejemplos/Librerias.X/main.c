/*
 * File:   main.c
 * Author: Pablo Mazariegos
 * Ejemplo de uso de librerías
 * Created on 27 de enero de 2020, 08:48 PM
 */
//**************************************************************
// Librerías
//**************************************************************
#include <xc.h>
#include <stdint.h>
#include "Oscilador.h"
//**************************************************************
// Palabra de configuración
//**************************************************************
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
//**************************************************************
// Prototipo de funciones
//**************************************************************
void initPorts(void);
void initTMR0(void);
//**************************************************************
// Variables
//**************************************************************
uint16_t contador = 0;
//**************************************************************
// Vector de interrupción
//**************************************************************

void __interrupt() ISR(void) {
    if (TMR0IF) {
        //Enter your code here
        TMR0IF = 0;
        TMR0 = 4;
        contador++; // Se incrementa la variable de contador cada 0.5 mS
    }
}
//**************************************************************
// Función Principal
//**************************************************************

void main(void) {
    initOsc(7);
    initPorts();
    initTMR0();
    while (1) {
        if (contador >= 1000) {
            PORTB++;
            contador = 0;
        }
    }
    return;
}
//**************************************************************
// Función para inicializar puerto
//**************************************************************

void initPorts(void) {
    TRISB = 0; // Puerto B como Salida
    ANSEL = 0;
    ANSELH = 0; // Puertos Digitales
    PORTB = 0; // Inicializar Puerto B en 0
}
//**************************************************************
// Función para inicializar Timer0
//**************************************************************

void initTMR0(void) {
    OPTION_REG = 0x81; // Configuración para tener un desborde 
    TMR0 = 4; // de 0.5 mS    
    INTCON = 0xA0;
}