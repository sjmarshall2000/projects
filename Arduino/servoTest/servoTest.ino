//#include <Servo.h>
//#include <"esp32-hal-ledc.h">
int COUNT_LOW = 2000;
int COUNT_HIGH = 7000;

int TIMER_WIDTH = 16;
int servoPin = 21; // same as neopixel

//Servo servo1;


void setup() {
  // put your setup code here, to run once:
  ledcSetup(1, 50, TIMER_WIDTH);
  ledcAttachPin(servoPin, 1);
  //servo1.attach(servoPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = COUNT_LOW; i < COUNT_HIGH; i=i+10){
    ledcWrite(1,i);
    delay(2);
  } 
  for(int i = COUNT_HIGH; i > COUNT_LOW; i=i-10){
    ledcWrite(1,i);
    delay(2);
  } 
}
