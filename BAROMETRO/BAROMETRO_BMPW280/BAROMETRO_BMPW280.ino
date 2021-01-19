#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(9600);
  if (!bmp.begin()) {
    Serial.println(F("ERROR"));
    while (1);
  }
}

void loop(){
  delay(1000);
  Serial.print(F("Temp = "));
  Serial.print(bmp.readTemperature());
  Serial.println(" C");
  Serial.print(F("Pres = "));
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");
  Serial.print(F("Altitud = "));
  Serial.print(bmp.readAltitude(1013.25));
  Serial.println(" m");
  Serial.println();
}
