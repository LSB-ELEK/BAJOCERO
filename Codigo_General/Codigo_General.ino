#include "SD.h"
#include"SPI.h"
#include <RTClib.h>
#include <Wire.h>
#include <TinyGPS.h>

File LOG_DATA;
RTC_DS1307 rtc;
TinyGPS gps;

const int CSpin = 53;

String First_Line = "FECHA, HORA, ";
bool first_line = 0;

String datos = "";


void setup() {
  Serial.begin(9600);
  SD.begin(CSpin);
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

}

void loop() {
  datos = RTC();
  SDdatalogger(datos);
  delay(1000);

}

void SDdatalogger(String x){
    LOG_DATA = SD.open("data.csv", FILE_WRITE);
        
        if(!first_line){
            LOG_DATA.println(First_Line);
            first_line++;
        }
        if(LOG_DATA){
            LOG_DATA.println(x);
            Serial.println(x);
            LOG_DATA.close();
        }
    
}

String RTC(){
    String X;
    DateTime now = rtc.now();
    int hora = now.hour();
    int mins = now.minute();
    int seg = now.second();
    int dia = now.day();
    int mes = now.month();
    int ano = now.year();
    
    X = (String) dia + "/" + (String) mes + "/" + (String) ano + ", " + (String) hora + 
    ":" + (String) mins + ":" + (String) seg + ", ";
    
    return X;
}

String GPS(){
  String dato;
   
   bool newData = false;  //Funcion para saber si hay datos
   
   // Intentar recibir secuencia durante un segundo
   for (unsigned long start = millis(); millis() - start < 1000;)
   {
      while (Serial1.available())
      {
         char c = Serial1.read();  //Guarda dentro de c los valores que de el GPS
         if (gps.encode(c))  //Desodifica la nueva secuencia recibida
            newData = true;
      }
   }
 
   if (newData)
    {
      float flat, flon;   //Variables de latitud y longitud
      unsigned long age;
      gps.f_get_position(&flat, &flon, &age);

      //Guardamos en el String todos los datos
      dato=(
      String(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6) + String(" ,  ") + //Latitud
      String(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6) +  String(" ,  ") + //Longitud
      String(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites()) + String(" ,  ") + //Cantidad de satelites
      String(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop()) + String(" ,  ") + //Precision de la informacion
      String(age) + String(" ,  ")
      );
      
     }else
       {
          dato = String("---") + String(" ,  ") + String("---") + String(" ,  ") + String("---") + 
          String(" ,  ") + String("---") + String(" ,  ") + String("---") +String(" ,  ");
       }
   
 return dato;
}
