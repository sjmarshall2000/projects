//This code is the work of Stephen Marshall, 2019

//7/11/19: as of today, the left/right pins are swapped
//i.e. right is now pin 10, left is now pin 11 -hardware change
//7/27/19: readjusting bounds to reflect physical installation:
//UDMIN:  406
//UDMAX:  647
//LRMIN:  279
//LRMAX:  500

const bool potDebug = false;
//PINS:###########
//tone-interrupt system
const int tonePin = 12; //pin for the interrupting tone
const int interruptPin = 2;//pin to attach interrupt
//steppers have step and directional pins
const int UDstepPin = 6; //stepper next to psu
const int UDdirPin = 7;//Up - Down
const int LRstepPin = 4;//Left - Right
const int LRdirPin = 5;
//joystick pins:
const int joyPinUp = 8;
const int joyPinDown = 9;
const int joyPinLeft = 10;
const int joyPinRight = 11;
//potentiometer pins
const int UDsensorPin = A1; //A1, A0 ... are Arduino Uno exclusive
const int LRsensorPin = A0;
//Values:##########
bool directions[4]; //will be constantly updated as joystick moves
//directions: [up][right][down][left]
int UDsensor = 0;//not sure why '=0'
int LRsensor = 0;//zeroing out the values? or temp values?
int UD_MIN = 406;//Exact Values as of 7/27/19
int UD_MAX = 647;
int LR_MIN = 279;//by ensuring their are correctly oriented at time of assembly,
int LR_MAX = 500;//we can assume LR and UD are the same


const bool invertPot = false; //broken feature, hard coded below

const int homeThreshold = 25; //diameter of range to consider the center

bool input = false;
int counter; //used to count up during acceleration
int baseFreq = 1000;
int maxFreq = 1800; //based on sound
int acceleration = 2;

int pin;  //variable used in pulse(), instantiating here
const int pulseWidth = 15; //width of stepper power pulse, in microseconds

const bool UD=true;
const bool LR=false;
void pulse(bool isUD=UD){ //true means up-down, false means left-right
  if(isUD){pin = UDstepPin;
  } else {pin = LRstepPin;}
  digitalWrite(pin, HIGH);    //at this point, direction pin should be set
  delayMicroseconds(pulseWidth);
  digitalWrite(pin, LOW);
}
void moveSteppers(){ //reads directions[] //directions[]: [up][right][down][left]
  if(directions[0] && UDsensor < UD_MAX) {             //UP
    digitalWrite(UDdirPin, HIGH);
    pulse(UD);
    //Serial.println("moved UP");
  }
  else if(directions[2] && UDsensor > UD_MIN) {        //DOWN
    digitalWrite(UDdirPin, LOW);
    pulse(UD);
    //Serial.println("moved DOWN");
  }
//LR
  if(directions[1] && LRsensor > LR_MIN) {             //RIGHT
    digitalWrite(LRdirPin, HIGH);
    pulse(LR);
    //Serial.println("moved RIGHT");
  } else if(directions[3] && LRsensor < LR_MAX ) {     //LEFT -this direction is the problem
    digitalWrite(LRdirPin, LOW);
    pulse(LR);
    //Serial.println("moved LEFT");
  }
}
void homeSteppers(){
  int UDlower,UDupper,LRlower,LRupper;
  int UDmid,LRmid;
  UDmid = (UD_MIN + UD_MAX) / 2; //integer imprecise
  LRmid = (UD_MIN + UD_MAX) / 2;
  UDlower = UDmid - homeThreshold;
  UDupper = UDmid + homeThreshold;
  LRlower = LRmid - homeThreshold;
  LRupper = LRmid + homeThreshold;
  //Serial.println("enteringWhileLoop");
  
  while(UDsensor < UDlower|| UDsensor > UDupper || LRsensor < LRlower || LRsensor > LRupper){

    if(UDsensor < UDlower) {
      Serial.println("A");
      directions[2] = false;
      directions[0] = true; //move up
    } else if(UDsensor > UDupper) {
      Serial.println("B");
      directions[0] = false;
      directions[2] = true; //move down
    } else {
      directions[0] = false;
      directions[2] = false;
    }
    if(LRsensor < LRlower) {
      Serial.println("C");
      directions[3] = false;
      directions[1] = true; //move right
    } else if(LRsensor > LRupper) {
      Serial.println("D");
      directions[1] = false;
      directions[3] = true; //move left
    }
    Serial.println("end of while");
  }
  //interrupts();
}
void setup() {
  if(potDebug){
    Serial.begin(9600);
    UD_MIN = 0;
    UD_MAX = 1000;
    LR_MIN = 0;
    LR_MAX = 1000;
  }
  
  if(invertPot){ //for mounting the pot on the motor side
  int temp = UD_MIN;
  UD_MIN = UD_MAX;
  UD_MAX = temp;
}
  // set pinmodes
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
  
  //homeSteppers();
}

void handler(){
  if(input){
    moveSteppers();
    if(counter < maxFreq){ 
      counter += acceleration;
      tone(tonePin, counter);
    }
    
    
  } else {
    counter = baseFreq;
    tone(tonePin, baseFreq);//when called, updates tone 
  } 
}

void loop() {
  //     ---Take Input---
  input = false;
  directions[0] = !digitalRead(joyPinUp); //pins are being grounded when activated, thus false means pressed
  directions[2] = !digitalRead(joyPinDown);
  
  directions[1] = !digitalRead(joyPinRight);
  directions[3] = !digitalRead(joyPinLeft);

  for(int i = 0; i < 4; i++){
    if(directions[i]){input = true;}
  }
  //clean up input:
//  if(directions[0]){directions[2] = false;}
//  if(directions[1]){directions[3] = false;}
//  if(directions[2]){directions[0] = false;}
//  if(directions[3]){directions[1] = false;}
  //    ---Read Sensors---
  UDsensor = 1000 - analogRead(UDsensorPin); //subtraction counteracts reversed mounting
  LRsensor = analogRead(LRsensorPin);

  if(potDebug){
    Serial.print("UD: ");
    Serial.print(UDsensor);
    Serial.print("\t\tLR: ");
    Serial.println( LRsensor);
  }
  //interrupts();
  //delay(200);
  //increment the velocity, increase by accel, etc
  //baseFreq += acceleration
}
