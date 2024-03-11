#include "HardwareSerial.h"
#include "Printer.h"


Printer::Printer()
  : _motorX(6, 7, 8, 9), _motorY(A0, A1, A2, A3), _solenoid(5) {
}


void Printer::setup() {
  _data.setup();
  _motorX.setRPM(15);
  _motorY.setRPM(15);
  //_motorX.move_zero();
  //_motorY.move_zero();
  if (_data.getModeG()) {   //If "G21" in first line, read as G code
    _modeG = true;
  }else{
    _modeP = true;
  }
}


void Printer::tickP() {
  if (!_dataReady) {  //Search "1" on SD card
      _data.nextP();
      if (_data.readP() == '1') {
        _dataReady = true;
      }
      if (_data.readP() == '2') {
        _dataReady = true;
        _dataFinish = true;
      }
    }
    if (_dataReady && !_dataFinish) {  //Normal drawing
      if (!_motorXReady) {
        _motorX.move_to(_data.getPX());
        _motorXReady = _motorX.ready();
      }
      if (!_motorYReady) {
        _motorY.move_to(_data.getPY());
        _motorYReady = _motorY.ready();
      }
      if (_motorXReady && _motorYReady && !_point) {
        _point = _solenoid.point();
      }
      if (_motorXReady && _motorYReady && _point) {
        _dataReady = false;
        _motorXReady = false;
        _motorYReady = false;
        _point = false;
      }
    }
    if (_dataFinish) {  //Finishing, moving to x0 y0.
      if (!_motorXReady) {
        _motorX.move_to(0);
        _motorXReady = _motorX.ready();
      }
      if (!_motorYReady) {
        _motorY.move_to(0);
        _motorYReady = _motorY.ready();
      }
    }
}


void Printer::tickG() {
  _data.nextG();
}


void Printer::onTick() {
  if (_modeP) {          //Point mode
    tickP();
    Serial.println("P");
  }else if (_modeG) {      //Line mode
    tickG();
    Serial.println("G");
  }
}