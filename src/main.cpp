#include "Arduino.h"
#include "constants.h"
#include "buzzer.h"
#include "water_sensors.h"


void setup_gpio() {
  pinMode(GPIO_tree_sensor, INPUT_PULLDOWN);
  pinMode(GPIO_tree_ref, OUTPUT);
  pinMode(GPIO_reservoir_sensor, INPUT_PULLDOWN);
  pinMode(GPIO_reservoir_ref, OUTPUT);
  pinMode(GPIO_alarm, OUTPUT);
  pinMode(GPIO_pump, OUTPUT);
  pinMode(GPIO_water_calibration_S, INPUT_PULLDOWN);
  pinMode(GPIO_water_calibration_R, OUTPUT);
  
  digitalWrite(GPIO_tree_ref, LOW);
  digitalWrite(GPIO_reservoir_ref, LOW);
  digitalWrite(GPIO_alarm, HIGH);
  digitalWrite(GPIO_pump, LOW);
  digitalWrite(GPIO_water_calibration_R, HIGH);

  delayMicroseconds(100);
}

void pump_water(uint duration_s=7) {
  digitalWrite(GPIO_pump, HIGH);
  delay(duration_s * 1000);
  digitalWrite(GPIO_pump, LOW);
}


void calibration() {
  // buzz if tree-sensor is in water
  while (!digitalRead(GPIO_water_calibration_S)) {
    if (check_water_level_tree()) {
      digitalWrite(GPIO_alarm, LOW);
    } else {
      digitalWrite(GPIO_alarm, HIGH);
    }
  }
}

void water_watchdog() {
  uint pump_ctr = 0;
  
  while (true) {
    if (!check_water_level_reservoir()) {
      beep_low_reservoir_level();
    }
    
    if (!check_water_level_tree()) {
      pump_ctr += 1;
      
      // try to pump water up to three times
      if (pump_ctr <= 3) {
        pump_water();
      } else { // panic if still low water-level, despite pumping
        beep_panic();
      }

    } else {
      pump_ctr = 0;
    }
    
    delay(3000);
  }
}

void setup() {
  setup_gpio();
  calibration();
  beep_startup();
  water_watchdog();
}

void loop() {
}
