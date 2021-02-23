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
#include "lcd.h"
#include "adc.h"


//******************************************************************************
//VARIABLES
//******************************************************************************

uint8_t adc_data1 = 0;
uint8_t adc_data2 = 0;
uint8_t uart_data = 0;
uint8_t uart_cont = 0;
uint8_t str_pos   = 0;

int ban_an1;
int ban_an2;

char* str_pot_a[6];
char* str_pot_b[5];

bool    adc_flag     = false;
bool    eusart_flag  = false;
//******************************************************************************
//CICLO PRINCIPAL
//******************************************************************************
void main(void)
{
    
}

//******************************************************************************
//FUNCIONES
//******************************************************************************
