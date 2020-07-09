//TODO: the output currently prints arduino pins, not correct row col
// Also, only works on some rows? very strange

//REFERENCE:
//p1: row 3 def
//p2: row 2 def
//p3: col 1 prob
//p4: row 1 prob
//p5: col 3 prob
//p6: row 4 prob
//p7: col 2 prob

int p1 = 2;
int p2 = 3;
int p3 = 4;
int p4 = 5;
int p5 = 6;
int p6 = 7;
int p7 = 8;

int pins[] = {2,3,4,5,6,7,8};

//int r1,r2,r3,r4,c1,c2,c3;

int r1 = pins[4];
int r2 = pins[2];
int r3 = pins[1];
int r4 = pins[6];
int c1 = pins[3];
int c2 = pins[7];
int c3 = pins[5];

int rows[] = {r1,r2,r3, r4};
int cols[] = {c1,c2,c3};


void setup() {

  int pressedRow;
  int pressedCol;
  Serial.begin(9600);
  for( int r : rows){ //for every row
    pinMode(r, INPUT_PULLUP);
  }
  for( int c : cols){ //for every column
    pinMode(c, OUTPUT);
    digitalWrite(c, LOW);
  }

  bool rowFound = false;
  bool colFound = false;

  while (!rowFound){
    for( int r : rows){
      if(!digitalRead(r)){ //if it's pulled low
        rowFound = true;
        pressedRow = r;
        Serial.print("Pressed @ row: ");
        Serial.print(r); 
      }
    }
  }

  //now columns become inputs and rows become outputs
  for( int c : cols){ //for every column
    pinMode(c, INPUT_PULLUP);
  }
  for( int r : rows){ //for every row
    pinMode(r, OUTPUT);
    digitalWrite(r, LOW);
  }

  while (!colFound){
    for( int c : cols){
      if(!digitalRead(c)){ //if it's pulled low
        colFound = true;
        pressedCol = c;
        Serial.print("Pressed @ col: ");
        Serial.println(c);
         
      }
    }
  }
  
}

void loop() {
  
  
  
  

}
