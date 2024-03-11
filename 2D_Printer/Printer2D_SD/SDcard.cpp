#include "WString.h"
#include "HardwareSerial.h"
#include "Arduino.h"
#include "SDcard.h"
#include <SPI.h>
#include <SD.h>

#define LINE_LENGHT 100
#define COLUMN_LENGHT 100

File myfile;
char* line;
void SDcard::setup() { //Setup
  SD.begin(10); //10pin
  myfile = SD.open("index.txt", FILE_READ);
  line = new char [LINE_LENGHT + 1];
  String l = myfile.readStringUntil('\n');
  strcpy(line, l.c_str());
  if (strcmp(line, "G21\n") == 3) {    //G mode activated, G21 mm standart, 3 because line is not 100% similar "G21\n"
    _modeG = true;
  }else{
    _modeG = false;
  }
}

char SDcard::readP() {
  if (_PY % 2 == 0) {       //Zigzag
  _PXSmart = _PX;
  }else{
  _PXSmart = COLUMN_LENGHT - 1 - _PX;
  }
  char let;
  if (_PY >= LINE_LENGHT) {        //If lines finish, return 2 to stop the printer
    let = '2';    //Go to x0 y0 and stop
  }else{
    let = line[_PXSmart];
  }
  return let;
}


void SDcard::nextP() {
  _PX++;
  if (_PX >= COLUMN_LENGHT) {  //Read next y if x > COLUMN_LENGHT-1
    _PX = 0;
    _PY++;
    String l = myfile.readStringUntil('\n');
    strcpy(line, l.c_str());
  }
}


int SDcard::getPX() {
  return _PXSmart;
}


int SDcard::getPY() {
  return _PY;
}


bool SDcard::nextG() {
//  if (getline(line, ))
}


int SDcard::getGX() {

}


int SDcard::getGY() {
  
}


bool SDcard::getGZ() {
  
}


bool SDcard::getModeG() {
  return _modeG;
}