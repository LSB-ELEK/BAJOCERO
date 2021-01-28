
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

  {
      while (Serial1.available())
      {
         char c = Serial1.read();  //Guarda dentro de c los valores que de el GPS
         if (gps.encode(c))  //Desodifica la nueva secuencia recibida
            newData = true;
      }
   }
    if (newData){
        Datos = gps.time.hour();
        Serial.println(Datos);
        
         }
   

}
