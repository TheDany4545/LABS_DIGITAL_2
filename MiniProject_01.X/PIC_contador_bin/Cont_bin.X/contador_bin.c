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