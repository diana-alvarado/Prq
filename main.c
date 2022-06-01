//**************************************************************************************************************
//Laboratorio 6
//Diana Alvarado
//20525

//**************************************************************************************************************
// Librerias para que funcione
//**************************************************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"

//**************************************************************************************************************
// Variables Globales
//**************************************************************************************************************

uint32_t ui32Period;
uint8_t P1 = 0;
uint8_t P2 = 0;
uint8_t P3 = 0;
uint8_t P4 = 0;
uint8_t total = 4;
uint8_t PU1 = 1;
uint8_t PU2 = 3;
uint8_t PU3 = 5;
uint8_t PU4 = 7;
uint32_t i = 0;

//**************************************************************************************************************
// Prototipos de Funcion
//**************************************************************************************************************
void InitUART(void);
void display(void);

//**************************************************************************************************************
// Codigo Principal
//**************************************************************************************************************
int main(void)
{
    // Configuracion del oscilador externo, usando PLL y teniendo una frecuencia de 40MHz
    SysCtlClockSet(
            SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ
                    | SYSCTL_OSC_MAIN);

    //Iniciar UART
    InitUART();

    // Se habilita el reloj para todos los puertos
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);//Rojos
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);//Botones
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);//Verdes


    // Se habilita el reloj para el temporizador
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    // Se establecen como salidas el puerto F
     GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,
                              GPIO_PIN_5 | GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4); //LEDS ROJOS
     GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE,
                                   GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_5); //LEDS VERDES
     GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,  GPIO_PIN_1  | GPIO_PIN_3 | GPIO_PIN_4 ); //Display
     GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_2 | GPIO_PIN_3);
     GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3); //Entrada de los botones

     GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
     GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
     GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
     GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU); //Pullups

    // Se habilitan las interrupciones Globales
    //IntMasterEnable();

    //**********************************************************************************************************
    // Loop Principal
    //**********************************************************************************************************
    while (1)
    {

        if(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_0) == 0){
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_PIN_5);
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0);
            P1 = 1;
            PU1 = 2;
            UARTCharPut(UART3_BASE, 2);

        }
        if(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_0) != 0){
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0);
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, GPIO_PIN_2);
            P1 = 0;
            PU1 = 1;
            UARTCharPut(UART3_BASE, 1);
        }
        if(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_1) == 0){
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, GPIO_PIN_4);
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0);
            P2 = 1;
            PU2 = 4;
            UARTCharPut(UART3_BASE, 4);
        }
        else{
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0);
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_PIN_1);
            P2 = 0;
            PU2 = 3;
            UARTCharPut(UART3_BASE, 3);
        }
        if(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_2) == 0){
            GPIOPinWrite(GPIO_PORTB_BASE,  GPIO_PIN_0, GPIO_PIN_0);
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, 0);
            P3 = 1;
            PU3 = 6;
            UARTCharPut(UART3_BASE, 6);
        }
        else{
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0);
            GPIOPinWrite(GPIO_PORTE_BASE,  GPIO_PIN_3 , GPIO_PIN_3);
            P3 = 0;
            PU3 = 5;
            UARTCharPut(UART3_BASE, 5);
        }
        if(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_3) == 0){
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, GPIO_PIN_1);
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0);
            P4 = 1;
            PU4 = 8;
            UARTCharPut(UART3_BASE, 8);
        }
        else{
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0);
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_PIN_5);
            P4 =0;
            PU4 = 7;
            UARTCharPut(UART3_BASE, 7);
        }
        total = 4 - (P4+P3+P2+P1);
        display();
    }
}


void InitUART(void)
{
    /*Enable the GPIO Port A*/
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

        /*Enable the peripheral UART Module 0*/
        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
        //GPIOPinConfigure(GPIO_PC6_U3RX);
        //GPIOPinConfigure(GPIO_PC7_U3TX);

        /* Make the UART pins be peripheral controlled. */
        GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7);

        /* Sets the configuration of a UART. */
        UARTConfigSetExpClk(
                UART3_BASE, SysCtlClockGet(), 115200,
                (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

        UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
}


void display(void)
{
    //MOSTRAR 0
    if (total == 0)
    {
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 0);

        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_3);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, GPIO_PIN_2);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_PIN_5);

    }
    //MOSTRAR 1
    if (total == 1)
    {
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 0);

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, GPIO_PIN_2);
    }
    //MOSTRAR 2
    if (total == 2)
    {
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 0);

        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_3);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_PIN_6);
    }
    //MOSTRAR 3
    if (total == 3)
    {
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 0);

        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_3);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
        //GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, GPIO_PIN_2);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_PIN_6);
        //GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_PIN_5);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
    }
    //MOSTRAR 4
    if (total == 4)
    {
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 0);

        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_PIN_5);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_PIN_6);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, GPIO_PIN_2);

    }
}
