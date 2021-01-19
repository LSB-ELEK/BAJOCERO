#include <Adafruit_BMP280.h>
#include <Wire.h>
#include <SPI.h>

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(9600);
  if (!bmp.begin()) {
    Serial.println("Error al iniciar BAROMETRO BMP280");
    while (1);
  }
}

void loop(){
    Serial.println(BMP280());
}

String BMP280(){
    String temperatura = "";
    String presion = "";
    String altitud = "";
    temperatura = bmp.readTemperature();
    presion = bmp.readPresure();
    altitud = bmp.readAltitude(1013.25);
    String b = temperatura + ", " + presion", " + altitud ", ";
    return b;
  }
  
