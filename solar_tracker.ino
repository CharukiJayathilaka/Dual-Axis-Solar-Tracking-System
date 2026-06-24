#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Servo horizontal;
Servo vertical;

LiquidCrystal_I2C lcd(0x27, 16, 2);

int hPos = 90;
int vPos = 90;

void setup() {

  horizontal.attach(9);
  vertical.attach(10);

  horizontal.write(hPos);
  vertical.write(vPos);

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
}

void loop() {

  int left = analogRead(A0);
  int right = analogRead(A1);

  int top = analogRead(A2);
  int bottom = analogRead(A3);

  // Horizontal Tracking
  if (left > right + 50) {
    hPos--;
  }

  if (right > left + 50) {
    hPos++;
  }

  // Vertical Tracking
  if (top > bottom + 50) {
    vPos++;
  }

  if (bottom > top + 50) {
    vPos--;
  }

  hPos = constrain(hPos, 0, 180);
  vPos = constrain(vPos, 0, 180);

  horizontal.write(hPos);
  vertical.write(vPos);

  // LCD Display
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("L:");
  lcd.print(left);

  lcd.setCursor(8,0);
  lcd.print("R:");
  lcd.print(right);

  lcd.setCursor(0,1);
  lcd.print("H:");
  lcd.print(hPos);

  lcd.setCursor(8,1);
  lcd.print("V:");
  lcd.print(vPos);

  delay(200);
}
