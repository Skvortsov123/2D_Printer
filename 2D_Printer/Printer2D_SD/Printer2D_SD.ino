#include "Printer.h"

Printer printer;

void setup() {
  Serial.begin(9600);
  printer.setup();
}

void loop() {
  printer.onTick();
}


//Data <- Manager -> Stepper