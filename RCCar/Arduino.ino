#include <SoftwareSerial.h>
#include <AFMotor.h>

#define F "forward"
#define L "left"
#define R "right"
#define B "backward"
#define S "stop"

AF_DCMotor motor1(3);
AF_DCMotor motor2(4);
String data; // storage data received from ESP8266
int t = 200; // delay time 
int Rx = 9, Tx = 10;

SoftwareSerial mySerial(Rx, Tx);

void setup() {
  mySerial.begin(9600);
  motor1.setSpeed(255);
  motor2.setSpeed(255);
}

/*
 * Descrip: execute function in limit time
 * 
 * param delayTime  execution time
 * param func       function is executed
 */
void Delay(int delayTime, void (func)())
{
    unsigned long endTime = millis() + delayTime;
    while(millis() < endTime)
    {
      func();
      while(millis() < endTime){};
    }
}

/*
 * Descrip: make car forward
 */
void goAhead() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}

/*
 * Descrip: make car turn left
 */
void turnLeft() {
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
}

/*
 * Descrip: make car turn right
 */
void turnRight() {
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
}

/*
 * Descrip: make car backward
 */
void goBack() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
}

/*
 * Descrip: make car stop
 */
void stop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void loop() {
  stop();
  if(mySerial.available()) {
    data = mySerial.readString(); 
    mySerial.println(data);
    
    if(data == F) {
      Delay(10 * t, goAhead);
    }
    else if(data == L) {
      Delay(t, turnLeft);
    }
    else if(data == R) {
      Delay(t, turnRight);
    }
    else if(data == B) {
      Delay(10 * t, goBack);
    }
    else if(data == S) {
      stop();
    }
  }
}
