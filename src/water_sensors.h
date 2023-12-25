#include "Arduino.h"
#include "constants.h"

bool check_water_level(int GPIO_sensor, int GPIO_ref) {
  // returns 1 if water between GPIO_sensor and GIPO_ref
  digitalWrite(GPIO_ref, HIGH);
  delayMicroseconds(100);
  auto ret = digitalRead(GPIO_sensor);
  digitalWrite(GPIO_ref, LOW);
  return ret;
}


bool check_water_level_tree() {
  // returns 1 if water high enough
  return check_water_level(GPIO_tree_sensor, GPIO_tree_ref);
}

bool check_water_level_reservoir() {
  // returns 1 if water high enough
  return check_water_level(GPIO_reservoir_sensor, GPIO_reservoir_ref);
}

