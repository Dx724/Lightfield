#include <Stepper.h>
#include <ESP32Servo.h>

const int stepsPerRevolution = 2038;

Stepper stepper = Stepper(stepsPerRevolution, 14, 26, 27, 25);
int currentRotation = 0;

Servo servo;

const int ledPins[] = {2, 32, 33}; // R, G, B
const int pwmCh[] = {5, 6, 7};
int red = 255;
int green = 0;
int blue = 255;

double r1 = 8.89; // cm
double r2 = 9.85; // cm
double maxrad = r1 + r2 - 0.1 // cm (small tolerance provided)

void setup() {
  stepper.setSpeed(15);

  servo.setPeriodHertz(50);
  servo.attach(15, 500, 2500);

  for (int i = 0; i < 3; i++) {
    ledcSetup(pwmCh[i], 1000, 8);
    ledcAttachPin(ledPins[i], pwmCh[i]);
  }
}

void stepper_move(int steps) {
  currentRotation += steps;
  stepper.step(steps);
}

void stepper_toangle(int angle) {
  stepper_move(stepsPerRevolution*(angle/360.0) - currentRotation);
}

void setColor(byte r, byte g, byte b) {
  ledcWrite(pwmCh[0], 255 - r);
  ledcWrite(pwmCh[1], 255 - g);
  ledcWrite(pwmCh[2], 255 - b);
}

void move_to_polar(double rad, double ang) {
  
}

void loop() {
  stepper_toangle(45);
  servo.write(45);
  stepper_toangle(0);
  servo.write(0);
  setColor(red, green, blue);
}
