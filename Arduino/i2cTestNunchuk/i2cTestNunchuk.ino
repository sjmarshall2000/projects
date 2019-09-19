#include <Wire.h>
#include "Nunchuk.h"

void setup() {
  // put your setup code here, to run once:
  
  //i2c_param_config();

  //i2c_driver_install(0,);
  
  Serial.begin(9600);
  Wire.begin();
  //Serial.println("\nI2C Scanner");
  nunchuk_init();
}

void loop() {


  if(nunchuk_read()){
    //work with data
    nunchuk_print();
  }
  delay(10);
//  byte error, address;
//  int nDevices;
//  Serial.println("Scanning...");
//  nDevices = 0;
//  for(address = 1; address < 127; address++ ) {
//    Wire.beginTransmission(address);
//    error = Wire.endTransmission();
//    if (error == 0) {
//      Serial.print("I2C device found at address 0x");
//      if (address<16) {
//        Serial.print("0");
//      } else {
//        Serial.print(address,HEX);
//      }
//      nDevices++;
//    }
//    else if (error==4) {
//      Serial.print("Unknow error at address 0x");
//      if (address<16) {
//        Serial.print("0");
//      }
//      Serial.println(address,HEX);
//    }    
//  }
//  if (nDevices == 0) {
//    Serial.println("No I2C devices found\n");
//  }
//  else {
//    Serial.println("\ndone\n");
//  }
//  //Serial.println(address, DEC);
//  delay(5000);

}

































//'***************************************************************************
//'* Wii Nunchuk code                                                        *
//'* Poorly coded by Russ McIntire 10/21/16                                  *
//'* Lots stolen from on-line sources                                        *
//'* http://www.robotshop.com/media/files/PDF/inex-zx-nunchuck-datasheet.pdf *
//'*                                                                         *
//'* Added buttons to start, stop and end the program                        *
//'***************************************************************************
//
//
//looper = 0
//address = 82   'Nunchuck address
//
//i2c.setup(D3,D4)
//i2c.begin(address)
//i2c.write(64)      'Initialize with a 64 followed by a 0
//i2c.write(0)
//i2c.end()
//
//wprint "Start, stop and end the wii nunchuk display on the serial port <br>"
//button "START", [startloop]
//wprint "<br>"
//button "STOP", [stoploop]
//wprint "<br>"
//button "END", [endprog]
//
//
//
//timer 10, [loop]
//wait
//
//
//[loop]
//if looper = 0 then goto [skip]
//
//gosub [sendzero]   'Send a zero to trigger receive
//i2c.requestfrom(address,6)  'Receive 6 bytes
//
//b1 = (val(i2c.read()) xor 23) + 23 'X joystick
//b2 = (val(i2c.read()) xor 23) + 23 'Y joystick
//b3 = (val(i2c.read()) xor 23) + 23 'x accelerometer bit 9 to bit 2
//b4 = (val(i2c.read()) xor 23) + 23 'y accelerometer bit 9 to bit 2
//b5 = (val(i2c.read()) xor 23) + 23 'z accelerometer bit 9 to bit 2
//b6 = (val(i2c.read()) xor 23) + 23 '2 bits of x y z, and C and Z button
//
//z = b6 and 1                       'set z button
//c = (b6 >> 1) and 1                'set c button
//
//joyx = b1
//joyy = b2
//
//accelx = (b3 << 2) + ((b6 >> 2) and 3) 'add 2 bits to x
//accely = (b4 << 2) + ((b6 >> 4) and 3) 'add 2 bits to y
//accelz = (b5 << 2) + ((b6 >> 6) and 3) 'add 2 bits to z
//
//serialprintln z & " " & c & " " &joyx & " " & joyy & " " & accelx & " " & accely & " " & accelz
//
//'gosub [sendzero] 'send zero to trigger next read
//
//[skip]
//wait
//
//
//[stoploop]
//looper = 0
//wait
//
//[startloop]
//looper = 1
//wait
//
//[endprog]
//end
//wait
//
//[sendzero]
//i2c.begin(address)
//i2c.write(0)
//i2c.end()
//return
