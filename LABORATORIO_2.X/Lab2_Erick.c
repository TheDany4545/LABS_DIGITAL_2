/* 
 * File:   mainTemplate.c
 * Author: Erick Daniel Aquino Paz
 * Carnet 17319
 * Plantilla/titulo del proyecto
 */

//******************************************************************************
//IMPORTACION DE LIBRERIAS
//******************************************************************************
//#include <xc.h>
//#include "PIC16F887.h"  
//******************************************************************************
//IMPORTACION DE LIBRERIAS Y CONFIG DEL PIC
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

//Frecuencia del oscilador
#define _XTAL_FREQ 8000000

//############## DECLARACION DE VARIABLES #######################

#include <xc.h>

//******************************************************************************
//PROTOTIPOS DE FUNCIONES
//******************************************************************************
void main(void);
void ADC(void);
void contadorbinario(void);
void setup(void);
//******************************************************************************
//DECLARACION DE VARIABLES
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
void main(void) {

    //while(1); 
    setup();
    /*while(1){
        contadorbinario();        
    }*/
    contadorbinario();
    return;
}
//******************************************************************************
//CONFIGURACION
//******************************************************************************

void setup(void){
    
    //###############OSCILADOR 8MH###################################
    OSCCONbits.IRCF = 0b111; //DE 8MH 
    OSCCONbits.SCS = 0b00; // 

    // CONFIGURACION DE PUERTOS 
    TRISA = 0b00000000; //PUERTO A COMO SALIDA PARA LEDS
    TRISB = 0b01111111; //PUERTO B COMO ENTRADA PAFRA PUSH Y POT
    TRISC = 0b00000000; //PUERTO C COMO SALIDA  DISPLAY
    TRISD = 0b00000000; //PUERTO D COMO SALIDA CONTADOR
    TRISE = 1; // PUERTO E COMO  entrada

    PORTA = 0b00000000; // LIMPIAMOS LOS PUERTOS 
    PORTB = 0b00000000; // LIMPIAMOS LOS PUERTOS 
    PORTC = 0b00000000; // LIMPIAMOS LOS PUERTOS 
    PORTD = 0b00000000; // LIMPIAMOS LOS PUERTOS 
    PORTE = 0b00010; // LIMPIAMOS LOS PUERTOS RE1 Inicia Encendido
    ANSELH = 0; //PARA PONER LAS ENTRADAS COMO DIGITALES 

    ///CONFIGURACION DEL ADC 
    //CONFIGURO EL AN6 RE1 COMO ENTRADA ANALOGICA
    ANSELbits.ANS6 = 0; // Pin con funcion especial ENTRADA DEL POT

    //SELECCION DEL FOSC/8
    ADCON0bits.ADCS0 = 1;
    ADCON0bits.ADCS1 = 0; // CONVERSION CLOCK SELECT BITS FOSC 8

    //SELECIONAMOS EL CANAL 
    ADCON0bits.CHS0 = 0;
    ADCON0bits.CHS1 = 1;
    ADCON0bits.CHS2 = 1;
    ADCON0bits.CHS3 = 0; //AN6 Analog select bits RE1

    //PINES DE REFERENCIA 
    ADCON1bits.VCFG0 = 0; //VDD
    ADCON1bits.VCFG1 = 0; //VSS
    //JUSTIFICACION IZQUIERDA 
    ADCON1bits.ADFM = 0;

    //CONFIGURACION DEL PUERTO 
    //ADCON1bits.ADFM = 0;

    //PARA CONVERSION DEL ADC
    ADCON0bits.GO_DONE = 1;//conversion del adc en progreso enabled

    //PARA HABILITAR ADC 
    ADCON0bits.ADON = 1;


    //HABIITAR INTERRUPCIONES DEL ADC Y GLOBALES
    INTCONbits.GIE = 1;//INTERRUPCIONES GLOBALES
    PIE1bits.ADIE = 0;
    PIE1bits.ADIE = 1;// interrupciones del ADC
    
    //PIR1bits.ADIF






    //#########HABILITOS LAS INTERRUPCIONES DEL PUERTO B#########
    INTCONbits.GIE = 1; //interrupcion global  
    INTCONbits.RBIF = 0; //SE LIMPIA
    INTCONbits.RBIF = 1; //SE PONE HABILITADO LA BANDERA DEL INTERRUPT ON CHANGE HACE QUE PUEDA USAR LAS INTERRUPCIONES EN EL PUERTO B
    IOCB = 1; //HABILITO LAS INTERRUPCIONES DEL PUERTO B
    IOCBbits.IOCB0 = 1; //LA BANDERA EN PUERTO B0
    IOCBbits.IOCB3 = 1; //BANDERA EN PUERTO B3 

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

