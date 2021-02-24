/*
 * File:   rutina_adc.c
 * Author: Erick Daniel Aquino Paz
 * Carnet: 17319
 * Created on February 22, 2021, 11:32 PM
 */

//******************************************************************************
//IMPORTACION DE LIBRERIAS
//******************************************************************************
#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "sensor_lcd.h"
#include "sensor_adc.h"


//******************************************************************************
//VARIABLES
//******************************************************************************

uint8_t adc_data1 = 0;
uint8_t adc_data2 = 0;
uint8_t prueba1 = 0;
uint8_t prueba2 = 0;
uint8_t uart_data = 0;
uint8_t uart_cont = 0;
uint8_t str_pos = 0;

int ban_an1;
int ban_an2;

char* str_pot_a[6];
char* str_pot_b[5];

bool adc_flag = false;
bool eusart_flag = false;

//******************************************************************************
//CICLO PRINCIPAL
//******************************************************************************

void main(void) {
    setup();
    while (1) {
        if (ADCON0bits.GO_DONE == 0 && ban_an1 == 0) {
            ADC_1();
        }
        if (ADCON0bits.GO_DONE == 0 && ban_an2 == 0) {
            ADC_2();
        }
        sprintf(str_pot_a, "A%.3iC", adc_data1 << 1);
        sprintf(str_pot_b, "B%.3iC%", adc_data2 << 1);

        display();
        semaforo();
    }
}

//******************************************************************************
//FUNCIONES
//******************************************************************************

void display(void) {
    lcd_move_cursor(0, 0);
    lcd_write_string("  T:  T:  Null: ");
    lcd_move_cursor(1, 0);

    char* str[3];

    sprintf(str, "%.3i", uart_cont);

    lcd_write_char(str_pot_a[1]);
    lcd_write_char('.');
    lcd_write_char(str_pot_a[2]);
    lcd_write_char(str_pot_a[3]);
    lcd_write_char(str_pot_a[4]);
    lcd_write_char(' ');

    lcd_write_char(str_pot_b[1]);
    lcd_write_char('.');
    lcd_write_char(str_pot_b[2]);
    lcd_write_char(str_pot_b[3]);
    lcd_write_char(str_pot_b[4]);
    lcd_write_char(' ');

    lcd_write_char(str[0]);
    lcd_write_char(str[1]);
    lcd_write_char(str[2]);
    lcd_write_char(str[3]);
}

void canal_10(void) {
    //SELECIONAMOS EL CANAL AN12
    //an12 1100
    ADCON0bits.CHS3 = 1;
    ADCON0bits.CHS2 = 1;
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS0 = 0;
}

void canal_12(void) {
    //SELECIONAMOS EL CANAL AN10
    //an10 1010
    ADCON0bits.CHS3 = 1;
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS1 = 1;
    ADCON0bits.CHS0 = 0;
}

void ADC_1(void) {
    adc_data1 = ADRESH;
    //prueba = adc_data1;
    ban_an1 = 1;
    ban_an2 = 0;
    canal_12();
    ADCON0bits.GO_DONE = 1;
}

void ADC_2(void) {
    adc_data2 = ADRESH;
    ban_an1 = 0;
    ban_an2 = 1;
    canal_10();
    ADCON0bits.GO_DONE = 1;
}

//******************************************************************************
// INTERRUPCIONES
//******************************************************************************

void __interrupt() isr(void) {
    if (PIR1bits.ADIF) {
        PIR1bits.ADIF = 0;

        if (adc_flag) {
            adc_data1 = ADRESH;
            prueba1 = ((adc_data1 * 5.0) / 255)*100;

        } else {
            adc_data2 = ADRESH;
        }

        adc_flag = !adc_flag;
    }

}

void semaforo(void) {
    if (prueba1 < 24) {
        PORTCbits.RC0 = 1;
        PORTCbits.RC1 = 0;
        PORTCbits.RC2 = 0;
    }
    if (prueba1 > 25 && prueba1 < 35) {
        PORTCbits.RC0 = 0;
        PORTCbits.RC1 = 1;
        PORTCbits.RC2 = 0;
    }
    if (prueba1 > 36) {
        PORTCbits.RC0 = 0;
        PORTCbits.RC1 = 0;
        PORTCbits.RC2 = 1;
    }
}