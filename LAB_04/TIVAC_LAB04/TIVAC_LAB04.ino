//Erick Daniel Aquino Paz
//Carnet 17319
// Lab#04 Digital 2

#define RED RED_LED
#define AZUL BLUE_LED
#define VERDE GREEN_LED
//#define PUSH3 PD_0
 
//boton 1 = PUSH1
//boton 2 = PUSH2
const int PUSH3 = 23; //pin2
int estado = 0;
int PORTB[] = {3,4,19,38,7,2,14,15};
void setup() {
  // put your setup code here, to run once:
  pinMode(RED,OUTPUT);
  pinMode(AZUL,OUTPUT);
  pinMode(VERDE,OUTPUT);
  pinMode(PUSH3,INPUT_PULLUP);  
}

void loop() {
  // put your main code here, to run repeatedly:
  estado = digitalRead(PUSH3);
  if(estado == 0){
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
  else{
    digitalWrite(RED,LOW);
    digitalWrite(VERDE,LOW);
    digitalWrite(AZUL,LOW);
    
  }
}
