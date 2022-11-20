#include "barometer.h"

void setup() {
  Serial.begin(9600);
  Serial.println("This is split barometer sketch.");
  Serial.println("Initializing barometer...");
  initializeBarometer();
}

void loop() {
  printElevation();
  printTemp();
  delay(3000);
}
