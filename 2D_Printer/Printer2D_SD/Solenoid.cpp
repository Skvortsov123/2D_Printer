#include "Arduino.h"
#include "Solenoid.h"

#define DOWN_TIME 200    //Delay to get Down
#define UP_TIME 50      //Delay to get Up


Solenoid::Solenoid(int pin1) {
  _pin1 = pin1;
  pinMode(pin1, OUTPUT);
}


bool Solenoid::point() {
  bool result = false;
  if (millis() < _timer1) {   //Reset _timer1 if millis() overflows
    _timer1 = 0;
  }
  if (!_downPointReady) {
    _downPointReady = _down();   //Allready dwon position
  }else if(!_upPointReady) {
    _upPointReady = _up();       //Allready upp position
  }else{
    _downPointReady = false;
    _upPointReady = false;
    result = true;
  }
  return result;
}


bool Solenoid::_down() {
  bool result = false;
  if (_oneTime) {
    _oneTime = false;
    _timer1 = millis();
    digitalWrite(_pin1, HIGH);
  }else if (millis() > _timer1 + DOWN_TIME) {
    result = true;
    _oneTime = true;
  }
  return result;
}


bool Solenoid::_up() {        //Reset _timer1 if millis() overflows
  bool result = false;
  if (_oneTime) {
    _oneTime = false;
    _timer1 = millis();
    digitalWrite(_pin1, LOW);
  }else if (millis() > _timer1 + UP_TIME) {
    result = true;
    _oneTime = true;
  }
  return result;
}


