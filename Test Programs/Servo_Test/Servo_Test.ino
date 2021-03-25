#include <ESP32Servo.h>

Servo servo;

void setup() {
  servo.setPeriodHertz(50);
  servo.attach(15, 500, 2500);
}

void loop() {
  servo.write(180);
}
