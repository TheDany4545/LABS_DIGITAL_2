//***************************************************************************************************************************************
/* Librería para el uso de la pantalla ILI9341 en modo 8 bits
   Basado en el código de martinayotte - https://www.stm32duino.com/viewtopic.php?t=637
   Adaptación, migración y creación de nuevas funciones: Pablo Mazariegos y José Morales
   Con ayuda de: José Guerra
   IE3027: Electrónica Digital 2 - 2019
*/
//***************************************************************************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include <TM4C123GH6PM.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

#include "bitmaps.h"
#include "font.h"
#include "lcd_registers.h"

#define LCD_RST PD_0
#define LCD_CS PD_1
#define LCD_RS PD_2
#define LCD_WR PD_3
#define LCD_RD PE_1
//#define tonePin PA_2
int DPINS[] = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};
//***************************************************************************************************************************************
// Functions Prototypes
//***************************************************************************************************************************************
void LCD_Init(void);
void LCD_CMD(uint8_t cmd);
void LCD_DATA(uint8_t data);
void SetWindows(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void LCD_Clear(unsigned int c);
void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c);
void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c);
void LCD_Print(String text, int x, int y, int fontSize, int color, int background);

void LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]);
void LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[], int columns, int index, char flip, char offset);


extern uint8_t fondo[];
extern uint8_t explotar[];
extern uint8_t gala[];


int x = 0;
int x2 = 288;
int yb1 = 150;
int yb2 = 150;

int xbala1;
int xbala2;

int estado1 = 0;
int estado2 = 0;

int antirebote1 = 0;
int antirebote2 = 0;
int antirebote3 = 0;
int antirebote4 = 0;

int estado1b = 0;
int estado2b = 0;
int estado3b = 0;
int estado4b = 0;

int contBala = 0;
int contBala2 = 0;
int contBala3 = 0;
int contBala4 = 0;

int contBBala = 0;
int contBBala2 = 0;
int contBBala3 = 0;
int contBBala4 = 0;

int revisar_bala = 0;

int enemigo  = 0;
int enemigo2 = 0;
int enemigo3 = 0;
int enemigo4 = 0;

int enemigo5  = 0;
int enemigo6 = 0;
int enemigo7 = 0;
int enemigo8 = 0;

int enemigo9  = 0;
int enemigo10 = 0;
int enemigo11 = 0;
int enemigo12 = 0;

int enemigo13 = 0;
int enemigo14 = 0;
int enemigo15 = 0;
int enemigo16 = 0;

int enemigo17 = 0;
int enemigo18 = 0;
int enemigo19 = 0;
int enemigo20 = 0;

int enemigo21 = 0;
int enemigo22 = 0;
int enemigo23 = 0;
int enemigo24 = 0;

int enemigo25 = 0;
int enemigo26 = 0;
int enemigo27 = 0;
int enemigo28 = 0;

int enemigo29 = 0;
int enemigo30 = 0;
int enemigo31 = 0;
int enemigo32 = 0;

int menu = 0;
int tonePin = 40;
int start = 0;



//***************************************************************************************************************************************
// Inicialización
//***************************************************************************************************************************************
void setup() {


  pinMode(PA_3, INPUT_PULLUP);
  pinMode(PA_4, INPUT_PULLUP);
  pinMode(PA_5, INPUT_PULLUP);
  pinMode(PA_6, INPUT_PULLUP);

  pinMode(PF_0, INPUT_PULLUP);
  pinMode(PF_4, INPUT_PULLUP);
  pinMode(tonePin, OUTPUT);



  SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
  Serial.begin(9600);
  GPIOPadConfigSet(GPIO_PORTB_BASE, 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
  Serial.println("Inicio");
  LCD_Init();
  LCD_Clear(0x00);


  while (start == 0) {

    //midi();
    //FillRect(0, 0, 320, 240, 0x0000);
    LCD_Bitmap(0, 0, 320, 240, fondo);
    LCD_Bitmap(200, 20, 100, 75, gala);
    //LCD_Bitmap(50,50,50,50,gala);
    // LCD_Sprite(0, 0, 100, 100, galaga, 1, 0, 0, 0);
    String text1 = "GALAGA";
    String text2 = "Fernando Figueroa";
    String text3 = "Erick Aquino";
    String text4 = "Press 'START'";
    LCD_Print(text1, 20, 50, 2, 0x07E0, 0x0002);
    LCD_Print(text2, 20, 100, 2, 0x07E0, 0x0007);
    LCD_Print(text3, 20, 150, 2, 0x07E0, 0x0009);
    LCD_Print(text4, 50, 200, 2, 0xFFE0, 0x0002);
    midi();
    //delay(5000);


    //LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[],int columns, int index, char flip, char offset);

  }



  //LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]);
  LCD_Bitmap(0, 0, 320, 240, fondo);

  LCD_Sprite(138,  0, 32, 32, asteroide, 1, 0, 0, 0);
  LCD_Sprite(138, 40, 32, 32, asteroide, 1, 0, 0, 0);
  LCD_Sprite(138, 80, 32, 32, asteroide, 1, 0, 0, 0);
  LCD_Sprite(138, 120, 32, 32, asteroide, 1, 0, 0, 0);
  LCD_Sprite(138, 160, 32, 32, asteroide, 1, 0, 0, 0);
  LCD_Sprite(138, 200, 32, 32, asteroide, 1, 0, 0, 0);



  int anim = (x / 5) % 8;
  LCD_Sprite(0, 175, 32, 32, Nave, 3, anim, 1, 0);
  LCD_Sprite(288, 175, 32, 32, Nave, 3, anim, 1, 0);

}
//***************************************************************************************************************************************
// Loop Infinito
//***************************************************************************************************************************************
void loop() {


  if (enemigo == 0) {
    LCD_Sprite(18, 120, 32, 32, pulgon_verde, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(18, 120, 32, 32, explotar);
  }

  if (enemigo2 == 0) {
    LCD_Sprite(18, 90, 32, 32, pulgon_verde, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(18, 90, 32, 32, explotar);
  }

  if (enemigo3 == 0) {
    LCD_Sprite(18, 60, 32, 32, pulgon_verde, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(18, 60, 32, 32, explotar);
  }

  if (enemigo4 == 0) {
    LCD_Sprite(18, 30, 32, 32, pulgon_verde, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(18, 30, 32, 32, explotar);
  }

  ///////////////////////////////////////////////////////////////////

  if (enemigo5 == 0) {
    LCD_Sprite(48, 120, 32, 32, pulgon_rojo, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(48, 120, 32, 32, explotar);
  }

  if (enemigo6 == 0) {
    LCD_Sprite(48, 90, 32, 32, pulgon_rojo, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(48, 90, 32, 32, explotar);
  }

  if (enemigo7 == 0) {
    LCD_Sprite(48, 60, 32, 32, pulgon_rojo, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(48, 60, 32, 32, explotar);
  }

  if (enemigo8 == 0) {
    LCD_Sprite(48, 30, 32, 32, pulgon_rojo, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(48, 30, 32, 32, explotar);
  }

  ///////////////////////////////////////////////////////////////////


  if (enemigo9 == 0) {
    LCD_Sprite(75, 120, 32, 32, Pulgon_redondo, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(75, 120, 32, 32, explotar);
  }

  if (enemigo10 == 0) {
    LCD_Sprite(75, 90, 32, 32, Pulgon_redondo, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(75, 90, 32, 32, explotar);
  }

  if (enemigo11 == 0) {
    LCD_Sprite(75, 60, 32, 32, Pulgon_redondo, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(75, 60, 32, 32, explotar);
  }

  if (enemigo12 == 0) {
    LCD_Sprite(75, 30, 32, 32, Pulgon_redondo, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(75, 30, 32, 32, explotar);
  }

  ///////////////////////////////////////////////////////////////////


  if (enemigo13 == 0) {
    LCD_Sprite(105, 120, 30, 30, pulgon_azul, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(105, 120, 32, 32, explotar);
  }

  if (enemigo14 == 0) {
    LCD_Sprite(105, 90, 30, 30, pulgon_azul, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(105, 90, 32, 32, explotar);
  }

  if (enemigo15 == 0) {
    LCD_Sprite(105, 60, 30, 30, pulgon_azul, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(105, 60, 32, 32, explotar);
  }

  if (enemigo16 == 0) {
    LCD_Sprite(105, 30, 30, 30, pulgon_azul, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(105, 30, 32, 32, explotar);
  }

  //////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////


  if (enemigo17 == 0) {
    LCD_Sprite(171, 120, 32, 32, Pulgon_redondo, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(171, 120, 32, 32, explotar);
  }

  if (enemigo18 == 0) {
    LCD_Sprite(171, 90, 32, 32, Pulgon_redondo, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(171, 90, 32, 32, explotar);
  }

  if (enemigo19 == 0) {
    LCD_Sprite(171, 60, 32, 32, Pulgon_redondo, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(171, 60, 32, 32, explotar);
  }

  if (enemigo20 == 0) {
    LCD_Sprite(171, 30, 32, 32, Pulgon_redondo, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(171, 30, 32, 32, explotar);
  }

  /////////////////////////////////////////////////////////////////////////////////////////


  if (enemigo21 == 0) {
    LCD_Sprite(201, 120, 30, 30, pulgon_azul, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(201, 120, 32, 32, explotar);
  }

  if (enemigo22 == 0) {
    LCD_Sprite(201, 90, 30, 30, pulgon_azul, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(201, 90, 32, 32, explotar);
  }

  if (enemigo23 == 0) {
    LCD_Sprite(201, 60, 30, 30, pulgon_azul, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(201, 60, 32, 32, explotar);
  }

  if (enemigo24 == 0) {
    LCD_Sprite(201, 30, 30, 30, pulgon_azul, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(201, 30, 32, 32, explotar);
  }
  /////////////////////////////////////////////////////////////////////////////////


  if (enemigo25 == 0) {
    LCD_Sprite(231, 120, 32, 32, pulgon_verde, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(231, 120, 32, 32, explotar);
  }

  if (enemigo26 == 0) {
    LCD_Sprite(231, 90, 32, 32, pulgon_verde, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(231, 90, 32, 32, explotar);
  }

  if (enemigo27 == 0) {
    LCD_Sprite(231, 60, 32, 32, pulgon_verde, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(231, 60, 32, 32, explotar);
  }

  if (enemigo28 == 0) {
    LCD_Sprite(231, 30, 32, 32, pulgon_verde, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(231, 30, 32, 32, explotar);
  }
  /////////////////////////////////////////////////////////////////////////////////


  if (enemigo29 == 0) {
    LCD_Sprite(261, 120, 32, 32, pulgon_rojo, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(261, 120, 32, 32, explotar);
  }

  if (enemigo30 == 0) {
    LCD_Sprite(261, 90, 32, 32, pulgon_rojo, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(261, 90, 32, 32, explotar);
  }

  if (enemigo31 == 0) {
    LCD_Sprite(261, 60, 32, 32, pulgon_rojo, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(261, 60, 32, 32, explotar);
  }

  if (enemigo32 == 0) {
    LCD_Sprite(261, 30, 32, 32, pulgon_rojo, 1, 0, 0, 0);
  }
  else {
    LCD_Bitmap(261, 30, 32, 32, explotar);
  }

  /////////////////////////////////////////////////////////////////////////////////


  /*if((digitalRead(PA_3)==1 && antirebote1 ==0)){
    antirebote1 = 1;
    }*/
  if (digitalRead(PA_3) == 0) {
    x = x + 3;
    antirebote1 = 0;
    if (x > 105) {
      x = 105;
    }
    delay(30);
    int anim = (x / 5) % 8;
    LCD_Sprite(x, 175, 32, 32, Nave, 3, anim, 1, 0);
  }




  /*if(digitalRead(PA_4)==1){
    antirebote2 = 1;
    }*/
  if (digitalRead(PA_4) == 0) {
    x = x - 3;
    antirebote2 = 0;
    if (x < 0) {
      x = 0;
    }
    delay(30);
    int anim = (x / 5) % 8;
    LCD_Sprite(x, 175, 32, 32, Nave, 3, anim, 1, 0);
  }



  /*if((digitalRead(PA_5)==1 && antirebote3 ==0)){
    antirebote3 = 1;
    }*/
  if (digitalRead(PA_5) == 0) {
    x2 = x2 + 3;
    antirebote3 = 0;
    if (x2 > 288) {
      x2 = 288;
    }
    delay(30);
    int anim = (x2 / 5) % 8;
    LCD_Sprite(x2, 175, 32, 32, Nave, 3, anim, 1, 0);
  }


  /*if((digitalRead(PA_6)==1 &&  antirebote4 == 0)){
     antirebote4 = 1;
    }*/

  if (digitalRead(PA_6) == 0) {
    x2 = x2 - 3;
    antirebote4 = 0;
    if (x2 < 171) {
      x2 = 171;
    }
    delay(30);
    int anim = (x2 / 5) % 8;
    LCD_Sprite(x2, 175, 32, 32, Nave, 3, anim, 1, 0);
  }


  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  if ((digitalRead(PF_0) == 0) && (estado1 == 0)) {
    estado1 = 1;
    yb1 = 150;
    xbala1 = x;
  }
  if (yb1 > 0 && estado1 == 1 && contBala == 0) {
    yb1 = yb1 - 7;
    delay(5);
    LCD_Sprite(xbala1, yb1, 32, 32, bala, 1, 0, 1, 0);
    if (yb1 <= 0) {
      estado1 = 0;

    }
    if (yb1 <= 120 && xbala1 == 18 ) {
      enemigo = 1;
      contBala = 1;
      estado1 = 0;
    }
  }

  if ((digitalRead(PF_0) == 0) && (estado1 == 0)) {
    estado1 = 1;
    yb1 = 150;
    xbala1 = x;
  }
  if (yb1 > 0 && estado1 == 1 && contBala == 1) {
    yb1 = yb1 - 7;
    delay(5);
    LCD_Sprite(xbala1, yb1, 32, 32, bala, 1, 0, 1, 0);
    if (yb1 <= 0) {
      estado1 = 0;
    }
    if (yb1 <= 90 && xbala1 == 18 ) {
      enemigo2 = 1;
      contBala = 2;
      estado1 = 0;
    }
  }

  if ((digitalRead(PF_0) == 0) && (estado1 == 0)) {
    estado1 = 1;
    yb1 = 150;
    xbala1 = x;
  }
  if (yb1 > 0 && estado1 == 1 && contBala == 2) {
    yb1 = yb1 - 7;
    delay(5);
    LCD_Sprite(xbala1, yb1, 32, 32, bala, 1, 0, 1, 0);
    if (yb1 <= 0) {
      estado1 = 0;
    }
    if (yb1 <= 60 && xbala1 == 18 ) {
      enemigo3 = 1;
      contBala = 3;
      estado1 = 0;
    }
  }


  if ((digitalRead(PF_0) == 0) && (estado1 == 0)) {
    estado1 = 1;
    yb1 = 150;
    xbala1 = x;
  }
  if (yb1 > 0 && estado1 == 1 && contBala == 3) {
    yb1 = yb1 - 7;
    delay(5);
    LCD_Sprite(xbala1, yb1, 32, 32, bala, 1, 0, 1, 0);
    if (yb1 <= 0) {
      estado1 = 0;
    }
    if (yb1 <= 30 && xbala1 == 18 ) {
      enemigo4 = 1;
      contBala = 4;
      estado1 = 0;
    }
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if ((digitalRead(PF_0) == 0) && (estado1 == 0)) {
    estado1 = 1;
    yb1 = 150;
    xbala1 = x;
  }
  if (yb1 > 0 && estado1 == 1 && contBala2 == 0) {
    yb1 = yb1 - 7;
    delay(5);
    LCD_Sprite(xbala1, yb1, 32, 32, bala, 1, 0, 1, 0);
    if (yb1 <= 0) {
      estado1 = 0;
    }
    if (yb1 <= 120 && xbala1 == 48 ) {
      enemigo5 = 1;
      contBala2 = 1;
      estado1 = 0;
    }
  }

  if ((digitalRead(PF_0) == 0) && (estado1 == 0)) {
    estado1 = 1;
    yb1 = 150;
    xbala1 = x;
  }
  if (yb1 > 0 && estado1 == 1 && contBala2 == 1) {
    yb1 = yb1 - 7;
    delay(5);
    LCD_Sprite(xbala1, yb1, 32, 32, bala, 1, 0, 1, 0);
    if (yb1 <= 0) {
      estado1 = 0;
    }
    if (yb1 <= 90 && xbala1 == 48 ) {
      enemigo6 = 1;
      contBala2 = 2;
      estado1 = 0;
    }
  }

  if ((digitalRead(PF_0) == 0) && (estado1 == 0)) {
    estado1 = 1;
    yb1 = 150;
    xbala1 = x;
  }
  if (yb1 > 0 && estado1 == 1 && contBala2 == 2) {
    yb1 = yb1 - 7;
    delay(5);
    LCD_Sprite(xbala1, yb1, 32, 32, bala, 1, 0, 1, 0);
    if (yb1 <= 0) {
      estado1 = 0;
    }
    if (yb1 <= 60 && xbala1 == 48 ) {
      enemigo7 = 1;
      contBala2 = 3;
      estado1 = 0;
    }
  }


  if ((digitalRead(PF_0) == 0) && (estado1 == 0)) {
    estado1 = 1;
    yb1 = 150;
    xbala1 = x;
  }
  if (yb1 > 0 && estado1 == 1 && contBala2 == 3) {
    yb1 = yb1 - 7;
    delay(5);
    LCD_Sprite(xbala1, yb1, 32, 32, bala, 1, 0, 1, 0);
    if (yb1 <= 0) {
      estado1 = 0;
    }
    if (yb1 <= 30 && xbala1 == 48 ) {
      enemigo8 = 1;
      contBala2 = 4;
      estado1 = 0;
    }
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  if ((digitalRead(PF_0) == 0) && (estado1 == 0)) {
    estado1 = 1;
    yb1 = 150;
    xbala1 = x;
  }
  if (yb1 > 0 && estado1 == 1 && contBala3 == 0) {
    yb1 = yb1 - 7;
    delay(5);
    LCD_Sprite(xbala1, yb1, 32, 32, bala, 1, 0, 1, 0);
    if (yb1 <= 0) {
      estado1 = 0;
    }
    if (yb1 <= 120 && xbala1 == 75 ) {
      enemigo9 = 1;
      contBala3 = 1;
      estado1 = 0;
    }
  }

  if ((digitalRead(PF_0) == 0) && (estado1 == 0)) {
    estado1 = 1;
    yb1 = 150;
    xbala1 = x;
  }
  if (yb1 > 0 && estado1 == 1 && contBala3 == 1) {
    yb1 = yb1 - 7;
    delay(5);
    LCD_Sprite(xbala1, yb1, 32, 32, bala, 1, 0, 1, 0);
    if (yb1 <= 0) {
      estado1 = 0;
    }
    if (yb1 <= 90 && xbala1 == 75 ) {
      enemigo10 = 1;
      contBala3 = 2;
      estado1 = 0;
    }
  }

  if ((digitalRead(PF_0) == 0) && (estado1 == 0)) {
    estado1 = 1;
    yb1 = 150;
    xbala1 = x;
  }
  if (yb1 > 0 && estado1 == 1 && contBala3 == 2) {
    yb1 = yb1 - 7;
    delay(5);
    LCD_Sprite(xbala1, yb1, 32, 32, bala, 1, 0, 1, 0);
    if (yb1 <= 0) {
      estado1 = 0;
    }
    if (yb1 <= 60 && xbala1 == 75 ) {
      enemigo11 = 1;
      contBala3 = 3;
      estado1 = 0;
    }
  }


  if ((digitalRead(PF_0) == 0) && (estado1 == 0)) {
    estado1 = 1;
    yb1 = 150;
    xbala1 = x;
  }
  if (yb1 > 0 && estado1 == 1 && contBala3 == 3) {
    yb1 = yb1 - 7;
    delay(5);
    LCD_Sprite(xbala1, yb1, 32, 32, bala, 1, 0, 1, 0);
    if (yb1 <= 0) {
      estado1 = 0;
    }
    if (yb1 <= 30 && xbala1 == 75 ) {
      enemigo12 = 1;
      contBala3 = 4;
      estado1 = 0;
    }
  }


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  if ((digitalRead(PF_0) == 0) && (estado1 == 0)) {
    estado1 = 1;
    yb1 = 150;
    xbala1 = x;
  }
  if (yb1 > 0 && estado1 == 1 && contBala4 == 0) {
    yb1 = yb1 - 7;
    delay(5);
    LCD_Sprite(xbala1, yb1, 32, 32, bala, 1, 0, 1, 0);
    if (yb1 <= 0) {
      estado1 = 0;
    }
    if (yb1 <= 120 && xbala1 == 105 ) {
      enemigo13 = 1;
      contBala4 = 1;
      estado1 = 0;
    }
  }

  if ((digitalRead(PF_0) == 0) && (estado1 == 0)) {
    estado1 = 1;
    yb1 = 150;
    xbala1 = x;
  }
  if (yb1 > 0 && estado1 == 1 && contBala4 == 1) {
    yb1 = yb1 - 7;
    delay(5);
    LCD_Sprite(xbala1, yb1, 32, 32, bala, 1, 0, 1, 0);
    if (yb1 <= 0) {
      estado1 = 0;
    }
    if (yb1 <= 90 && xbala1 == 105 ) {
      enemigo14 = 1;
      contBala4 = 2;
      estado1 = 0;
    }
  }

  if ((digitalRead(PF_0) == 0) && (estado1 == 0)) {
    estado1 = 1;
    yb1 = 150;
    xbala1 = x;
  }
  if (yb1 > 0 && estado1 == 1 && contBala4 == 2) {
    yb1 = yb1 - 7;
    delay(5);
    LCD_Sprite(xbala1, yb1, 32, 32, bala, 1, 0, 1, 0);
    if (yb1 <= 0) {
      estado1 = 0;
    }
    if (yb1 <= 60 && xbala1 == 105 ) {
      enemigo15 = 1;
      contBala4 = 3;
      estado1 = 0;
    }
  }


  if ((digitalRead(PF_0) == 0) && (estado1 == 0)) {
    estado1 = 1;
    yb1 = 150;
    xbala1 = x;
  }
  if (yb1 > 0 && estado1 == 1 && contBala4 == 3) {
    yb1 = yb1 - 7;
    delay(5);
    LCD_Sprite(xbala1, yb1, 32, 32, bala, 1, 0, 1, 0);
    if (yb1 <= 0) {
      estado1 = 0;
    }
    if (yb1 <= 30 && xbala1 == 105 ) {
      enemigo16 = 1;
      contBala4 = 4;
      estado1 = 0;
    }
  }


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  if ((digitalRead(PF_4) == 0) && (estado2 == 0)) {
    estado2 = 1;
    yb2 = 150;
    xbala2 = x2;
  }
  if (yb2 > 0 && estado2 == 1 && contBBala == 0) {
    yb2 = yb2 - 7;
    delay(5);
    LCD_Sprite(xbala2, yb2, 32, 32, bala, 1, 0, 1, 0);
    if (yb2 <= 0) {
      estado2 = 0;
    }
    if (yb2 <= 120 && xbala2 == 171) {
      enemigo17 = 1;
      contBBala = 1;
      estado2 = 0;
    }
  }

  if ((digitalRead(PF_4) == 0) && (estado2 == 0)) {
    estado2 = 1;
    yb2 = 150;
    xbala2 = x2;
  }
  if (yb2 > 0 && estado2 == 1 && contBBala == 1) {
    yb2 = yb2 - 7;
    delay(5);
    LCD_Sprite(xbala2, yb2, 32, 32, bala, 1, 0, 1, 0);
    if (yb2 <= 0) {
      estado2 = 0;
    }
    if (yb2 <= 90 && xbala2 == 171) {
      enemigo18 = 1;
      contBBala = 2;
      estado2 = 0;
    }
  }

  if ((digitalRead(PF_4) == 0) && (estado2 == 0)) {
    estado2 = 1;
    yb2 = 150;
    xbala2 = x2;
  }
  if (yb2 > 0 && estado2 == 1 && contBBala == 2) {
    yb2 = yb2 - 7;
    delay(5);
    LCD_Sprite(xbala2, yb2, 32, 32, bala, 1, 0, 1, 0);
    if (yb2 <= 0) {
      estado2 = 0;
    }
    if (yb2 <= 60 && xbala2 == 171) {
      enemigo19 = 1;
      contBBala = 3;
      estado2 = 0;
    }
  }

  if ((digitalRead(PF_4) == 0) && (estado2 == 0)) {
    estado2 = 1;
    yb2 = 150;
    xbala2 = x2;
  }
  if (yb2 > 0 && estado2 == 1 && contBBala == 3) {
    yb2 = yb2 - 7;
    delay(5);
    LCD_Sprite(xbala2, yb2, 32, 32, bala, 1, 0, 1, 0);
    if (yb2 <= 0) {
      estado2 = 0;
    }
    if (yb2 <= 30 && xbala2 == 171) {
      enemigo20 = 1;
      contBBala = 4;
      estado2 = 0;
    }
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



  if ((digitalRead(PF_4) == 0) && (estado2 == 0)) {
    estado2 = 1;
    yb2 = 150;
    xbala2 = x2;
  }
  if (yb2 > 0 && estado2 == 1 && contBBala2 == 0) {
    yb2 = yb2 - 7;
    delay(5);
    LCD_Sprite(xbala2, yb2, 32, 32, bala, 1, 0, 1, 0);
    if (yb2 <= 0) {
      estado2 = 0;
    }
    if (yb2 <= 120 && xbala2 == 201) {
      enemigo21 = 1;
      contBBala2 = 1;
      estado2 = 0;
    }
  }

  if ((digitalRead(PF_4) == 0) && (estado2 == 0)) {
    estado2 = 1;
    yb2 = 150;
    xbala2 = x2;
  }
  if (yb2 > 0 && estado2 == 1 && contBBala2 == 1) {
    yb2 = yb2 - 7;
    delay(5);
    LCD_Sprite(xbala2, yb2, 32, 32, bala, 1, 0, 1, 0);
    if (yb2 <= 0) {
      estado2 = 0;
    }
    if (yb2 <= 90 && xbala2 == 201) {
      enemigo22 = 1;
      contBBala2 = 2;
      estado2 = 0;
    }
  }

  if ((digitalRead(PF_4) == 0) && (estado2 == 0)) {
    estado2 = 1;
    yb2 = 150;
    xbala2 = x2;
  }
  if (yb2 > 0 && estado2 == 1 && contBBala2 == 2) {
    yb2 = yb2 - 7;
    delay(5);
    LCD_Sprite(xbala2, yb2, 32, 32, bala, 1, 0, 1, 0);
    if (yb2 <= 0) {
      estado2 = 0;
    }
    if (yb2 <= 60 && xbala2 == 201) {
      enemigo23 = 1;
      contBBala2 = 3;
      estado2 = 0;
    }
  }

  if ((digitalRead(PF_4) == 0) && (estado2 == 0)) {
    estado2 = 1;
    yb2 = 150;
    xbala2 = x2;
  }
  if (yb2 > 0 && estado2 == 1 && contBBala2 == 3) {
    yb2 = yb2 - 7;
    delay(5);
    LCD_Sprite(xbala2, yb2, 32, 32, bala, 1, 0, 1, 0);
    if (yb2 <= 0) {
      estado2 = 0;
    }
    if (yb2 <= 30 && xbala2 == 201) {
      enemigo24 = 1;
      contBBala2 = 4;
      estado2 = 0;
    }
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




  if ((digitalRead(PF_4) == 0) && (estado2 == 0)) {
    estado2 = 1;
    yb2 = 150;
    xbala2 = x2;
  }
  if (yb2 > 0 && estado2 == 1 && contBBala3 == 0) {
    yb2 = yb2 - 7;
    delay(5);
    LCD_Sprite(xbala2, yb2, 32, 32, bala, 1, 0, 1, 0);
    if (yb2 <= 0) {
      estado2 = 0;
    }
    if (yb2 <= 120 && xbala2 == 231) {
      enemigo25 = 1;
      contBBala3 = 1;
      estado2 = 0;
    }
  }

  if ((digitalRead(PF_4) == 0) && (estado2 == 0)) {
    estado2 = 1;
    yb2 = 150;
    xbala2 = x2;
  }
  if (yb2 > 0 && estado2 == 1 && contBBala3 == 1) {
    yb2 = yb2 - 7;
    delay(5);
    LCD_Sprite(xbala2, yb2, 32, 32, bala, 1, 0, 1, 0);
    if (yb2 <= 0) {
      estado2 = 0;
    }
    if (yb2 <= 90 && xbala2 == 231) {
      enemigo26 = 1;
      contBBala3 = 2;
      estado2 = 0;
    }
  }

  if ((digitalRead(PF_4) == 0) && (estado2 == 0)) {
    estado2 = 1;
    yb2 = 150;
    xbala2 = x2;
  }
  if (yb2 > 0 && estado2 == 1 && contBBala3 == 2) {
    yb2 = yb2 - 7;
    delay(5);
    LCD_Sprite(xbala2, yb2, 32, 32, bala, 1, 0, 1, 0);
    if (yb2 <= 0) {
      estado2 = 0;
    }
    if (yb2 <= 60 && xbala2 == 231) {
      enemigo27 = 1;
      contBBala3 = 3;
      estado2 = 0;
    }
  }

  if ((digitalRead(PF_4) == 0) && (estado2 == 0)) {
    estado2 = 1;
    yb2 = 150;
    xbala2 = x2;
  }
  if (yb2 > 0 && estado2 == 1 && contBBala3 == 3) {
    yb2 = yb2 - 7;
    delay(5);
    LCD_Sprite(xbala2, yb2, 32, 32, bala, 1, 0, 1, 0);
    if (yb2 <= 0) {
      estado2 = 0;
    }
    if (yb2 <= 30 && xbala2 == 231) {
      enemigo28 = 1;
      contBBala3 = 4;
      estado2 = 0;
    }
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  if ((digitalRead(PF_4) == 0) && (estado2 == 0)) {
    estado2 = 1;
    yb2 = 150;
    xbala2 = x2;
  }
  if (yb2 > 0 && estado2 == 1 && contBBala4 == 0) {
    yb2 = yb2 - 7;
    delay(5);
    LCD_Sprite(xbala2, yb2, 32, 32, bala, 1, 0, 1, 0);
    if (yb2 <= 0) {
      estado2 = 0;
    }
    if (yb2 <= 120 && xbala2 == 261) {
      enemigo29 = 1;
      contBBala4 = 1;
      estado2 = 0;
    }
  }

  if ((digitalRead(PF_4) == 0) && (estado2 == 0)) {
    estado2 = 1;
    yb2 = 150;
    xbala2 = x2;
  }
  if (yb2 > 0 && estado2 == 1 && contBBala4 == 1) {
    yb2 = yb2 - 7;
    delay(5);
    LCD_Sprite(xbala2, yb2, 32, 32, bala, 1, 0, 1, 0);
    if (yb2 <= 0) {
      estado2 = 0;
    }
    if (yb2 <= 90 && xbala2 == 261) {
      enemigo30 = 1;
      contBBala4 = 2;
      estado2 = 0;
    }
  }

  if ((digitalRead(PF_4) == 0) && (estado2 == 0)) {
    estado2 = 1;
    yb2 = 150;
    xbala2 = x2;
  }
  if (yb2 > 0 && estado2 == 1 && contBBala4 == 2) {
    yb2 = yb2 - 7;
    delay(5);
    LCD_Sprite(xbala2, yb2, 32, 32, bala, 1, 0, 1, 0);
    if (yb2 <= 0) {
      estado2 = 0;
    }
    if (yb2 <= 60 && xbala2 == 261) {
      enemigo31 = 1;
      contBBala4 = 3;
      estado2 = 0;
    }
  }

  if ((digitalRead(PF_4) == 0) && (estado2 == 0)) {
    estado2 = 1;
    yb2 = 150;
    xbala2 = x2;
  }
  if (yb2 > 0 && estado2 == 1 && contBBala4 == 3) {
    yb2 = yb2 - 7;
    delay(5);
    LCD_Sprite(xbala2, yb2, 32, 32, bala, 1, 0, 1, 0);
    if (yb2 <= 0) {
      estado2 = 0;
    }
    if (yb2 <= 30 && xbala2 == 261) {
      enemigo32 = 1;
      contBBala4 = 4;
      estado2 = 0;
    }
  }





















}

//***************************************************************************************************************************************
// Función para inicializar LCD
//***************************************************************************************************************************************
void LCD_Init(void) {
  pinMode(LCD_RST, OUTPUT);
  pinMode(LCD_CS, OUTPUT);
  pinMode(LCD_RS, OUTPUT);
  pinMode(LCD_WR, OUTPUT);
  pinMode(LCD_RD, OUTPUT);
  for (uint8_t i = 0; i < 8; i++) {
    pinMode(DPINS[i], OUTPUT);
  }
  //****************************************
  // Secuencia de Inicialización
  //****************************************
  digitalWrite(LCD_CS, HIGH);
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_WR, HIGH);
  digitalWrite(LCD_RD, HIGH);
  digitalWrite(LCD_RST, HIGH);
  delay(5);
  digitalWrite(LCD_RST, LOW);
  delay(20);
  digitalWrite(LCD_RST, HIGH);
  delay(150);
  digitalWrite(LCD_CS, LOW);
  //****************************************
  LCD_CMD(0xE9);  // SETPANELRELATED
  LCD_DATA(0x20);
  //****************************************
  LCD_CMD(0x11); // Exit Sleep SLEEP OUT (SLPOUT)
  delay(100);
  //****************************************
  LCD_CMD(0xD1);    // (SETVCOM)
  LCD_DATA(0x00);
  LCD_DATA(0x71);
  LCD_DATA(0x19);
  //****************************************
  LCD_CMD(0xD0);   // (SETPOWER)
  LCD_DATA(0x07);
  LCD_DATA(0x01);
  LCD_DATA(0x08);
  //****************************************
  LCD_CMD(0x36);  // (MEMORYACCESS)
  LCD_DATA(0x40 | 0x80 | 0x20 | 0x08); // LCD_DATA(0x19);
  //****************************************
  LCD_CMD(0x3A); // Set_pixel_format (PIXELFORMAT)
  LCD_DATA(0x05); // color setings, 05h - 16bit pixel, 11h - 3bit pixel
  //****************************************
  LCD_CMD(0xC1);    // (POWERCONTROL2)
  LCD_DATA(0x10);
  LCD_DATA(0x10);
  LCD_DATA(0x02);
  LCD_DATA(0x02);
  //****************************************
  LCD_CMD(0xC0); // Set Default Gamma (POWERCONTROL1)
  LCD_DATA(0x00);
  LCD_DATA(0x35);
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0x02);
  //****************************************
  LCD_CMD(0xC5); // Set Frame Rate (VCOMCONTROL1)
  LCD_DATA(0x04); // 72Hz
  //****************************************
  LCD_CMD(0xD2); // Power Settings  (SETPWRNORMAL)
  LCD_DATA(0x01);
  LCD_DATA(0x44);
  //****************************************
  LCD_CMD(0xC8); //Set Gamma  (GAMMASET)
  LCD_DATA(0x04);
  LCD_DATA(0x67);
  LCD_DATA(0x35);
  LCD_DATA(0x04);
  LCD_DATA(0x08);
  LCD_DATA(0x06);
  LCD_DATA(0x24);
  LCD_DATA(0x01);
  LCD_DATA(0x37);
  LCD_DATA(0x40);
  LCD_DATA(0x03);
  LCD_DATA(0x10);
  LCD_DATA(0x08);
  LCD_DATA(0x80);
  LCD_DATA(0x00);
  //****************************************
  LCD_CMD(0x2A); // Set_column_address 320px (CASET)
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0x3F);
  //****************************************
  LCD_CMD(0x2B); // Set_page_address 480px (PASET)
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0xE0);
  //  LCD_DATA(0x8F);
  LCD_CMD(0x29); //display on
  LCD_CMD(0x2C); //display on

  LCD_CMD(ILI9341_INVOFF); //Invert Off
  delay(120);
  LCD_CMD(ILI9341_SLPOUT);    //Exit Sleep
  delay(120);
  LCD_CMD(ILI9341_DISPON);    //Display on
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para enviar comandos a la LCD - parámetro (comando)
//***************************************************************************************************************************************
void LCD_CMD(uint8_t cmd) {
  digitalWrite(LCD_RS, LOW);
  digitalWrite(LCD_WR, LOW);
  GPIO_PORTB_DATA_R = cmd;
  digitalWrite(LCD_WR, HIGH);
}
//***************************************************************************************************************************************
// Función para enviar datos a la LCD - parámetro (dato)
//***************************************************************************************************************************************
void LCD_DATA(uint8_t data) {
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_WR, LOW);
  GPIO_PORTB_DATA_R = data;
  digitalWrite(LCD_WR, HIGH);
}
//***************************************************************************************************************************************
// Función para definir rango de direcciones de memoria con las cuales se trabajara (se define una ventana)
//***************************************************************************************************************************************
void SetWindows(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
  LCD_CMD(0x2a); // Set_column_address 4 parameters
  LCD_DATA(x1 >> 8);
  LCD_DATA(x1);
  LCD_DATA(x2 >> 8);
  LCD_DATA(x2);
  LCD_CMD(0x2b); // Set_page_address 4 parameters
  LCD_DATA(y1 >> 8);
  LCD_DATA(y1);
  LCD_DATA(y2 >> 8);
  LCD_DATA(y2);
  LCD_CMD(0x2c); // Write_memory_start
}
//***************************************************************************************************************************************
// Función para borrar la pantalla - parámetros (color)
//***************************************************************************************************************************************
void LCD_Clear(unsigned int c) {
  unsigned int x, y;
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  SetWindows(0, 0, 319, 239); // 479, 319);
  for (x = 0; x < 320; x++)
    for (y = 0; y < 240; y++) {
      LCD_DATA(c >> 8);
      LCD_DATA(c);
    }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una línea horizontal - parámetros ( coordenada x, cordenada y, longitud, color)
//***************************************************************************************************************************************
void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c) {
  unsigned int i, j;
  LCD_CMD(0x02c); //write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  l = l + x;
  SetWindows(x, y, l, y);
  j = l;// * 2;
  for (i = 0; i < l; i++) {
    LCD_DATA(c >> 8);
    LCD_DATA(c);
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una línea vertical - parámetros ( coordenada x, cordenada y, longitud, color)
//***************************************************************************************************************************************
void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c) {
  unsigned int i, j;
  LCD_CMD(0x02c); //write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  l = l + y;
  SetWindows(x, y, x, l);
  j = l; //* 2;
  for (i = 1; i <= j; i++) {
    LCD_DATA(c >> 8);
    LCD_DATA(c);
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar un rectángulo - parámetros ( coordenada x, cordenada y, ancho, alto, color)
//***************************************************************************************************************************************
void Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  H_line(x  , y  , w, c);
  H_line(x  , y + h, w, c);
  V_line(x  , y  , h, c);
  V_line(x + w, y  , h, c);
}
//***************************************************************************************************************************************
// Función para dibujar un rectángulo relleno - parámetros ( coordenada x, cordenada y, ancho, alto, color)
//***************************************************************************************************************************************
/*void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  unsigned int i;
  for (i = 0; i < h; i++) {
    H_line(x  , y  , w, c);
    H_line(x  , y+i, w, c);
  }
  }
*/

void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);

  unsigned int x2, y2;
  x2 = x + w;
  y2 = y + h;
  SetWindows(x, y, x2 - 1, y2 - 1);
  unsigned int k = w * h * 2 - 1;
  unsigned int i, j;
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      LCD_DATA(c >> 8);
      LCD_DATA(c);

      //LCD_DATA(bitmap[k]);
      k = k - 2;
    }
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar texto - parámetros ( texto, coordenada x, cordenada y, color, background)
//***************************************************************************************************************************************
void LCD_Print(String text, int x, int y, int fontSize, int color, int background) {
  int fontXSize ;
  int fontYSize ;

  if (fontSize == 1) {
    fontXSize = fontXSizeSmal ;
    fontYSize = fontYSizeSmal ;
  }
  if (fontSize == 2) {
    fontXSize = fontXSizeBig ;
    fontYSize = fontYSizeBig ;
  }

  char charInput ;
  int cLength = text.length();
  Serial.println(cLength, DEC);
  int charDec ;
  int c ;
  int charHex ;
  char char_array[cLength + 1];
  text.toCharArray(char_array, cLength + 1) ;
  for (int i = 0; i < cLength ; i++) {
    charInput = char_array[i];
    Serial.println(char_array[i]);
    charDec = int(charInput);
    digitalWrite(LCD_CS, LOW);
    SetWindows(x + (i * fontXSize), y, x + (i * fontXSize) + fontXSize - 1, y + fontYSize );
    long charHex1 ;
    for ( int n = 0 ; n < fontYSize ; n++ ) {
      if (fontSize == 1) {
        charHex1 = pgm_read_word_near(smallFont + ((charDec - 32) * fontYSize) + n);
      }
      if (fontSize == 2) {
        charHex1 = pgm_read_word_near(bigFont + ((charDec - 32) * fontYSize) + n);
      }
      for (int t = 1; t < fontXSize + 1 ; t++) {
        if (( charHex1 & (1 << (fontXSize - t))) > 0 ) {
          c = color ;
        } else {
          c = background ;
        }
        LCD_DATA(c >> 8);
        LCD_DATA(c);
      }
    }
    digitalWrite(LCD_CS, HIGH);
  }
}
//***************************************************************************************************************************************
// Función para dibujar una imagen a partir de un arreglo de colores (Bitmap) Formato (Color 16bit R 5bits G 6bits B 5bits)
//***************************************************************************************************************************************
void LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]) {
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);

  unsigned int x2, y2;
  x2 = x + width;
  y2 = y + height;
  SetWindows(x, y, x2 - 1, y2 - 1);
  unsigned int k = 0;
  unsigned int i, j;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      LCD_DATA(bitmap[k]);
      LCD_DATA(bitmap[k + 1]);
      //LCD_DATA(bitmap[k]);
      k = k + 2;
    }
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una imagen sprite - los parámetros columns = número de imagenes en el sprite, index = cual desplegar, flip = darle vuelta
//***************************************************************************************************************************************
void LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[], int columns, int index, char flip, char offset) {
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);

  unsigned int x2, y2;
  x2 =   x + width;
  y2 =    y + height;
  SetWindows(x, y, x2 - 1, y2 - 1);
  int k = 0;
  int ancho = ((width * columns));
  if (flip) {
    for (int j = 0; j < height; j++) {
      k = (j * (ancho) + index * width - 1 - offset) * 2;
      k = k + width * 2;
      for (int i = 0; i < width; i++) {
        LCD_DATA(bitmap[k]);
        LCD_DATA(bitmap[k + 1]);
        k = k - 2;
      }
    }
  } else {
    for (int j = 0; j < height; j++) {
      k = (j * (ancho) + index * width + 1 + offset) * 2;
      for (int i = 0; i < width; i++) {
        LCD_DATA(bitmap[k]);
        LCD_DATA(bitmap[k + 1]);
        k = k + 2;
      }
    }


  }
  digitalWrite(LCD_CS, HIGH);
}

void midi() {

  tone(tonePin, 391, 351.5625);
  if (digitalRead(PF_0) == 0) {
    start = 1;
    return;
  }
  delay(390.625);
  tone(tonePin, 440, 234.375);
  if (digitalRead(PF_0) == 0) {
    start = 1;
    return;
  };
  delay(260.416666667);
  tone(tonePin, 523, 117.1875);
  if (digitalRead(PF_0) == 0) {
    start = 1;
    return;
  }
  delay(130.208333333);
  tone(tonePin, 493, 351.5625);
  if (digitalRead(PF_0) == 0) {
    start = 1;
    return;
  }
  delay(390.625);
  tone(tonePin, 391, 351.5625);
  if (digitalRead(PF_0) == 0) {
    start = 1;
    return;
  }
  delay(390.625);
  tone(tonePin, 523, 351.5625);
  if (digitalRead(PF_0) == 0) {
    start = 1;
    return;
  }
  delay(390.625);
  tone(tonePin, 587, 234.375);
  if (digitalRead(PF_0) == 0) {
    start = 1;
    return;
  }
  delay(260.416666667);
  tone(tonePin, 698, 117.1875);
  if (digitalRead(PF_0) == 0) {
    start = 1;
    return;
  }
  delay(130.208333333);
  tone(tonePin, 659, 351.5625);
  if (digitalRead(PF_0) == 0) {
    start = 1;
    return;
  }
  delay(390.625);
  tone(tonePin, 587, 351.5625);
  if (digitalRead(PF_0) == 0) {
    start = 1;
    return;
  }
  delay(390.625);
  tone(tonePin, 622, 351.5625);
  if (digitalRead(PF_0) == 0) {
    start = 1;
    return;
  }
  delay(390.625);
  tone(tonePin, 587, 234.375);
  if (digitalRead(PF_0) == 0) {
    start = 1;
    return;
  }
  delay(260.416666667);
  tone(tonePin, 523, 117.1875);
  if (digitalRead(PF_0) == 0) {
    start = 1;
    return;
  }
  delay(130.208333333);
  tone(tonePin, 466, 351.5625);
  if (digitalRead(PF_0) == 0) {
    start = 1;
    return;
  }
  delay(390.625);
  tone(tonePin, 622, 351.5625);
  if (digitalRead(PF_0) == 0) {
    start = 1;
    return;
  }
  delay(390.625);
  tone(tonePin, 932, 351.5625);
  if (digitalRead(PF_0) == 0) {
    start = 1;
    return;
  }
  delay(390.625);
  tone(tonePin, 783, 234.375);
  if (digitalRead(PF_0) == 0) {
    start = 1;
    return;
  }
  delay(260.416666667);
  tone(tonePin, 622, 117.1875);
  if (digitalRead(PF_0) == 0) {
    start = 1;
    return;
  }
  delay(130.208333333);
  tone(tonePin, 587, 351.5625);
  if (digitalRead(PF_0) == 0) {
    start = 1;
    return;
  }
  delay(390.625);
  tone(tonePin, 783, 234.375);
  if (digitalRead(PF_0) == 0) {
    start = 1;
    return;
  }
  delay(260.416666667);
  tone(tonePin, 659, 468.75);
  if (digitalRead(PF_0) == 0) {
    start = 1;
    return;
  }
  delay(520.833333333);

}
