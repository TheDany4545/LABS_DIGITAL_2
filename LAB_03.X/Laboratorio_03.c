/* 
 * File:   mainTemplate.c
 * Author: Erick Daniel Aquino Paz
 * Carnet 17319
 * Plantilla/titulo del proyecto
 * Se utilizo una libreria para la función de inicializar la conección USART
 * Enlace: https://exploreembedded.com/wiki/UART
 */

//******************************************************************************
//IMPORTACION DE LIBRERIAS
//******************************************************************************
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pic16f887.h>
#include "lib_lab03.h"

//******************************************************************************
//CONFIGURACION
//******************************************************************************
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON      // Power-up Timer Enable bit (PWRT disabled)
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

#define _XTAL_FREQ 4000000

//******************************************************************************
//VARIABLES
//******************************************************************************
//ya vienen en las librerias
//******************************************************************************
//PROTOTIPOS DE FUNCIONES
//******************************************************************************
//ya estan declaradas en  la libreria lib_lab03
void setup(void);


//******************************************************************************
//CICLO PRINCIPAL
//******************************************************************************

void main(void) {

    //setup();

    //**************************************************************************
    //LOOP PRINCIPAL
    //**************************************************************************

    while (1) {
        setup();
        adcInit ();
        lcd_msg ("POT1 POT2 DISTA.");
        PORTAbits.RA3 = 0;
        ADCON0bits.CHS = 0;
        __delay_ms(50);
        print();
        floattochar(voltaje);
        __delay_ms(5);
        lcd_com(192);
        itoa(valana1,valanapot1,10);
        itoa(valana2,valanapot2,10);
        itoa(valana3,valanapot3,10);
        lcd_msg (valana1);
        lcd_com(193);
        lcd_msg (".");
        lcd_com(194);
        lcd_msg (valana2);
        lcd_com(195);
        lcd_msg (valana3);
        voltaje = 0;
        valana=0;

        PORTAbits.RA3 =1;
        __delay_ms(1);
    
        ADCON0bits.CHS = 1;
        __delay_ms(200);
        print();
        floattochar(voltaje);
        __delay_ms(5);
        lcd_com(197);
        itoa(valana1,valanapot1,10);
        itoa(valana2,valanapot2,10);
        itoa(valana3,valanapot3,10);
        lcd_msg (valana1);
        lcd_com(198);
        lcd_msg (".");
        lcd_com(199);
        lcd_msg (valana2);
        lcd_com(200);
        lcd_msg (valana3);

    }
}

//******************************************************************************
//CONFIGURACION
//******************************************************************************

void setup(void) {
    //Se declaran todos los iniciadores del pic, LCD y ADC
    OSCCONbits.IRCF =0b110;
    OSCCONbits.OSTS= 0;
    OSCCONbits.HTS = 0;
    OSCCONbits.LTS = 0;
    OSCCONbits.SCS = 1;
    //Declaratoria de puertos analógicos
    ANSEL = 0b00000011;  //defino los puertos analogicos
    ANSELH = 0b00000000;
    //Declaratoria de entradas y salidas de pines del pic
    TRISA = 0b00000011; //defino el pin del puerto como entrada
    TRISE = 0b00000100;
    TRISC = 0;
    TRISD = 0;
    TRISB = 0;
    //Definición del valor de inicio de cada puerto
    PORTA = 0;
    PORTE = 0;
    PORTC = 0;
    PORTD = 0;
    PORTB = 0;
    //Se inicializa la LCD y luego se manda a borrar por si existia un valor previo en la LCD
    lcd_ini();
    lcd_com(LCD_BORRAR);
    __delay_ms(20);
}

//******************************************************************************
//FUNCIONES
//******************************************************************************
//Iniciar el ADC
void adcInit (void){
    ADCON1bits.ADFM =0;
    ADCON1bits.VCFG0 =0;
    ADCON1bits.VCFG1 =0;
    ADCON0bits.ADCS0 =1;
    ADCON0bits.ADCS1 =0;
    ADCON0bits.CHS = 0;
    ADCON0bits.ADON = 1;
    return;
}
//Leer los valores analogicos pasarlos de float a char
void floattochar (float valor){
    
    valanapot1 = valor;
    valanapot2 = (valor-valanapot1)*10;
    valanapot3 = (((valor-valanapot1) *10)-valanapot2) *10;
    return;
}
//da el valoe del voltaje en la LCD con un corrimiento de bits y lectura
// del valor analogico del ADC
void print(void){
        __delay_ms(10);
        ADCON0bits.GO_DONE=1;
        while(ADCON0bits.GO_DONE);
        valana=ADRESH;
        voltaje=(valana*5.0)/255.0;
        __delay_ms(5);
        return;
}

//Función que inicia comando de la LCD
void lcd_ini(void){
    __delay_ms(30);
    lcd_com(LCD_FUNCION_8BITS);
    lcd_com(LCD_APAGAR_CURSOR_ENCENDER_DISPLAY);
    lcd_com(LCD_BORRAR);
    lcd_com(LCD_MODO_INGRESO);
    lcd_com(LCD_PRIMERA_FILA);
}

//Aplica el enable y su respectivo delay para ser llamado entre comandos.
void enable (void){
    EN = 0;
    __delay_ms(15);
    EN = 1;
}
//Función encargada de procesar los datos del comando mandando en la función
//lcd_ini().
void lcd_com(uint8_t dato){
    LCD = 0xFF;
    LCD = 0x14;  
    LCD &= 0x80;
    RS = 0;
    RW = 1;
    enable();
    if (LCD == 0x80){
        enable();
    } 
    LCD = dato;
    RS = 0;
    RW = 0;
    enable();
    __delay_ms(5);
    return;
}
void lcd_ready(void) {
    LCD = 0xFF;
    LCD &= 0x80;
    RS = 0;
    RW = 1;
    EN = 0;
    __delay_ms(30);
    EN = 1;
    if (LCD == 0x80){
    EN = 0;
    __delay_ms(30);
    EN = 1;  
    }
    else{   
    }    
}

//Funciones que definen fila y puntero del cursor y procesa el string realizado
void lcd_dwr(unsigned char x){
    lcd_ready();
    LCD = x;
    RS = 1;
    RW = 0;
    enable(); 
}

void lcd_msg(unsigned char *c){
    while(*c != 0)
        lcd_dwr(*c++);
}
//funciones que definen fila y puntero del cursos y procesar el string realizado
char UART_Init(const long int baudrate)
{
	unsigned int x;
	x = (_XTAL_FREQ - baudrate*64)/(baudrate*64);
	if(x>255)
	{
		x = (_XTAL_FREQ - baudrate*16)/(baudrate*16);
		BRGH = 1;
	}
	if(x<256)
	{
	  SPBRG = x;
	  SYNC = 0;
	  SPEN = 1;
          TRISC7 = 1;
          TRISC6 = 1;
          CREN = 1;
          TXEN = 1;
	  return 1;
	}
	return 0;
}

char UART_TX_Empty()
{
  return TRMT;
}

char UART_Data_Ready()
{
   return RCIF;
}
char UART_Read()
{
 
  while(!RCIF);
  return RCREG;
}

void UART_Read_Text(char *Output, unsigned int length)
{
	unsigned int i;
	for(int i=0;i<length;i++)
		Output[i] = UART_Read();
}

void UART_Write(char data)
{
  while(!TRMT);
  TXREG = data;
}

void UART_Write_Text(char *text)
{
  int i;
  for(i=0;text[i]!='\0';i++)
	  UART_Write(text[i]);
}


//*************** Comunicacion serial*******************************************
