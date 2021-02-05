//Erick Aquino
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
#include"PIC16f887.h"

//******************************************************************************
//CONFIGURACION
//******************************************************************************
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

#define _XTAL_FREQ 8000000


//******************************************************************************
//VARIABLES
//******************************************************************************

//******************************************************************************
//PROTOTIPOS DE FUNCIONES
//******************************************************************************
void main(void);
void setup(void);
void serial(void);



//******************************************************************************
//CICLO PRINCIPAL
//******************************************************************************

void main(void) {

    setup();

    //**************************************************************************
    //LOOP PRINCIPAL
    //**************************************************************************

    while (1) {
		//ANTIRREBOTE
        if(PORTBbits.RB0 == 0){
            estado = 1;
        }
        if(PORTBbits.RB0 == 1 && estado ==1){
            contador = contador+1;
            estado =0;
        }
		if(PORTBbits.RB1 == 0){
            estado = 1;
        }
        if(PORTBbits.RB1 == 1 && estado ==1){
            contador = contador+1;
            estado =0;
        }
		if(ADCON0bits.GO_DONE == 0){
			//hago la conversion...
		}
		serial();
	}
}

//******************************************************************************
//CONFIGURACION
//******************************************************************************

void setup(void) {
    TRISA = 0; //PUERTO A COMO SALIDA 
    TRISB = 1; //PUERTO B COMO ENTRADA PUSH Y POTENCIOMETRO
    TRISC = 0; //PUERTO C COMO SALIDA DE LEDS
    TRISD = 0; //PUERTO D COMO SALIDA DE DISPLAYS
    TRISE = 1; //PUERTO E COMO ENTRADA

    PORTA = 0; //INICIAN LIMPIOS
    PORTB = 0; //INICIAN LIMPIOS
    PORTC = 0; //INICIAN LIMPIOS
    PORTD = 0; //INICIAN LIMPIOS
    PORTE = 0; //INICIAN LIMPIOS

    ANSEL = 0;
    ANSELH = 0; //ENTRADAS DIGITALES
    //**************************************************************************
    //ADC CONFIG
    //**************************************************************************
    //ANSELbits.ANS6 = 0; // ANS6 RE1 COMO ENTRADA
    //FOSC/8 SELECCION - CONVERSION CLOCK SELECT BITS
    ADCON0bits.ADCS0 = 1;
    ADCON0bits.ADCS1 = 0; // SETEAMOS 01 QUE ES FOSC/8
    //SELECCIONAMOS EL CANAL
    ADCON0bits.CHS0 = 1;
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS2 = 1;
    ADCON0bits.CHS3 = 1; //AN11 RB4

    //PINES DE REFERENCIA
    ADCON1bits.VCFG0 = 0; //VDD
    ADCON1bits.VCFG1 = 0; //VSS
    //A/D CONVERSION RESULT FORMAT - JUSTIFICACION A LA IZQUIERDA
    ADCON1bits.ADFM = 0; //JUSTIFICACION A LA IZQUIERDA
    //CONVERSION DEL ADC
    ADCON0bits.GO_DONE = 1; //CONVERSION STATUS IN PROGRESS
    ADCON0bits.ADON = 1; //ADC IS ENABLED

    //ENCENDER BANDERA DEL ADC
    INTCONbits.GIE = 1; //GLOBAL INTERRUPT ENABLED
    INTCONbits.PEIE = 1; //INTERRUPCIONES PERIFERICAS ACTIVADAS PARA EL ADC
    INTCONbits.INTE = 1; //INTERRUPCIONES EXTERNAS ACIVADAS
    PIE1bits.ADIE = 1; //ENCIENDO LAS INTERRPCIONES DEL ADC
    PIR1bits.ADIF = 0; // A/D CONVERSION COMPLETE

}

//******************************************************************************
//FUNCIONES
//******************************************************************************
void serial(void){
	//hacer comunicacion serial entre ascii y binario
}
