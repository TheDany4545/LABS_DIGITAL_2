/* 
 * File:   mainTemplate.c
 * Author: Erick Daniel Aquino Paz
 * Carnet 17319
 * Plantilla/titulo del proyecto
 */

//******************************************************************************
//IMPORTACION DE LIBRERIAS
//******************************************************************************
#include <xc.h>



void main(void) {
    
    OSCCONbits.IRCF =0b110;
    OSCCONbits.OSTS= 0;
    OSCCONbits.HTS = 0;
    OSCCONbits.LTS = 0;
    OSCCONbits.SCS = 1;
    
    ANSEL = 0b000000000;
    ANSELH = 0b00000000;
    
    SDO = 0;
    SDI = 1;
    SCK = 0;
    SS = 0;
    CONTADOR = 0;
    CONTADORPROVICIONAL = 0;
    BANDERA =0;
    
    PORTA = 0b00000000;
    PORTB = 0b00000000;
    PORTC = 0b00000000;
    PORTD = 0b00000000;
    PORTE = 0b0000;
    UART_Init(9600);
    spiMasterInit();
    
    
    
    
    
    while(1){
        __delay_ms(10);
        spiWrite(0);
        masterIn = spiRead();
        UARTR();
        UARTW(masterIn);
        //UARTR();
        //PORTD = uartIn;
        PORTB = uartIn;
        

    }    
}