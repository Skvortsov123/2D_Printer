//Servo A0
//SPI D13-D10
//MotorX D9-D6    MotorY D5-D2

class Manager{
private:
  SDcard _data;
  WeakStepper _motorX(6, 7, 8, 9);
  WeakStepper _motorY(2, 3, 4, 5);
public:
  Manager(){

  }


};