/* 
 * Se utilizó y se adaptaron las librerías de Ligo George 
 * de la página www.electrosome.com
 * Enlace: https://electrosome.com/lcd-pic-mplab-xc8/
 */
 
 #ifndef __LABOR3_H_
#define	__LABOR3_H_
#include <stdint.h>
#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define _XTAL_FREQ  4000000
#define  LCD PORTD
#define  POT1 PORTEbits.RE1
#define  POT2 PORTAbits.RA0
#define  RS  PORTCbits.RC5
#define  RW  PORTCbits.RC6
#define  EN  PORTCbits.RC7
#define LCD_PRIMERA_FILA 128
#define LCD_SEGUNDA_FILA 192
#define LCD_FUNCION_8BITS 56
#define LCD_BORRAR 1
#define LCD_APAGAR_CURSOR_ENCENDER_DISPLAY 12
#define LCD_MODO_INGRESO 6 

//*****************************************************************************
//Prototipos de funciones
//*****************************************************************************
void print (void);
void lcd_ini (void);
//void lcd_sal2 (uint8_t y, uint8_t x, char *buffer);
//void lcd_char (uint8_t dato);
void lcd_com (uint8_t dato);
void lcd_ready(void);
void lcd_msg(unsigned char *c);
void lcd_dwr(unsigned char x);
void adcInit (void);
void floattochar (float valor);
//void reverse(char s[]);
//void itoa(int n, char s[]);


//Se declaran las Variables que no son internas y se utilizan en el programa
//unsigned char buffer[17];
//uint8_t i;
uint8_t valana;
char valana1[8];
char valana2[8];
char valana3[8];
float voltaje;
int valanapot1;
int valanapot2;
int valanapot3;
float valor;

#endif