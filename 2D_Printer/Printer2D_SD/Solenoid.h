#include "Arduino.h"
#ifndef Solenoid_H
#define Solenoid_H


class Solenoid {
public:
  Solenoid(int pin1);
  bool point();
private:
  bool _down();
  bool _up();


  //bool _position = true;
  bool _downPointReady = false;
  bool _upPointReady = false;

  int _pin1 = 1;
  unsigned long _timer1 = 0;
  bool _oneTime = true;

};

#endif