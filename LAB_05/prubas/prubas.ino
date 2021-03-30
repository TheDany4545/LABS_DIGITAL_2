
bool state;
bool state2;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PUSH1,INPUT_PULLUP);
  pinMode(PUSH2,INPUT_PULLUP);
  pinMode(BLUE_LED,OUTPUT);
  pinMode(RED_LED,OUTPUT);
  

}

void loop() {
  state = digitalRead(PUSH1);
  state2 = digitalRead(PUSH2);
  char get = Serial.read();
  Serial.println(get);
  int n = sizeof(get);
  Serial.println(n);

  if(n == 4){
     char get = Serial.read();
     int n = sizeof(n);
     Serial.println(n);
     digitalWrite(BLUE_LED,HIGH);
     digitalWrite(RED_LED,LOW);
     
     
  }
  if(state==LOW){
    Serial.println("No hay valor");
    digitalWrite(RED_LED,HIGH);
    digitalWrite(BLUE_LED,LOW);
  }
  if(state2 == LOW){
    Serial.write("FF");
  }
  
}
