//tone-interrupt system
const int tonePin = 12; //pin for the interrupting tone
const int interruptPin = 2;//pin to attach interrupt
//steppers have step and directional pins
const int UDstepPin = 6; //stepper next to psu
const int UDdirPin = 7;//Up - Down
const int LRstepPin = 4;//Left - Right
const int LRdirPin = 5;
const int joyPinUp = 8;
const int joyPinDown = 9;
const int joyPinLeft = 10;
const int joyPinRight = 11;
bool directions[4];
int baseFreq = 3000; //doesnt currently work as expected, but this seems like a reasonable value

int pin;
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
  if(directions[0]) {             //UP
    digitalWrite(UDdirPin, HIGH);
    pulse(UD);
    //Serial.println("moved UP");
  }
  else if(directions[2]) {        //DOWN
    digitalWrite(UDdirPin, LOW);
    pulse(UD);
    //Serial.println("moved DOWN");
  }
//LR
  if(directions[1]) {             //RIGHT
    digitalWrite(LRdirPin, HIGH);
    pulse(LR);
    //Serial.println("moved RIGHT");
  } else if(directions[3]) {      //LEFT 
    //Serial.println("passed left test");
    digitalWrite(LRdirPin, LOW);
    pulse(LR);
    //Serial.println("moved LEFT");
  }
}
void handler(){moveSteppers();}

void setup(){
  pinMode(UDstepPin, OUTPUT);
  pinMode(UDdirPin, OUTPUT);
  pinMode(LRstepPin, OUTPUT);
  pinMode(LRdirPin, OUTPUT);
  pinMode(joyPinUp, INPUT_PULLUP);
  pinMode(joyPinDown, INPUT_PULLUP);
  pinMode(joyPinLeft, INPUT_PULLUP);
  pinMode(joyPinRight, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), handler, RISING);//testing rising instead of falling
  tone(tonePin, baseFreq);//set a tone to the pin which will be listening for interrupts
}
void loop(){
  directions[0] = !digitalRead(joyPinUp); //pins are being grounded when activated, hence false meaning true
  directions[1] = !digitalRead(joyPinRight);
  directions[2] = !digitalRead(joyPinDown);
  directions[3] = !digitalRead(joyPinLeft);
}
