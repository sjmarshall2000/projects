const int buzz1pin = 2;
const int buzz2pin = 15;
const int buzz3pin = 5;
const int buzz4pin = 18;
const int buzz5pin = 23;
const int buzz6pin = 19;
const int buttonpin = 22;
const int buzztime = 800; //in milliseconds


#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
String message = "";
char input;

//String pi = "1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679";
//int piLength = pi.length();
//int indexNum = 0;

void buzz(int num){
  //num -= '0';
  
  int pin = buzz1pin;
    switch (num){
      case 0:
        digitalWrite(buzz1pin, HIGH);
        digitalWrite(buzz2pin, HIGH);
        digitalWrite(buzz3pin, HIGH);
        digitalWrite(buzz4pin, HIGH);
        digitalWrite(buzz5pin, HIGH);
        digitalWrite(buzz6pin, HIGH);
        delay(buzztime);
        digitalWrite(buzz1pin, LOW);
        digitalWrite(buzz2pin, LOW);
        digitalWrite(buzz3pin, LOW);
        digitalWrite(buzz4pin, LOW);
        digitalWrite(buzz5pin, LOW);
        digitalWrite(buzz6pin, LOW);
        break;
      case 1:
        digitalWrite(buzz1pin, HIGH);
        delay(buzztime);
        digitalWrite(buzz1pin, LOW);
        break;
      case 2:
        digitalWrite(buzz2pin, HIGH);
        delay(buzztime);
        digitalWrite(buzz2pin, LOW);
        break;
      case 3:
        digitalWrite(buzz1pin, HIGH);
        digitalWrite(buzz2pin, HIGH);
        delay(buzztime);
        digitalWrite(buzz1pin, LOW);
        digitalWrite(buzz2pin, LOW);
        break;
      case 4:
        digitalWrite(buzz3pin, HIGH);
        delay(buzztime);
        digitalWrite(buzz3pin, LOW);
        break;
      case 5:
        digitalWrite(buzz4pin, HIGH);
        delay(buzztime);
        digitalWrite(buzz4pin, LOW);
        break;
      case 6:
        digitalWrite(buzz3pin, HIGH);
        digitalWrite(buzz4pin, HIGH);
        delay(buzztime);
        digitalWrite(buzz3pin, LOW);
        digitalWrite(buzz4pin, LOW);
        break;
      case 7:
        digitalWrite(buzz5pin, HIGH);
        delay(buzztime);
        digitalWrite(buzz5pin, LOW);
        break;
       case 8:
        digitalWrite(buzz6pin, HIGH);
        delay(buzztime);
        digitalWrite(buzz6pin, LOW);
        break;
      case 9:
        digitalWrite(buzz5pin, HIGH);
        digitalWrite(buzz6pin, HIGH);
        delay(buzztime);
        digitalWrite(buzz5pin, LOW);
        digitalWrite(buzz6pin, LOW);
        break;
      
      
    }
}

  
void setup() {
  pinMode(buzz1pin, OUTPUT);
  pinMode(buzz2pin, OUTPUT);
  pinMode(buzz3pin, OUTPUT);
  pinMode(buzz4pin, OUTPUT);
  pinMode(buzz5pin, OUTPUT);
  pinMode(buzz6pin, OUTPUT);
  pinMode(buttonpin, INPUT_PULLUP);
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {

  if (SerialBT.available()) {
    char c = SerialBT.read();
    if(c > 47 && c < 58){
      Serial.println(c);
      buzz(c - 48);
    }
  }
    
      

  //buzz(0);
  delay(1000);
}
