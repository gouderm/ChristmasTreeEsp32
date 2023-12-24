#include "Arduino.h"
#include "constants.h"

void beep_startup() {
    for (int i = 0; i < 5; i++) {
        digitalWrite(GPIO_alarm, LOW);
        delay(50);
        digitalWrite(GPIO_alarm, HIGH);
        delay(50);
    }
}

void beep_low_reservoir_level() {
    for (int i = 0; i < 3; i++) {
        digitalWrite(GPIO_alarm, LOW);
        delay(400);
        digitalWrite(GPIO_alarm, HIGH);
        delay(400);
    }
}

void beep_panic() {
    for (int i = 0; i < 10; i++) {
        digitalWrite(GPIO_alarm, LOW);
        delay(100);
        digitalWrite(GPIO_alarm, HIGH);
        delay(100);
    }
}

