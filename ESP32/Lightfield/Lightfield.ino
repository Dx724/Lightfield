#include <Stepper.h>
#include <ESP32Servo.h>

const int stepsPerRevolution = 2038;

Stepper stepper = Stepper(stepsPerRevolution, 14, 26, 27, 25);
int currentRotation = 0;

Servo servo;
const int SERVO_OFFSET = 0; // Extra degrees past 180 to point straight back to center (should be a negative or zero quantity)

const int ledPins[] = {33, 32, 2}; // R, G, B
const int pwmCh[] = {5, 6, 7};
int red = 255;
int green = 0;
int blue = 255;

double r1 = 8.89; // cm
double r2 = 9.85; // cm
double maxrad = r1 + r2 - 0.1; // cm (small tolerance provided)

void setup() {
  //Serial.begin(9600);
  stepper.setSpeed(15);

  for (int i = 0; i < 3; i++) {
    ledcSetup(pwmCh[i], 1000, 8);
    ledcAttachPin(ledPins[i], pwmCh[i]);
  }

  servo.setPeriodHertz(50);
  servo.attach(15, 500, 2500); // This will find an unused PWM channel to attach to
}

void stepper_move(int steps) {
  currentRotation += steps;
  stepper.step(steps);
}

void stepper_to_angle(double angle) { // Calculated with acos, so should remain bounded
  stepper_move((int) (stepsPerRevolution*(angle/360.0) - currentRotation));
}

void combo_move(double th1, double th2) {
  stepper_to_angle(th1);
  servo.write((int) th2);
}

void setColor(byte r, byte g, byte b) {
  ledcWrite(pwmCh[0], 255 - r);
  ledcWrite(pwmCh[1], 255 - g);
  ledcWrite(pwmCh[2], 255 - b);
}

void move_to_polar(double rad, double ang) {
  rad *= maxrad;
  if (rad == 0) // Avoid divide-by-zero issues
    rad = 0.001;
  double theta1 = acos((r1*r1+rad*rad-r2*r2)/(2*r1*rad));
  double theta2 = acos((r1*r1+r2*r2-rad*rad)/(2*r1*r2));
  theta1 *= 180.0 / PI;
  theta2 *= 180.0 / PI;
  theta1 = ang - theta1;
  theta2 = 180 + SERVO_OFFSET - theta2;
  //stepper_to_angle(theta1);
  //servo.write((int)theta2);
  combo_move(theta1, theta2);
  //Serial.print(theta1);
  //Serial.print("  ");
  //Serial.println(theta2);
}

void loop() {
  for (float i = 0.1; i < 1.0; i += 0.01) {
    move_to_polar(i, 35);
    delay(50);
  }
}
