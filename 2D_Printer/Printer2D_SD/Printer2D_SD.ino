#include "MySD.h"

  SDcard SDa;


void setup() {
  Serial.begin(9600);
  SDa.setup();
}

void loop() {
  SDa.read();

}



//Data <- Manager -> Stepper