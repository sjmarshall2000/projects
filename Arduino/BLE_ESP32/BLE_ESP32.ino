//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

//Edited by Stephen Marshall Oct 22, 2019

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
String message = "";
char input;

void setup() {
  pinMode(5, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (Serial.available()) {
    //message = Serial.read();
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    char c = SerialBT.read();
    Serial.println(c);
    if(c==97){
      digitalWrite(5,HIGH);
    } else if(c==98){
      digitalWrite(5,LOW);
    }else if(c>=48&&c<=57){
      
      c -= 48;


      for(int i = 0; i < c; i++){
        Serial.println((int)i);
        digitalWrite(5, HIGH);
        delay(100);
        digitalWrite(5,LOW);
        delay(100);
      }
      
      
      
//      
//      if(c == 49){    
//        Serial.println("on!");
//        digitalWrite(5, HIGH);
//      }else if(c == 48){
//        Serial.println("off!");
//        digitalWrite(5, LOW);
//      }  
    }
    delay(500);
  }
  delay(20);
}
