#include "HardwareSerial.h"
#include "Arduino.h"
#include "SDcard.h"
#include <SPI.h>
#include <SD.h>



void SDcard::setup() {
  SD.begin(10);
  Serial.println("start");
}


void SDcard::read() {


  File filePic = SD.open("index.txt", FILE_READ);  //FILE_WRITE enables to read
  String str = filePic.readString();
  //Serial.println(str.length());
  _leng = 100;
  for (int i = 0; i < _leng; i++) {
    //Serial.println(i);
    char c = str.charAt(i);
    Serial.print(c);
  }
}