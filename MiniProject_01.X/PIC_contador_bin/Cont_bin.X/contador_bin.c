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
#include "contador.h"
//******************************************************************************
//VARIABLES
//******************************************************************************
int cont0 = 0;
char ciclo = 1;
char todo = 1;
int adc;
float volt;
const unsigned char display[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
int H;//Multiplexado
int L;
int suma; //comparacion entre el contador y los displays

//******************************************************************************
//CICLO PRINCIPAL
//******************************************************************************

void main(void) 
{
    setup();
    contadorbinario();
}

//******************************************************************************
//FUNCIONES
//******************************************************************************
void contadorbinario(void) {
    __delay_ms(300);
    do {
        if (IOCBbits.IOCB0 = 1 && PORTBbits.RB0 == 1) {
            //PORTBbits.RB7 = 1;
            cont0++;
            __delay_ms(500);
            IOCBbits.IOCB0 = 0;
            do {
                //********
            } while (PORTBbits.RB0 == 1);
            PORTA = cont0;
        }
        if (IOCBbits.IOCB3 = 1 && PORTBbits.RB3 == 1) {
            cont0--;
            __delay_ms(500);
            do {
                //********
            } while (PORTBbits.RB3 == 1);
            PORTA = cont0;
            IOCBbits.IOCB3 = 0;
        }
        if (cont0 > 255) {
            cont0 = 0;
        }

        if (ADCON0bits.GO_DONE == 0) {
            //ADCON0bits.GO_DONE = 1;            
            H = ADRESH;
            L = ADRESH;
            //__delay_ms(5);
            H = ((H/16)%16);//DIVISION DE H/16 display izquierdo
            L = (L%16);//RESIDUO DE LA DIVISION display derecho
            suma = ADRESH;
            PORTD = display[H];
            PORTCbits.RC0 = 1;
            PORTCbits.RC0 = 0;
            //PORTCbits.RC1 = 0;
            PORTD = display[L];
            //PORTCbits.RC0 = 0;
            PORTCbits.RC1 = 1;
            PORTCbits.RC1 = 0;
            ADCON0bits.GO_DONE =1;
            
            //adc = ADRESL;
            //adc = adc << 8;
            //adc = adc + ADRESH;
            //PORTD = adc;
        }
        if (cont0<suma){
            PORTBbits.RB7 = 1;           
        }
        else{
            PORTBbits.RB7 = 0;
        }
    } while (ciclo == 1);
}