

/************************** Configuration ***********************************/
#include "config.h"
#include "driver/uart.h"
/************************ Example Starts Here *******************************/

// this int will hold the current count for our sketch
int count = 0;

int temperatura = 0;
int entrada = 0;

//HardwareSerial Serial2(2);

// set up the 'counter' feed
//AdafruitIO_Feed *counter = io.feed("counter");
AdafruitIO_Feed *tempfeed = io.feed("example");

void setup() {

  // start the serial connection
  Serial.begin(115200);
  Serial2.begin(115200,SERIAL_8N1,16,17);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");//funciona como .... de espera
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  //temperatura = random(0,50);
  
  // save count to the 'counter' feed on Adafruit IO
  /*
 if(Serial2.available()){
    entrada = char(Serial2.read());
    Serial.print("sending -> ");
    Serial.println(entrada);
    //Serial.print(entrada);
  }
  */
    
  Serial.print("Recibo");
  Serial.println(Serial.read());
  entrada = char(Serial.read());

    
  //entrada = char(Serial2.read());
  //Serial.print("sending -> ");
  //Serial.println(entrada);
  tempfeed->save(entrada);

  // increment the count by 1
  //count++;

  // Adafruit IO is rate limited for publishing, so a delay is required in
  // between feed->save events. In this example, we will wait three seconds
  // (1000 milliseconds == 1 second) during each loop.
  delay(3000);

}
