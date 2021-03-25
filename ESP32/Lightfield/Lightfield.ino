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
double maxrad = r1 + r2 - 0.1; // cm (small tolerance provided)

void setup() {
  Serial.begin(9600);
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

void stepper_to_angle(double angle) { // Calculated with acos, so should remain bounded
  stepper_move((int) (stepsPerRevolution*(angle/360.0) - currentRotation));
}

void setColor(byte r, byte g, byte b) {
  ledcWrite(pwmCh[0], 255 - r);
  ledcWrite(pwmCh[1], 255 - g);
  ledcWrite(pwmCh[2], 255 - b);
}

void move_to_polar(double rad, double ang) {
  rad *= maxrad;
  double theta1 = ang - acos((r1*r1+rad*rad-r2*r2)/(2*r1*rad));
  double theta2 = acos((r1*r1+r2*r2-rad*rad)/(2*r1*r2));
  theta1 *= 180.0 / PI;
  theta2 *= 180.0 / PI;
  stepper_to_angle(theta1);
  servo.write((int)theta2);
  Serial.print(theta1);
  Serial.print("  ");
  Serial.println(theta2);
}

void loop() {
  move_to_polar(0.5, 20);\
  setColor(255, 0, 0);
  delay(1000);
  move_to_polar(0.2, 40);
  setColor(0, 0, 255);
  delay(1000);
}
