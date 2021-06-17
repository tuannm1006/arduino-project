#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>

int Rx = 3, Tx = 1;
SoftwareSerial s(Rx, Tx);
WebSocketsClient webSocket;

const char* ssid = "*********"; // change with your wifi network name
const char* password = "*********"; // change with your wifi network password
const char* ip_host = "*********"; // change with your computer ip address
const uint16_t port = 3000;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      s.printf("[WSc] Disconnected!\n");
      digitalWrite(LED_BUILTIN, HIGH);
      s.flush();
      break;
    case WStype_CONNECTED:
      s.printf("[WSc] Connected to url: %s\n", payload);
      digitalWrite(LED_BUILTIN, LOW);
      s.flush();
      break;
    case WStype_TEXT:
      {
        char *tmp = (char*)payload;
        s.write(tmp);
      }
      break;
  }
}

void setup() {
  s.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  s.printf("ESP8266 Websocket Client\n");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    s.printf(".");
  }
  
  s.flush();
  webSocket.begin(ip_host, port);
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();
}
