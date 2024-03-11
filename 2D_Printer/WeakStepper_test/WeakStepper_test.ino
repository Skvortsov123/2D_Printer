#include "WeakStepper.h"
#include "Heartbeat.h"


int var = 0;
Heartbeat heartbeat;
WeakStepper motorX(A0, A1, A2, A3);
WeakStepper motorY(9, 8, 7, 6);



void setup() {
  Serial.begin(9800);
  Serial.println("Serial.begin");
  motorX.move_zero();
}

void loop() {
  heartbeat.beat();

  switch (var) {
    case 0:
      {
        motorX.move_to(100);
        break;
      }
    case 1:
      {
        motorX.move_to(0);
        break;
      }
  }
  if (motorX.ready()) {
    var++;
    if (var >= 2){var = 0;}
  }
}