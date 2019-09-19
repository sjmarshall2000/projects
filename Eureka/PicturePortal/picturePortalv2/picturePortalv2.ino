//pins:
const int tonePin = 13; //pin for the interrupting tone
const int interruptPin = 2;//pin to attach interrupt
//steppers have step and directional pins
const int UDstepPin = 6; //stepper next to psu
const int UDdirPin = 7;
const int LRstepPin = 4;
const int LRdirPin = 5;
//joystick pins:
const int joyPinUp = 8;
const int joyPinDown = 9;
const int joyPinLeft = 10;
const int joyPinRight = 11;

//potentiometer pins
const int UDsensorPin = A1;
const int LRsensorPin = A0;

const int baseFreq = 12000;
const int acceleration = 10; // very arbitrary choice

//button values:
bool directions[4]; //will be constantly updated as joystick moved
bool joyStateUp;
bool joyStateDown;
bool joyStateLeft;
bool joyStateRight;

//int currentButton;int lastButton;

int UDsensor = 0;//not sure, zeroing out the values? or temp values?
int LRsensor = 0;

bool swapper = false; //just something to set steppers to
bool changed = false;

void setup() {
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  pinMode(UDstepPin, OUTPUT);
  pinMode(UDdirPin, OUTPUT);
  pinMode(LRstepPin, OUTPUT);
  pinMode(LRdirPin, OUTPUT);
  
  pinMode(joyPinUp, INPUT_PULLUP);
  pinMode(joyPinDown, INPUT_PULLUP);
  pinMode(joyPinLeft, INPUT_PULLUP);
  pinMode(joyPinRight, INPUT_PULLUP);

  pinMode(tonePin, OUTPUT);
  pinMode(interruptPin, INPUT);
  
  //PINS 2(interruptPin) and 13(tonePin) ARE CONNECTED BY JUMPER
  attachInterrupt(digitalPinToInterrupt(interruptPin), handler, FALLING);
  tone(tonePin, baseFreq);//set a tone to the pin which will be listening for interrupts
   
  // UD default lookin like 200 or something
  int UDdefault = 220;//double check
  // LR default lookin like 1000 or something
  int LRdefault = 910;//double check

  
}
void handler(){
  
  if(changed){ //set changed when input is read, set unchanged at the end of handler
    swapper = !swapper;
    //Serial.println(swapper);
    if(directions[0]) {//directions: [up][right][down][left]
      digitalWrite(UDdirPin, HIGH);
      digitalWrite(UDstepPin, swapper);
    } else if(directions[1]) {
      digitalWrite(LRdirPin, HIGH);
      digitalWrite(LRstepPin, swapper);
    } else if(directions[2]) {
      digitalWrite(UDdirPin, LOW);
      digitalWrite(UDstepPin, swapper);
    } else if(directions[3]) {
      digitalWrite(LRdirPin, LOW);
      digitalWrite(LRstepPin, swapper);
    }
    changed = false;
  }
    
}


void loop() {
  // put your main code here, to run repeatedly:
  // high is clockwise for dir pin and low is counterclockwise - steppers
  //bool oldDirections[] = {directions[0], directions[1], directions[3], directions[4]};
//UP
  bool prev = directions[0];
  directions[0] = !digitalRead(joyPinUp); //pins are pull-up by default, so pressed = 0 = false
  if(prev != directions[0]) {changed = true;}
//RIGHT
  prev = directions[1];
  directions[1] = !digitalRead(joyPinRight); //pins are pull-up by default, so pressed = 0 = false
  if(prev != directions[1]) {changed = true;}
//DOWN
  prev = directions[2];
  directions[2] = !digitalRead(joyPinDown); //pins are pull-up by default, so pressed = 0 = false
  if(prev != directions[2]) {changed = true;}
//LEFT
  prev = directions[3];
  directions[3] = !digitalRead(joyPinLeft); //pins are pull-up by default, so pressed = 0 = false
  if(prev != directions[3]) {changed = true;}
  
//  if(directions[0] != !digitalRead(joyPinUp)){
//    changed = true;
//    directions[0] = !digitalRead(joyPinUp);
////  }
//  directions[1] = !digitalRead(joyPinRight);
//  directions[2] = !digitalRead(joyPinDown);
//  directions[3] = !digitalRead(joyPinLeft);
  Serial.print("0: ");
  Serial.print(directions[0]);
  Serial.print(" 1: ");
  Serial.print(directions[1]);
  Serial.print(" 2: ");
  Serial.print(directions[2]);
  Serial.print(" 3: ");
  Serial.println(directions[3]);
  //changed = true;
  
  //for(int i = 0; i < 4; i++){
  //  if(oldDirections[i] != directions[i]){
  //    changed = true;
  //    Serial.println("changed");
  //    break;
  //  }
  //}
  

  //increment the velocity, increase by accel, etc
  
  UDsensor = analogRead(UDsensorPin);
  LRsensor = analogRead(LRsensorPin);
  
  
  //pin, freq, duration(ms)
  //tone(, 10000, 1000); 
  
  //digitalWrite(UDstepPin, HIGH);
  //delayMicroseconds(5);
  //digitalWrite(UDstepPin, LOW);
  //delayMicroseconds(1);

  
  /*
  if (buttonStateUp == LOW) {
    if (UDsensor > 0) {
      digitalWrite(3, HIGH);
      for (int i = 0; i < 25; i++) {
        digitalWrite(2, HIGH);
        delay(5);
        digitalWrite(2, LOW);
        delay(1);
      }
    }
  } else if (buttonStateDown == LOW) {
    if (UDsensor < 2000) {
      digitalWrite(3, LOW);
      for (int i = 0; i < 25; i++) {
        digitalWrite(2, HIGH);
        delay(5);
        digitalWrite(2, LOW);
        delay(1);
      }
    }
  } else if (buttonStateLeft == LOW) {
    if (LRsensor < 0) {
      digitalWrite(5, HIGH);
      for (int i = 0; i < 25; i++) {
        digitalWrite(4, HIGH);
        delay(5);
        digitalWrite(4, LOW);
        delay(1);
      }
    }
  } else if (buttonStateRight == LOW) {
    if (LRsensor < 2000) {
      digitalWrite(5, LOW);
      for (int i = 0; i < 25; i++) {
        digitalWrite(4, HIGH);
        delay(5);
        digitalWrite(4, LOW);
        delay(1);
      }
    }
  }
  
  Serial.print("UD: ");
  Serial.println(UDsensor);
  Serial.print("LR: ");
  Serial.println(LRsensor);
  */
}

//hopefully this method replaces the code repetition in loop()
//Direction:
//up:     0 (top right)
//right:  1 (bottom right)
//down:   2 (bottom left)
//left:   3 (top left)
void moveStepper(int direction){
  int dirPin;
  int stepPin;
  direction %= 4; //cleans up values to only be 0 - 3
  bool reversed = false;
  switch(direction){ //tone function
    case 0:
      dirPin = UDdirPin;
      stepPin = UDstepPin;
      reversed = false;
      break;
    case 1:
      dirPin = LRdirPin;
      stepPin = LRstepPin;
      reversed = false;
      break;
      
    case 2:
      dirPin = UDdirPin;
      stepPin = UDstepPin;
      reversed = true;
      break;
      
    case 3:
      dirPin = LRdirPin;
      stepPin = LRstepPin;
      reversed = true;
      break;
      
    default:
      Serial.print("oops it broke, direction invalid value");
    break;
  }
  
  if(direction == 2 || direction == 3) {//if its down or left
    digitalWrite(dirPin, LOW);          //set stepper direction to reversed
  } else { digitalWrite(dirPin, HIGH); }//otherwise set to normal  
}
