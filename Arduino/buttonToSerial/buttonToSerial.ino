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
  Serial.print("hello");
    
  delay(50);
}
