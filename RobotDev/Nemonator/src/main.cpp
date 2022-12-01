#include <Arduino.h>
#include "motorControls.h"
#include "serverCommands.h"
void setup() {
  MotorSetup();
  serverSetup();
}

void loop() {
  runServer();
}