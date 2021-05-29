//---------------------------------
//Universidad del Valle de Guatemala
//Erick Daniel Aquino Paz
//Digital 2
//Proyecto 4
///********************************
//librerias
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
//***************************************
#ifdef DEBUG
void
__error_(char *pcfilename, uint32_t ui32Line)
{
    while(1);

}
#endif
/**
 * main.c
 */
#define XTAL 16000000
void InitUART(void);
void initGPIOF(void);
unsigned char letra;
uint8_t LED_ROJ;
uint8_t LED_AZU;
uint8_t LED_VERD;
uint8_t bandera;
uint32_t push1;
uint32_t push2;
uint32_t push3;
uint32_t push4;

int anti1 = 0;
int anti11 = 0;
int anti2 = 0;
int anti22 = 0;
int anti3 = 0;
int anti33 = 0;
int anti4 = 0;
int anti44 = 0;

int cont = 4;
int val = 0;

void display(void);
void Timer0Config(void);
void InitUART(void);
void push(void);
void parqueo(void);
void uartc(void);

int main(void)
{

    SysCtlClockSet(
    SYSCTL_SYSDIV_5 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ); // Reloj de 40MHz
    //Timer0Config(); // Configuracion del TIMER 0
    //InitUART(); // Configuracion de UART 0
    initGPIOF(); //configuracion de leds y puerto F
    uartc(); // configurar el uart1 en el puerto c

    while (1)
    {
        push();
        parqueo();
        display();
        UARTCharPutNonBlocking(UART1_BASE, cont);

    }
}

void Timer0Config(void)
{

    uint32_t ui32Period;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0))
    {
    }
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

    ui32Period = (SysCtlClockGet()) / 2;
    TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period - 1);

    IntEnable(INT_TIMER0A);   // Configuro las interrupciones
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT); // Configuro las interrupciones
    IntMasterEnable();   // Configuro las interrupciones

    TimerEnable(TIMER0_BASE, TIMER_A); // timers.
}

void uartc(void)
{
    //ENABLE UART PERIPHERAL
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1); //Enable the peripheral UART Module 3
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC); //Enable the GPIO Port C
    //SET RX AND TX PINS
    GPIOPinConfigure(GPIO_PC4_U1RX);
    GPIOPinConfigure(GPIO_PC5_U1TX);
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    //BAUDRATE
    UARTConfigSetExpClk(
            UART1_BASE, SysCtlClockGet(), 115200,
            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    UARTEnable(UART1_BASE);
}

void InitUART(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); //Enable the GPIO Port A

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0); //Enable the peripheral UART Module 0

    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTConfigSetExpClk(
            UART0_BASE, SysCtlClockGet(), 115200,
            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
    IntEnable(INT_UART0);
    UARTEnable(UART0_BASE);

    UARTCharPut(UART0_BASE, 'P');
    UARTCharPut(UART0_BASE, 'R');
    UARTCharPut(UART0_BASE, 'O');
    UARTCharPut(UART0_BASE, 'Y');
    UARTCharPut(UART0_BASE, 'E');
    UARTCharPut(UART0_BASE, 'C');
    UARTCharPut(UART0_BASE, 'T');
    UARTCharPut(UART0_BASE, 'O');
    UARTCharPut(UART0_BASE, '4');
    UARTCharPut(UART0_BASE, ' ');

}

//*************************Interrupcion de UART**************************************************

void UARTIntHandler(void)
{

    UARTIntClear(UART0_BASE, UART_INT_RX | UART_INT_RT); // Limpiar bandera de interrupcion

    letra = UARTCharGet(UART0_BASE);  // guardar en variable

    if (letra == 'g')
    {
        LED_VERD = ~LED_VERD;
    }
    else if (letra == 'b')
    {
        LED_AZU = ~LED_AZU;
    }
    else if (letra == 'r')
    {
        LED_ROJ = ~LED_ROJ;
    }
}

//*************************Interrupcion de TIMER 0**************************************************
void Timer0IntHandler(void)
{
    // Clear the timer interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    if (bandera == 1)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
        bandera = 0;
    }
    else
    {
        bandera = 1;
        if (LED_ROJ)
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
        }
        else
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
        }
        if (LED_AZU)
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
        }
        else
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
        }
        if (LED_VERD)
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
        }
        else
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
        }
    }
}


void push(void)
{

    //antirrebote push 1
    push1 = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_2);
    if (((push1 & GPIO_PIN_2) == 0) && anti1 == 0)
    {
        anti1 = 1;
        anti11 = 0;
        cont--;
    }
    push1 = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_2);
    if (((push1 & GPIO_PIN_2) != 0) && (anti11 == 0))
    {
        anti1 = 0;
        anti11 = 1;
        cont++;
    }

    //antirrebote push 2
    push2 = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_3);
    if (((push2 & GPIO_PIN_3) == 0) && anti2 == 0)
    {
        anti2 = 1;
        anti22 = 0;
        cont--;
    }
    push2 = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_3);
    if (((push2 & GPIO_PIN_3) != 0) && (anti22 == 0))
    {
        anti2 = 0;
        anti22 = 1;
        cont++;
    }

    //antirrebote push 3
    push3 = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_4);
    if (((push3 & GPIO_PIN_4) == 0) && (anti3 == 0))
    {
        anti3 = 1;
        anti33 = 0;
        cont--;
    }
    push3 = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_4);
    if (((push3 & GPIO_PIN_4) != 0) && (anti33 == 0))
    {
        anti3 = 0;
        anti33 = 1;
        cont++;
    }
    //antirrebote push 4
    push4 = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_5);
    if (((push4 & GPIO_PIN_5) == 0) && (anti4 == 0))
    {
        anti4 = 1;
        anti44 = 0;
        cont--;
    }
    push4 = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_5);
    if (((push4 & GPIO_PIN_5) != 0) && (anti44 == 0))
    {
        anti4 = 0;
        anti44 = 1;
        cont++;
    }

}
void parqueo(void)
{
    push1 = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_2);
    if (((push1 & GPIO_PIN_2) == 0))
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_PIN_0); //amarillo-ocupado
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0);
    }
    if ((push1 & GPIO_PIN_2) != 0)
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PIN_1);  //azul-libre
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0);
    }
    //SEGUNDO PAR DE LEDS
    push2 = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_3);
    if (((push2 & GPIO_PIN_3) == 0))
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2); //amarillo-ocupado
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0);
    }
    if ((push2 & GPIO_PIN_3) != 0)
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_PIN_3);  //azul-libre
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0);
    }
    //TERCER PAR DE LEDS
    push3 = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_4);
    if (((push3 & GPIO_PIN_4) == 0))
    {
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, GPIO_PIN_0); //amarillo-ocupado
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0);
    }
    if ((push3 & GPIO_PIN_4) != 0)
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, GPIO_PIN_6);  //azul-libre
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, 0);
    }
    //CUARTO PAR DE LEDS
    push4 = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_5);
    if (((push4 & GPIO_PIN_5) == 0))
    {
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_PIN_1); //amarillo-ocupado
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0);
    }
    if ((push4 & GPIO_PIN_5) != 0)
    {
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, GPIO_PIN_2);  //azul-libre
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0);
    }

    if (cont > 4)
    {
        cont = 4;
    }
    if (cont < 0)
    {
        cont = 0;
    }
}

void display(void)
{
    //MOSTRAR 4
    if (cont == 4)
    {
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, GPIO_PIN_1);  //1
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0);  //2
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0);  //3
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, GPIO_PIN_4);  //4
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, GPIO_PIN_0);  //0 pin medio
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0);  //5
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, GPIO_PIN_3);  //6
    }
    //MOSTRAR 3
    if (cont == 3)
    {
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, GPIO_PIN_1);  //1
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_PIN_2);  //2
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0);  //3
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0);  //4
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, GPIO_PIN_0);  //0 pin medio
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_PIN_5);  //5
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, GPIO_PIN_3);  //6
    }
    //MOSTRAR 2
    if (cont == 2)
    {
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0);  //1
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_PIN_2);  //2
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, GPIO_PIN_3);  //3
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0);  //4
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, GPIO_PIN_0);  //0 pin medio
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_PIN_5);  //5
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, GPIO_PIN_3);  //6
    }
    //MOSTRAR 1
    if (cont == 1)
    {
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, GPIO_PIN_1);  //1
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0);  //2
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0);  //3
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0);  //4
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0);  //0 pin medio
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0);  //5
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, GPIO_PIN_3);  //6
    }
    //MOSTRAR 0
    if (cont == 0)
    {
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, GPIO_PIN_1);  //1
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_PIN_2);  //2
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, GPIO_PIN_3);  //3
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, GPIO_PIN_4);  //4
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0);  //0 pin medio
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_PIN_5);  //5
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, GPIO_PIN_3);  //6
    }
}
//**************************INICIALIZA PUERTO F Y LEDS OUTPUTS-------------------
void initGPIOF(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,
    GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE,
    GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5);
    GPIOPinTypeGPIOOutput(
            GPIO_PORTD_BASE,
            GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_6
                    | GPIO_PIN_7);
    GPIOPinTypeGPIOOutput(
            GPIO_PORTE_BASE,
            GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4
                    | GPIO_PIN_5);
    GPIOPinTypeGPIOOutput(
            GPIO_PORTB_BASE,
            GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4
                    | GPIO_PIN_5);
}

