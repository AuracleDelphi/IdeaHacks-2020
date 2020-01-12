#include <SoftwareSerial.h>

SoftwareSerial SerialBT(2,3);

//pinout
#define RED 7
#define YELLOW 6
#define GREEN 5

#define REDPIN 10
#define GREENPIN 11
#define BLUEPIN 9


bool debounce();
unsigned long lastDebounceTimes[] = {0,0,0};  // the last time the output pin was toggled
uint8_t mac[6] = {0x00, 0x14, 0x03, 0x06, 0x39, 0xD1};
char *pin = "1234";
bool lastReadValue[] = {HIGH,HIGH,HIGH}; //recording falling edges

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("WELCOME");
  SerialBT.begin(9600); //Bluetooth device name, set to master
  
  pinMode(RED, INPUT_PULLUP);
  pinMode(YELLOW, INPUT_PULLUP);
  pinMode(GREEN, INPUT_PULLUP);

  //single rgb led
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //if there are bytes being received in serial port, send info via bt to connected device
//  while(SerialBT.available()) {
//    Serial.write(SerialBT.read());
//  }
  while(Serial.available()) {
    char c = Serial.read();
    if(c == 'o' || c == 'O') {
      SerialBT.write(c);
      analogWrite(BLUEPIN, 0);
    }
  }
  //return;
  if(debounce(RED, 0)){
    SerialBT.print('R');
    Serial.println('R');
    analogWrite(REDPIN, 255);
    analogWrite(GREENPIN, 0);
    analogWrite(BLUEPIN, 0);
  }
  
  if(debounce(YELLOW, 1)){
    SerialBT.print('Y');
    Serial.println('Y');
    analogWrite(REDPIN, 100);
    analogWrite(GREENPIN, 100);
    analogWrite(BLUEPIN, 0);
  }
  
  if(debounce(GREEN, 2)){
    SerialBT.print('G');
    Serial.println('G');
    analogWrite(REDPIN, 0);
    analogWrite(GREENPIN, 255);
    analogWrite(BLUEPIN, 0);
  }
}

bool debounce(byte pin, int index){
  const byte buttonPin = pin;    // the number of the pushbutton pin
  
  // Variables will change:
  bool buttonState = digitalRead(buttonPin);         // the current state of the output pin
  if(buttonState == lastReadValue[index]){ //if remaining at HIGH or remaining at LOW
    return false;
  }
  else if(buttonState == HIGH && lastReadValue[index] == LOW){ //button has been released
    lastReadValue[index] = HIGH;
    if(millis()-lastDebounceTimes[index] >=10){
      return true;
    }
    return false;
  }
  else{ //button has been pressed
    lastReadValue[index] = LOW;
    lastDebounceTimes[index] = millis();
    return false;
  }
}
