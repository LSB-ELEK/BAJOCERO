
#include <RTClib.h>
#include <TinyGPS.h>
#include <LiquidCrystal_I2C.h>

TinyGPS gps;
LiquidCrystal_I2C LCD(0x27, 16, 2);



void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  LCD.begin();

}

void loop() {
  bool newData = 0;
  String Datos;
