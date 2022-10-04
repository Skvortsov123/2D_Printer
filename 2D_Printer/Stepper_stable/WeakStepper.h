#include "Arduino.h"
#ifndef WeakStepper_H
#define WeakStepper_H

class WeakStepper {
public:

  WeakStepper() {
    _pin[0] = 8;
    _pin[1] = 9;
    _pin[2] = 10;
    _pin[3] = 11;
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
  }
  WeakStepper(int pin1, int pin2, int pin3, int pin4) {
    _pin[0] = pin1;
    _pin[1] = pin2;
    _pin[2] = pin3;
    _pin[3] = pin4;
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pin3, OUTPUT);
    pinMode(pin4, OUTPUT);
  }
  void setRPM(float rpm);  //Best RPM 5-2
  bool move_mm(float distance);  //Return True when ready. Get coordinates in mm

private:
  bool _stepManager(long amountStep);
  void _stepper(int seqIN); 
  float _calcRPM(float rpm);

  int _pin[4];
  float _rpm = 20;
  int _step;
};

#endif