// ******************** PIC16F877 y comunicacion I2C con Sensor) *********//
// ********************** Miniprojectt 2 *******************//
// ***************** I2C Communication Source Code ********************//
// ********************* Erick Daniel Aquino Paz **************************//
// *************** Basado en: https://www.projectyard.weebly.com *************//

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)


//*****************************************************************************
//LIBRERIAS
//*****************************************************************************

#include<pic.h>
#include<xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <pic16f887.h>
#include "eusart.h"


//******************************************************
//VARIABLES
//******************************************************
uint8_t r = 0;
char* recibo[];
uint8_t uart_data = 0;
uint8_t uart_cont = 0;
uint8_t str_pos   = 0;
bool    eusart_flag  = false;

//*******************************************************
//PROTOTIPOS DE FUNCIONES
void setup(void);
void funcion(void);
//****************** Supporting Data *****************//
unsigned char r;
char* d = "Detectando ...";
char* d1 = "Sensor listo";
char* d2 = "No hay sensor";
char* d3 = "Iniciando I2C";
char* tmp = "Temp :   *C";

//***************** LCD Ctrl Functions ******************//
void delay(unsigned int x)
{
	while(x--);
}

void LCD_cmd(char y)
{
	RC0 = 0; // LCD supply
	RC1 = 1; //LCD supply
	PORTB = y;
	delay(100);
    RC1 = 0;
    delay(100);
}

void LCD_data(char y)
{
	RC0 = 1;
	RC1 = 1;
	PORTB = y + 48;
	delay(100);
	RC1 = 0;
	delay(200);
}

//***************** LCD Display Functions *****************//
void no_dev_disp()
{
	LCD_cmd(0xc0);
	delay(100);
	RC0 = 1;
	while( *d2 != '\0')
	{
		RC1 = 1;
		delay(100);
		PORTB = *d2;
		delay(100);
		RC1 = 0;
		delay(100);
		*d2++; // NO HAY SENSOR 
	}
	while(1);
}

void dev_found_disp()
{
	LCD_cmd(0xc0);
	delay(100);
	RC0 = 1;
	while(*d1 != '\0')
	{
		RC1 = 1;
		delay(100);
		PORTB = *d1;
		delay(100);
		RC1 = 0;
		delay(100);
		*d1++; // SENSOR LISTO
	}
}

void temp_disp()
{
	LCD_cmd(0x01);
	LCD_cmd(0x80);
	delay(100);
	RC0 = 1;
	while( *tmp != '\0')
	{
		RC1 = 1;
		delay(100);
		PORTB = *tmp;
		delay(100);
		RC1 = 0;
		delay(100);
		tmp++; // MUESTRA TEMP
	}
}


//******************************************************************************
//******************* I2C Section *********************//
//******************************************************************************

//INICO EL I2C
void i2c_start()
{
	SEN = 1;
	while(SEN);
}

//mantener esperarando a que una interrupcion del MSSP ocurra
void i2c_wait()
{
	while(SSPIF==0);
	SSPIF = 0;
}

void i2c_rep_start()// Inicio la comunicacion con el bit de inicio
{
	RSEN = 1;
	while(RSEN);
}

void i2c_NACK()
{
	ACKDT = 1;
	ACKEN = 1;
	while(ACKEN);
}

void i2c_stop()
{
	i2c_wait();
	PEN = 1;
	while(PEN);
}

unsigned char i2c_rx()
{
	RCEN = 1;
	while(!BF);
	return SSPBUF;
}

unsigned char i2c_send(unsigned char c) //envio la direccion del 12c con el disp que me quiero comunicar
{
	SSPBUF = c;
	while(BF);
	i2c_wait();
}

//*************** Initialization Section ****************//
void setup()
{
   ANSEL  = 0x03;
    ANSELH = 0x00;
   
    TRISCbits.TRISC7 = 1;
    TRISCbits.TRISC6 = 1;
    TRISE = 0b000;
     
    PORTC = 0;
    PORTE = 0;
    OSCCON = 0b01100001;
   

    eusart_init_tx();
    eusart_enable_tx_isr();

    eusart_init_rx();
    eusart_enable_rx_isr();
    return;
}
void i2c_init()
{
	TRISC3 = 1;
	TRISC4 = 1;
	SSPBUF = 0x00;
	SSPSTAT = 0xc0;
	SSPCON = 0x28;
	SSPCON2 = 0x00;
	SSPIF = 0;
	SSPADD = 9;
}

void LCD_init()
{
	TRISB = 0x00;
	PORTB = 0x00;
	TRISC0 = 0;
	TRISC1 = 0;
	delay(200);
	LCD_cmd(0x0c);
	LCD_cmd(0x06);
	LCD_cmd(0x38);
	LCD_cmd(0x80);
}

//********** Temperature Display Function **************//
void LCD_disp(unsigned char y)
{
	int temp = y/10;
	LCD_data(temp);
	delay(100);
	temp = y%10;
	LCD_data(temp);
	delay(100);
}

//******** i2c Initialization Display Function ***********//
void i2c_init_disp()
{
	LCD_cmd(0x01);
	LCD_cmd(0x80);
	while( *d3 != '\0')
	{
		RC0 = 1;
		RC1 = 1;
		delay(100);
		PORTB = *d3;
		delay(200);
		RC1 = 0;
		d3++;
		delay(100);
	}
}

//************* Device Check Function **************//
int check_dev()
{
	SEN = 1;
	while(SEN);
	i2c_send(0b10010000);
	if(ACKSTAT)
	{
		RC2 = 1;
	}	
	PEN = 1;
	while(PEN);
	delay(65000);
	return RC2;
}

//****** Device Checking Display Function ********//
void check_dev_disp()
{
	LCD_cmd(0x01);
	LCD_cmd(0x80);
	delay(100);
	RC0 = 1;
	delay(100);
	while( *d != '\0')
	{
		RC1 = 1;
		delay(100);
		PORTB = *d;
		delay(100);
		RC1 = 0;
		delay(100);
		d++;
	}
	delay(65000);
	(check_dev() ? no_dev_disp() : dev_found_disp());
}

//****************** Main Function ****************//
void main()
{
	TRISC2 = 0; // Setting the "No_Dev_LED" (OUTPUT) Pin
	RC2 = 0;	
	
	LCD_init();		

	i2c_init_disp();
	delay(65000);
	i2c_init();
	
	check_dev_disp();
	delay(65000);
	temp_disp();
	while(1)
	{
        uart_data = 0;
		LCD_cmd(0x86);		// Setting the cursor position for displaying the temperature value

		i2c_rep_start();	// Inicio la comunicacion con el bit de inicio
		delay(4);

		i2c_send(0b10010000);  // SLAVE ADDRESS = 1001 1010 | Last bit is '0' - Write
		i2c_send(0x00);	 // Sending read command to the slave (0000 0000) | Refer the datasheet 

		i2c_rep_start(); // Again initiating the communication due to change in R/W bit
		delay(4);

		SSPBUF = 0b10010001; // Slave ADDRESS = 1001 1011 | Last bit is '1' - Read
		i2c_wait();
		delay(4);

		r = i2c_rx(); // Recieving the temp value in 8 bit format
		i2c_wait();

		i2c_NACK();  // After reception, Master sends the ACKN bit
		delay(4);

		i2c_stop(); // Corta la comuniacion
		delay(4);

		LCD_disp(r); // Mando los valores a la lcd
        
        funcion(); // mando a la usart con los valores converitdos
	}
}

//*********************************************************************
//INTERRUPCIONES
//********************************************************************

void __interrupt() isr(void)
{

    if (PIE1bits.TXIE && PIR1bits.TXIF)
    {
        if (eusart_flag)
        {
            TXREG = recibo[str_pos];
        }
        str_pos++;
        if (str_pos == 5)
        {
            eusart_flag = !eusart_flag;
            str_pos = 0;
        }
    }
    if (PIR1bits.RCIF)
    {
        uart_data = RCREG;
    }
}
void funcion(void)
{
    sprintf(recibo, " %2i ", r); // hace la conversion la uart
}
