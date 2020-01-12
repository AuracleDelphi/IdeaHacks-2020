#define REDPIN 10
#define GREENPIN 11
#define BLUEPIN 9
#include <SoftwareSerial.h>

SoftwareSerial bSerial(2, 3); // RX, TX

//This is a starting character value that will be replaced by values recieved over bluetooth
char inputChar = 'a';
bool override = false;
void recolor();
byte r,g,b;

void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  
  Serial.begin(9600);

  bSerial.begin(9600);
}
 
 
void loop() {
//  while(bSerial.available()) {
//    Serial.write(bSerial.read());
//  }
//  while(Serial.available()) {
//    char c = Serial.read();
//    bSerial.write(c);
//    Serial.print(c);
//  }
  
  if (bSerial.available() > 0) //The value returned by Serial.available() will be 0 if there has not been a transmission.
  {
    inputChar = bSerial.read();  //Store character read from serial
    Serial.println(inputChar);  //This sends the recieved value back to the the Bluetooth master (your computer). This prints the value for you to see
    switch (inputChar)
    {
      case 'O':
        override = true;
        break;
       case 'o':
        override = false;
        break;
      case 'R':   //Red LED
        r = 255;
        g = 0;
        b = 0;
        break;
     case 'G':   //Red LED  
        r = 0;
        g = 255;
        b = 0;
        break;
     case 'Y':   //Red LED
        r = 255;
        g = 255;
        b = 0;
        break;
      default:
        break;
    }
    recolor();
  }
}
void recolor() {
  if(override) {
    analogWrite(REDPIN, 100);
    analogWrite(GREENPIN, 0);
    analogWrite(BLUEPIN, 255);
    return;
  }
  analogWrite(REDPIN, r);
  analogWrite(GREENPIN, g);
  analogWrite(BLUEPIN, b);
}
