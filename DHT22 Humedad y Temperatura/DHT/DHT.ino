/*NECESARIA LA DESCARGAR DE LA LIBRERIA ADAFRUIT SENSOR MASTER
DESCARGA: https://github.com/adafruit/Adafruit_Sensor */


#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTTYPE DHT22 //MODELO DEL SENSOR A UTILIZAR
const int DHTPin = 5;

DHT dht(DHTPin, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,20,4);
void setup(){

  lcd.init();
  lcd.backlight();
  dht.begin();
}

void loop(){

  float h = dht.readHumidity();
  float t = dht.readTemperature(); // dht.readTemperature(true); LEER EN FAHRENHEIT
  lcd.setCursor(0,0);
  lcd.print("Humedad = ");
  lcd.print(h);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("Temp = ");
  lcd.print(t);
  lcd.print("\337C");
  delay(2000);
  lcd.clear();
}
