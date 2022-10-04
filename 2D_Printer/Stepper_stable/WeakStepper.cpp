#include "HardwareSerial.h"
#include "Arduino.h"
#include "WeakStepper.h"




void WeakStepper::setRPM(float rpm) {
  _rpm = rpm;
}



float WeakStepper::_calcRPM(float rpm) {  //1 RPM = micro delay 14648
  return 14648 / rpm;                     //Return delay between steps in microSeconds
}



bool WeakStepper::move_mm(float distans) {    //move (in millimeters)
  _stepManager(distans * 1.25 / 9.5 * 4096);  //Thread pitch 0.8, gears 9.5/1, one rotatione = 4096 steps
}



bool WeakStepper::_stepManager(long amountStep) {
  if (amountStep > 0) {  //if positive number
    for (long n = 0; n < amountStep; n++) {
      _step++;
      if (_step >= 8) _step = 0;  //if more that 8 = state 0
      _stepper(_step);
    }
  }
  if (amountStep < 0) {
    amountStep = amountStep * -1;
    for (long n = 0; n < amountStep; n++) {
      _step--;
      if (_step <= -1) _step = 7;  //if less that 0 = state 8
      _stepper(_step);
    }
  }
}



void WeakStepper::_stepper(int seqIN) {  //Total 4096 miniSteps
  bool _coil[4];

  switch (seqIN) {
    case 0:
      {
        _coil[0] = 1;
        _coil[1] = 0;
        _coil[2] = 0;
        _coil[3] = 0;
        break;
      }
    case 1:
      {
        _coil[0] = 1;
        _coil[1] = 1;
        _coil[2] = 0;
        _coil[3] = 0;
        break;
      }
    case 2:
      {
        _coil[0] = 0;
        _coil[1] = 1;
        _coil[2] = 0;
        _coil[3] = 0;
        break;
      }
    case 3:
      {
        _coil[0] = 0;
        _coil[1] = 1;
        _coil[2] = 1;
        _coil[3] = 0;
        break;
      }
    case 4:
      {
        _coil[0] = 0;
        _coil[1] = 0;
        _coil[2] = 1;
        _coil[3] = 0;
        break;
      }
    case 5:
      {
        _coil[0] = 0;
        _coil[1] = 0;
        _coil[2] = 1;
        _coil[3] = 1;
        break;
      }
    case 6:
      {
        _coil[0] = 0;
        _coil[1] = 0;
        _coil[2] = 0;
        _coil[3] = 1;
        break;
      }
    case 7:
      {
        _coil[0] = 1;
        _coil[1] = 0;
        _coil[2] = 0;
        _coil[3] = 1;
        break;
      }
    default:
      {
        _coil[0] = 0;
        _coil[1] = 0;
        _coil[2] = 0;
        _coil[3] = 0;
        break;
      }
  }

  for (int p = 0; p < 4; p++) {
    digitalWrite(_pin[p], _coil[p]);
  }
  delayMicroseconds(_calcRPM(_rpm));
}