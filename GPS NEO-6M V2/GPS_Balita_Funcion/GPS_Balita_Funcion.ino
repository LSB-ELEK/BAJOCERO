//Incluimos las librerias necesarias

#include <TinyGPS.h> //Nos da exactamente las cordenadas de forma simple


 
TinyGPS gps;


String dato_gps;



void setup()
{
   Serial.begin(9600);  // ordenador--> Arduino
   Serial1.begin(9600); // arduino -->> GPS

}
 
void loop()
{
  Serial.println(GPS());
  delay(1000);
} 



String GPS(){
   
   bool newData = false;  //Funcion para saber si hay dato_gpss
   
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

      //Guardamos en el String todos los dato_gps
      dato_gps=(
      String(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6) + String(" ,  ") + //Latitud
      String(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6) +  String(" ,  ") + //Longitud
      String(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites()) + String(" ,  ") + //Cantidad de satelites
      String(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop()) + String(" ,  ") + //Precision de la informacion
      String(age) + String(" ,  ")
      );
      
     }else
       {
          dato_gps = String("---") + String(" ,  ") + String("---") + String(" ,  ") + String("---") + 
          String(" ,  ") + String("---") + String(" ,  ") + String("---") +String(" ,  ");
       }
   
 return dato_gps;
}
