//Liberia de la LCD
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

#define _XTAL_FREQ 4000000

//******************************************************************************
//PROTOTIPOS DE FUNCIONES
//******************************************************************************
void setup(void);
void main(void);
//******************************************************************************
// CONFIGURACION LCD
//******************************************************************************
#ifndef LCD_lib
#define LCD_lib

#define _XTAL_FREQ 4000000
//definimos los puertos y pines con los que bamos a trabajar
#define LCD_PORT PORTD
#define RS       PORTEbits.RE0
#define RW       PORTEbits.RE1
#define EN       PORTEbits.RE2

#include <xc.h>
#include <stdint.h>

void lcd_init(void);

void lcd_cmd(uint8_t a);

void lcd_clear(void);

void lcd_move_cursor(uint8_t row, uint8_t col);

void lcd_write_char(uint8_t a);

void lcd_write_string(uint8_t *a);

void lcd_shift_right(void);

void lcd_shift_left(void);

void lcd_port(uint8_t a);

#endif //LCD_lib