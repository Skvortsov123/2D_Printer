#ifndef SDcard_H
#define SDcard_H

//next(); Manager = end();
class SDcard {
public:
  void setup(); //Use only right mode functions!

  void nextP(); //Point mode
  char readP();
  int getPX();
  int getPY();

  bool nextG(); //G-code mode //return 1 if line has coordinates
  int getGX();
  int getGY();
  bool getGZ();
  bool getModeG();
private:
  bool _modeG = false;
  int _PX = -1;
  int _PXSmart = _PX;    //Invert number when line even to rise print speed
  int _PY = 0;
  bool oneTime = true;
};


#endif