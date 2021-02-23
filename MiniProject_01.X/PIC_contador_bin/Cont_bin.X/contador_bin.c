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
        
    } while (ciclo == 1);
}