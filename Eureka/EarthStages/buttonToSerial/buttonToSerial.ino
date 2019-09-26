const int greenPin = 12;
const int redPin = 13; //coincidentally the led pin
bool useEdgeDetection = false; //if TRUE, output values for both press and release, FALSE: just press
int greenLastState = 1;
int greenState;
int redLastState = 1;
int redState;
void setup() {
  Serial.begin(9600);

  pinMode(greenPin, INPUT_PULLUP);
  pinMode(redPin, INPUT_PULLUP);
}

void loop() {
  greenState = digitalRead(greenPin);
  redState = digitalRead(redPin);
  if (greenState != greenLastState) { //only enter this loop if state change
    if (!greenState) {              //pin reads LOW, i.e. its connected to GND,-> pressed
      Serial.print("A\n");
    } else if (useEdgeDetection) {  //state change and pin reads HIGH,-> released
      Serial.print("a\n");
    }
  }
  if (redState != redLastState) {
    if (!redState) {
      Serial.print("B\n");
    } else if (useEdgeDetection) {
      Serial.print("b\n");
    }

  }
  delay(50);
  greenLastState = greenState;
  redLastState = redState;
}
