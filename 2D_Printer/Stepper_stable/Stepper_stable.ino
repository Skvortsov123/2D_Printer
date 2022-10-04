#include "WeakStepper.h"
#include "Heartbeat.h"
Heartbeat heartbeat;


WeakStepper motorX(9, 10, 11, 12);
WeakStepper motorY(5, 6, 7, 8);



void setup() {
  Serial.begin(9800);
}

void loop() {
  heartbeat.beat();

  motorX.move_mm(120);
  //delay(2000);
  motorX.move_mm(-120);
  //delay(2000);

}