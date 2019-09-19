void setup() {
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  digitalWrite(7,HIGH);
  tone(6, 3000);//set a tone to the pin which will be listening for interrupts
}

void loop() {
}
