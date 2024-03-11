#include "SDcard.h"
#include "WeakStepper.h"
#include "Solenoid.h"

#ifndef Printer_H
#define Printer_H

//Solenoid 5
//SPI CS=D10  SCK=D13  MOSI=D11  MISO=D12
//MotorX D9-D6  MotorY A3-A0

class Printer {
public:
  Printer();
  void setup();
  void tickP();
  void tickG();
  void onTick();
private:
  SDcard _data;
  WeakStepper _motorX;
  WeakStepper _motorY;
  Solenoid _solenoid;
  bool _modeP = false;
  bool _modeG = false;
  bool _point = false;
  bool _dataReady = false;
  bool _dataFinish = false;
  bool _motorXReady = false;
  bool _motorYReady = false;
};

#endif