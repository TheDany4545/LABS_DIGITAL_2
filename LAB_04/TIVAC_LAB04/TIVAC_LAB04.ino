//Erick Daniel Aquino Paz
//Carnet 17319
// Lab#04 Digital 2

#define RED RED_LED
#define AZUL BLUE_LED
#define VERDE GREEN_LED

 
//boton 1 = PUSH1
//boton 2 = PUSH2
const int PUSH3 = 10; //pin23
bool state = 0;
int estado1 = 0;
int estado2 = 0;
int cont1 = 0;
int cont2 = 0;
int ant1 = 0;
int ant2 = 0;
byte PORTD_E[8] = {36,37,25,26,33,32,34,35};
byte PORTB[8] = {3,4,19,38,7,2,14,15};
void setup() {
  // put your setup code here, to run once:
  pinMode(RED,OUTPUT);
  pinMode(AZUL,OUTPUT);
  pinMode(VERDE,OUTPUT);
  pinMode(PUSH3,INPUT_PULLUP);
  pinMode(PUSH1,INPUT_PULLUP);
  pinMode(PUSH2,INPUT_PULLUP);

  //inicializar  
  for(int i=0;i < (sizeof(PORTB)/sizeof(byte));i++)
  {    
    pinMode(PORTB[i],OUTPUT);
    digitalWrite(PORTB[i],LOW);    
  }
    for(int i=0;i < (sizeof(PORTD_E)/sizeof(byte));i++)
  {    
    pinMode(PORTD_E[i],OUTPUT);
    digitalWrite(PORTD_E[i],LOW);    
  }
  


  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  state = digitalRead(PUSH3);
  if(state == 0){
    semaforo();
  }
  if(state == 1){
    semaforo_off();
  }

  //antirrebote2
  estado2 = digitalRead(PUSH2);
  if(estado2 == 0){
    ant2 = 1;
  }
  if(estado2 == 1 && ant2 == 1){
    ant2 = 0;
    cont2++;
    Serial.print("Jugador 2 -> ");
    Serial.println(cont2);
    byte number = cont2;
    binario2();
  }
  if(cont2==255){
    cont2=0;
    ganador2();   
  }
    //antirrebote
  estado1 = digitalRead(PUSH1);
  if(estado1 == 0){
    ant1 = 1;
  }
  if(estado1 == 1 && ant1 == 1){
    ant1 = 0;
    cont1++;
    Serial.print("Jugador 1 -> ");
    Serial.println(cont1);
    byte number = cont1;
    binario();
  }
  if(cont1==255){
    cont1=0;
    ganador1();   
  }
  
}

//funciones
void semaforo(void){
      //ROJO 
  digitalWrite(VERDE,LOW);
  digitalWrite(RED,HIGH);
  delay(1000);
  //AMARILLO
  digitalWrite(VERDE,HIGH);
  digitalWrite(RED,HIGH);
  delay(750);
  //VERDE
  digitalWrite(RED,LOW);
  digitalWrite(VERDE,HIGH);
  delay(750);  
}
void semaforo_off(void){
    digitalWrite(RED,LOW);
    digitalWrite(VERDE,LOW);
    digitalWrite(AZUL,LOW);
}
void binario(void){
  //byte binaryNumbers[8] = {128,64,32,16,8,4,2,1};
  //cual led encender
  byte a=cont1%2;     
  byte b=cont1/2 %2;     
  byte c=cont1/4 %2;       
  byte d=cont1/8 %2;
  byte e=cont1/16 %2;
  byte f=cont1/32 %2;
  byte g=cont1/64 %2;
  byte h=cont1/128 %2;

  digitalWrite(3,a);
  digitalWrite(4,b);
  digitalWrite(19,c);
  digitalWrite(38,d);
  digitalWrite(7,e);
  digitalWrite(2,f);
  digitalWrite(14,g);
  digitalWrite(15,h);
  /*
  byte decimal = number;
  int result = decimal - binaryNumbers[cont1];
  byte i =0;
  digitalWrite(PORTB[cont1],HIGH);
  i++;
  */
}
void binario2(void){
  //byte binaryNumbers[8] = {128,64,32,16,8,4,2,1};
  //cual led encender
  byte aa=cont2%2;     
  byte bb=cont2/2 %2;     
  byte cc=cont2/4 %2;       
  byte dd=cont2/8 %2;
  byte ee=cont2/16 %2;
  byte ff=cont2/32 %2;
  byte gg=cont2/64 %2;
  byte hh=cont2/128 %2;
//byte PORTD_E[8] = {23,24,25,26,33,32,34,35};
  digitalWrite(36,aa);
  digitalWrite(37,bb);
  digitalWrite(25,cc);
  digitalWrite(26,dd);
  digitalWrite(33,ee);
  digitalWrite(32,ff);
  digitalWrite(34,gg);
  digitalWrite(35,hh);

}
void ganador1(){
  //led morado
    digitalWrite(AZUL,HIGH);
    digitalWrite(RED,HIGH);
    delay(1000);
    digitalWrite(AZUL,LOW);
    digitalWrite(RED,LOW);
    delay(1000);
    digitalWrite(AZUL,HIGH);
    digitalWrite(RED,HIGH);
    delay(1000);
    digitalWrite(AZUL,LOW);
    digitalWrite(RED,LOW);
    delay(1000);
    digitalWrite(AZUL,HIGH);
    digitalWrite(RED,HIGH);
    delay(1000);
    digitalWrite(AZUL,LOW);
    digitalWrite(RED,LOW);
    delay(1000);
    digitalWrite(AZUL,HIGH);
    digitalWrite(RED,HIGH);
    delay(1000);
    digitalWrite(AZUL,LOW);
    digitalWrite(RED,LOW);
}
void ganador2(){
  //led CIAN
    digitalWrite(AZUL,HIGH);
    digitalWrite(VERDE,HIGH);
    delay(1000);
    digitalWrite(AZUL,LOW);
    digitalWrite(VERDE,LOW);
    delay(1000);
    digitalWrite(AZUL,HIGH);
    digitalWrite(VERDE,HIGH);
    delay(1000);
    digitalWrite(AZUL,LOW);
    digitalWrite(VERDE,LOW);
    delay(1000);
    digitalWrite(AZUL,HIGH);
    digitalWrite(VERDE,HIGH);
    delay(1000);
    digitalWrite(AZUL,LOW);
    digitalWrite(VERDE,LOW);
    delay(1000);
    digitalWrite(AZUL,HIGH);
    digitalWrite(VERDE,HIGH);
    delay(1000);
    digitalWrite(AZUL,LOW);
    digitalWrite(VERDE,LOW);
}
