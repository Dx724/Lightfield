const int ledPins[] = {33, 32, 13}; // R, G, B
const int pwmCh[] = {5, 6, 7};

double BRIGHTNESS = 1.0; // Allow scaling down brightness to enable longer exposures

void setup() {
  for (int i = 0; i < 3; i++) {
    ledcSetup(pwmCh[i], 1000, 8);
    ledcAttachPin(ledPins[i], pwmCh[i]);
  }
}

void setColor(byte r, byte g, byte b) {
  r *= BRIGHTNESS;
  g *= BRIGHTNESS;
  b *= BRIGHTNESS;
  ledcWrite(pwmCh[0], 255 - r);
  ledcWrite(pwmCh[1], 255 - g);
  ledcWrite(pwmCh[2], 255 - b);
}

void loop() {
  // put your main code here, to run repeatedly:
  setColor(255, 0, 0);
  delay(1000);
  setColor(0, 255, 0);
  delay(1000);
  setColor(0, 0, 255);
  delay(1000);
  setColor(255, 255, 255);
  delay(1000);
  setColor(0, 0, 0);
  delay(1000);
}
