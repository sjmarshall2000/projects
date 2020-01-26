int lightPin = 10;
void setup() {
  // put your setup code here, to run once:
  pinMode(lightPin,OUTPUT);

  digitalWrite(lightPin, HIGH);
}

void flashABunch(int numSeconds, int numFlashes){ //take only the amount of time in NumSeconds 
  numFlashes--;
  int flashesPerSec;
  int timePerFlash;

  
  flashesPerSec = 3;
  timePerFlash = (numSeconds * 1000) / numFlashes;



  int delayTime = timePerFlash / 2; //in ms // one delay for on and one for off
  
  bool on = true;
  for(int i = 0; i <= numSeconds * 1000; i+= delayTime){
    on = !on; //flip the bool
    digitalWrite(lightPin, on); //set light to this bool
    delay(delayTime);
  }
  digitalWrite(lightPin, HIGH);//make sure its on
}
//  
//  //numFlashes = num
//  digitalWrite(lightPin, HIGH);
//  for(int i = 0; i < numFlashes; i++){
//    delay(timePerFlash / 2);
//    digitalWrite(lightPin, LOW);
//    delay(timePerFlash / 2);
//    digitalWrite(lightPin, HIGH);
////    for(int j = 0; j < flashesPerSec; j++){
////      
////    }
//  }


void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);
  flashABunch(180, 180 * 15);

}
