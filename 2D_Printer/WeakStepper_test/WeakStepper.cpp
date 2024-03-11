//#include "HardwareSerial.h"
#include "Arduino.h"
#include "WeakStepper.h"




void WeakStepper::setRPM(float rpm) {
  _rpm = rpm;
}

float WeakStepper::_calcRPM(float rpm) {  //1 RPM = micro delay 14648
  return 14648 / rpm;                     //Return delay between steps in microSeconds
}

void WeakStepper::move_zero() {
  while(!ready()){
  move_to(-120);
  }
  _stepTick1 = 0;
}

void WeakStepper::move_to(float distance) {           //move (in millimeters)
  _stepManager(distance * 1.25 / 6 * 4096);  //Thread pitch 0.8, gears 6/1, one rotatione = 4096 steps
}

void WeakStepper::_stepManager(long stepPosition) {
  _flagRD = 0;  //Not ready for next command

  if (micros() < _timer1) {
    _timer1 = 0;
  }

  if (_stepTick1 < stepPosition and micros() - (_calcRPM(_rpm) + _timer1) > 0) {
    _stepTick1++;
    _timer1 = micros();
    _step++;
    if (_step >= 8) _step = 0;  //if more that 8 = state 0
    _stepper(_step);

  }

  if (_stepTick1 > stepPosition and micros() - (_calcRPM(_rpm) + _timer1) > 0) {
    _stepTick1--;
    _timer1 = micros();
    _step--; 
    if (_step < 0) _step = 7;  //if less that 0 = state 7
    _stepper(_step);
  }

  if (_stepTick1 == stepPosition) {
    _flagRD = 1;
  }
}

bool WeakStepper::ready(){
  return _flagRD;
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
}