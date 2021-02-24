/* 
 * File:   lib_adc.c
 * Author: Daniel
 * Carne 17319
 * Created on February 22, 2021, 11:50 PM
 */


#include <xc.h>
#include "sensor_lcd.h"
#include "sensor_adc.h"
#define tmr_preload 6;

int ban_an1;
int ban_an2;

//******************************************************************************
// CONFIGURACION DE LA LCD
//******************************************************************************
//iniciación del lcd realizando la secuencia de inización mostrada en clase
void lcd_init()
{
    lcd_port(0x00);
    __delay_ms(20); 

    lcd_cmd(0x30);
    __delay_ms(5);

    lcd_cmd(0x30);
    __delay_ms(11);

    lcd_cmd(0x30);
    /////////////////////////////////////////////////////
    lcd_cmd(0x38);
    lcd_cmd(0x10);
    lcd_cmd(0x01);
    lcd_cmd(0x06);
    lcd_cmd(0x0F); // display on, cursor on, blink on
}
//manda los datos al puerto de display
void lcd_port(uint8_t a)
{
    #ifdef LCD_PORT
    LCD_PORT = a;
    #endif

    #ifndef LCD_PORT
    if(a & 1)
		D0 = 1;
	else
		D0 = 0;

	if(a & 2)
		D1 = 1;
	else
		D1 = 0;

	if(a & 4)
		D2 = 1;
	else
		D2 = 0;

	if(a & 8)
		D3 = 1;
	else
		D3 = 0;
	if(a & 16)
		D4 = 1;
	else
		D4 = 0;

	if(a & 32)
		D5 = 1;
	else
		D5 = 0;

	if(a & 64)
		D6 = 1;
	else
		D6 = 0;

	if(a & 128)
		D7 = 1;
	else
		D7 = 0;
    
    #endif
}
//configura el display para comandos y manda el valor introducido
void lcd_cmd(uint8_t cmd)
{
    RS = 0;             // => RS = 0
    lcd_port(cmd);

    EN  = 1;             // => E = 1
    __delay_ms(4);
    EN  = 0;             // => E = 0
}
//linpiamos la pantalla
void lcd_clear(void)
{
    lcd_cmd(0);
    lcd_cmd(1);
}

// Seteamos la columna y fila de la lcd
void lcd_move_cursor(uint8_t row, uint8_t col)
{
    if(row == 0)
    {
        lcd_cmd(0x80 + col);
    }
    else if(row == 1)
    {
        lcd_cmd(0xC0 + col);
    }
}
//escribimos un unico caracter en el lcd
void lcd_write_char(uint8_t data)
{
    RS = 1;             // => RS = 1
    lcd_port(data);

    EN  = 1;             // => E = 1
    __delay_ms(4);
    EN  = 0;             // => E = 0
}
//tomamos a un string y lo dividimos en caracteres y uno a uno en el lcd
void lcd_write_string(uint8_t *a)
{
    for(int i=0; a[i] != '\0'; i++)
    {
       lcd_write_char(a[i]);
    }
}
//Movemos los caracteres achia la derecha
void lcd_shift_right()
{
    lcd_cmd(0x1C);
}
//Movemos los caracteres achia la inzquierda
void lcd_shift_left()
{
    lcd_cmd(0x18);
}


//******************************************************************************
// CONFIGURACION DEL ADC, ENTRADAS Y SALIDAS
//******************************************************************************
void setup(void)
{
    ANSEL  = 0x03;
    ANSELH = 0x00;
    
    TRISA = 0x03;
    TRISB = 0x00;
    TRISC = 0;
    TRISD = 0x00;
    TRISE = 0x00;
    
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;

    // interrupts
    IOCB = 0x00;
    INTCONbits.RBIE = 0;
    INTCONbits.T0IE = 0;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    
    OSCCON = 0b01100001;

    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS2 = 0;
    OPTION_REGbits.PS1 = 0;
    OPTION_REGbits.PS0 = 1;

    TMR0 = tmr_preload;

    INTCONbits.T0IF = 0;
/*
    adc_config();
    adc_isr_enable();
*/
    lcd_init();
    lcd_cmd(0x0c); // turn off cursor

    //eusart_init_tx();
    //eusart_enable_tx_isr();

    //eusart_init_rx();
    //eusart_enable_rx_isr();

    ///CONFIGURACION DEL ADC 
    ANSELHbits.ANS10 = 1;
    ANSELHbits.ANS12 = 1;
    
    //SELECIONAMOS EL CANAL 
    //an12 1100
    //an10 1010
    ADCON0bits.CHS0 = 1;
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS2 = 1;
    ADCON0bits.CHS3 = 0;

    //PINES DE REFERENCIA 
    ADCON1bits.VCFG0 = 0; //VDD
    ADCON1bits.VCFG1 = 0; //VSS
    
    //JUSTIFICACION IZQUIERDA 
    ADCON1bits.ADFM = 0;


    //PARA CONVERSION DEL ADC
    ADCON0bits.GO_DONE = 1;

    //PARA HABILITAR ADC 
    ADCON0bits.ADON = 1;

    //ENCENDER BANDERA DEL ADC
    INTCONbits.GIE = 1;//INTERRUPCIONES GLOBALES
    PIE1bits.ADIE = 0;
    PIE1bits.ADIE = 1;// interrupciones del ADC
    
    ban_an1 = 0;
    ban_an2 = 1;
    canal_10();
    return;
}
