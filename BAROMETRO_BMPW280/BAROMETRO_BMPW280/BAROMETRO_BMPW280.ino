#include <Adafruit_BMP280.h>
#include <Wire.h>

Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(9600);
  if (!bmp.begin(0x76)) {
    Serial.println(F("ERROR"));
    //while (1);
  }
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Modo de operación */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Presion oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtrado. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Tiempo Standby. */
}

void loop(){
  delay(1000);
  Serial.print(F("Temp = "));
  Serial.print(bmp.readTemperature());
  Serial.println(" C");
  Serial.print(F("Pres = "));
  Serial.print(bmp.readPressure()/100);
  Serial.println(" hPa");
  Serial.print(F("Altitud = "));
  Serial.print(bmp.readAltitude(1005));
  Serial.println(" m");
  Serial.println();
}
