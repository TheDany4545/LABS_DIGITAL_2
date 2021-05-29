/*************************************************************************************************
  ESP32 Web Server
  Ejemplo de creación de Web server
  Basándose en los ejemplos de:
  https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/
  https://electropeak.com/learn
**************************************************************************************************/
//************************************************************************************************
// Librerías
//************************************************************************************************
#include <WiFi.h>
#include <WebServer.h>
//************************************************************************************************
// Variables globales
//************************************************************************************************
// SSID & Password
const char* ssid = "Joie de vivre";  // Enter your SSID here
const char* password = "apex014578";  //Enter your Password here

WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)


uint8_t LED1pin = 2;
bool LED1status = LOW;
bool LED2status = LOW;
bool LED3status = LOW;
bool LED4status = LOW;
char state;
char state2;
int parqueos = 0;

//************************************************************************************************
// Configuración
//************************************************************************************************
void setup() {
  Serial.begin(115200);

 // Serial2.begin(115200);//, SERIAL_8N1, 16, 17);

  Serial.println("Try Connecting to ");
  Serial.println(ssid);

  pinMode(LED1pin, OUTPUT);

  // Connect to your wi-fi modem
  WiFi.begin(ssid, password);

  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial

  server.on("/", handle_OnConnect); // Directamente desde e.g. 192.168.0.8
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);
  server.on("/led2on", handle_led2on);
  server.on("/led2off", handle_led2off);
  server.on("/led3on", handle_led3on);
  server.on("/led3off", handle_led3off);
  server.on("/led4on", handle_led4on);
  server.on("/led4off", handle_led4off);

  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
  delay(100);
}
//************************************************************************************************
// loop principal
//************************************************************************************************
void loop() {
  //state = Serial.read();
  server.handleClient();
  if (LED1status)
  {
    digitalWrite(LED1pin, HIGH);
  }
  else
  {
    digitalWrite(LED1pin, LOW);
  }

}
//************************************************************************************************
// Handler de Inicio página
//************************************************************************************************
void handle_OnConnect() {
  LED1status = LOW;
  Serial.println("GPIO2 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status));

  LED2status = LOW;
  Serial.println("GPIO3 Status: OFF");
  server.send(200, "text/html", SendHTML(LED2status));

  LED3status = LOW;
  Serial.println("GPIO4 Status: OFF");
  server.send(200, "text/html", SendHTML(LED3status));

  LED4status = LOW;
  Serial.println("GPIO5 Status: OFF");
  server.send(200, "text/html", SendHTML(LED4status));
}
//************************************************************************************************
// Handler de led1on
//************************************************************************************************
void handle_led1on() {
  LED1status = HIGH;
  Serial.println("GPIO2 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status));

  LED2status = HIGH;
  Serial.println("GPIO3 Status: ON");
  server.send(200, "text/html", SendHTML(LED2status));

  LED3status = HIGH;
  Serial.println("GPIO4 Status: ON");
  server.send(200, "text/html", SendHTML(LED3status));

  LED4status = HIGH;
  Serial.println("GPIO5 Status: ON");
  server.send(200, "text/html", SendHTML(LED4status));
}

void handle_led2on() {
  LED2status = HIGH;
  Serial.println("GPIO3 Status: ON");
  server.send(200, "text/html", SendHTML(LED2status));

}
void handle_led3on() {
  LED3status = HIGH;
  Serial.println("GPIO4 Status: ON");
  server.send(200, "text/html", SendHTML(LED3status));
}

void handle_led4on() {
  LED3status = HIGH;
  Serial.println("GPIO5 Status: ON");
  server.send(200, "text/html", SendHTML(LED3status));
}
//************************************************************************************************
// Handler de led1off
//************************************************************************************************
void handle_led1off() {
  LED1status = LOW;
  Serial.println("GPIO2 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status));

  LED2status = LOW;
  Serial.println("GPIO3 Status: OFF");
  server.send(200, "text/html", SendHTML(LED2status));

  LED3status = LOW;
  Serial.println("GPIO4 Status: OFF");
  server.send(200, "text/html", SendHTML(LED3status));

  LED4status = LOW;
  Serial.println("GPIO5 Status: OFF");
  server.send(200, "text/html", SendHTML(LED4status));
}
void handle_led2off() {
  LED2status = LOW;
  Serial.println("GPIO3 Status: OFF");
  server.send(200, "text/html", SendHTML(LED2status));

}
void handle_led3off() {
  LED3status = LOW;
  Serial.println("GPIO4 Status: OFF");
  server.send(200, "text/html", SendHTML(LED3status));
}
void handle_led4off() {
  LED3status = LOW;
  Serial.println("GPIO5 Status: OFF");
  server.send(200, "text/html", SendHTML(LED3status));
}
//************************************************************************************************
// Procesador de HTML
//************************************************************************************************
String SendHTML(uint8_t led1stat) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>LED Control</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 20px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";

  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>Proyecto # 4 Parqueos &#128664</h1>\n";
  ptr += "<h3>Erick Aquino 17319</h3>\n";

  //BOTON1
  ptr += "<button>";
  if (led1stat)
  {
    ptr += "<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/led1off\">VACANT</a>\n";
  }
  else
  {
    ptr += "<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">PARKED</a>\n";
  }
  //ptr += "<script>function timedRefresh(a){setTimeout(\"location.reload(true);\",a)}window.onload=timedRefresh(1000);</script>\n";
  ptr += "</button>";

  //BOTON2
  ptr += "<button>";

  if (led1stat)
  {
    ptr += "<p>LED2 Status: ON</p><a class=\"button button-off\" href=\"/led2off\">VACANT</a>\n";
  }
  else
  {
    ptr += "<p>LED2 Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">PARKED</a>\n";
  }
  //ptr += "<script>function timedRefresh(a){setTimeout(\"location.reload(true);\",a)}window.onload=timedRefresh(1000);</script>\n";
  ptr += "</button>";



  //BOTON3
  ptr += "<button>";

  if (led1stat)
  {
    ptr += "<p>LED3 Status: ON</p><a class=\"button button-of\" href=\"/led3off\">VACANT</a>\n";
  }
  else
  {
    ptr += "<p>LED3 Status: OFF</p><a class=\"button button-on\" href=\"/led3on\">PARKED</a>\n";
  }
  //ptr += "<script>function timedRefresh(a){setTimeout(\"location.reload(true);\",a)}window.onload=timedRefresh(1000);</script>\n";
  ptr += "</button>";


  //BOTON4
  ptr += "<button>";

  if (led1stat)
  {
    ptr += "<p>LED4 Status: ON</p><a class=\"button button-off\" href=\"/led4off\">VACANT4</a>\n";
  }
  else
  {
    ptr += "<p>LED4 Status: OFF</p><a class=\"button button-on\" href=\"/led4on\">PARKED4</a>\n";
  }
  //ptr += "<script>function timedRefresh(a){setTimeout(\"location.reload(true);\",a)}window.onload=timedRefresh(1000);</script>\n";
  ptr += "</button>";


  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
//************************************************************************************************
// Handler de not found
//************************************************************************************************
void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}
