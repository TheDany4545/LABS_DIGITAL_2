//Erick Daniel Aquino Paz
//libreria contador binario
//#include<xc.h>
//#include<pic16f887.h>
#include "contador.h"

//******************************************************************************
//CONFIGURACION DE PUERTOS
//******************************************************************************
void setup(void)
{
    //oscilador
    //Puertos
    TRISA = 0b00000000; //PUERTO A COMO SALIDA PARA LEDS
    TRISB = 0b01111111; //PUERTO B COMO ENTRADA PAFRA PUSH Y POT

    PORTA = 0b00000000; // LIMPIAMOS LOS PUERTOS 
    PORTB = 0b00000000; // LIMPIAMOS LOS PUERTOS 

    ANSELH = 0; //PARA PONER LAS ENTRADAS COMO DIGITALES 
    
    //#########HABILITOS LAS INTERRUPCIONES DEL PUERTO B#########
    INTCONbits.GIE = 1; //interrupcion global  
    INTCONbits.RBIF = 0; //SE LIMPIA
    INTCONbits.RBIF = 1; //SE PONE HABILITADO LA BANDERA DEL INTERRUPT ON CHANGE HACE QUE PUEDA USAR LAS INTERRUPCIONES EN EL PUERTO B
    IOCB = 1; //HABILITO LAS INTERRUPCIONES DEL PUERTO B
    IOCBbits.IOCB0 = 1; //LA BANDERA EN PUERTO B0
    IOCBbits.IOCB3 = 1; //BANDERA EN PUERTO B3    
}