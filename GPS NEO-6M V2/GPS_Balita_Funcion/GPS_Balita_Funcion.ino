//Incluimos las librerias necesarias

#include <SoftwareSerial.h> //Para tener un segundo puerto serie
#include <TinyGPS.h> //Nos da exactamente las cordenadas de forma simple
 
TinyGPS gps;
SoftwareSerial softSerial(4, 3); //Asignar el puerto a los pines(Al GPS)

String Datos; //Aqui guarda todos los datos
String dato;

void setup()
{
   Serial.begin(9600);  // ordenador--> Arduino
   softSerial.begin(9600);  // arduino -->> GPS 
}
 
void loop()
{
}



String GPS(){
   
   bool newData = false;  //Funcion para saber si hay datos
   
   // Intentar recibir secuencia durante un segundo
   for (unsigned long start = millis(); millis() - start < 1000;)
   {
      while (softSerial.available())
      {
         char c = softSerial.read();  //Guarda dentro de c los valores que de el GPS
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
          String(" ,  ") + String("---") + String(" ,  ") + String("---") +String(" ,  ") +;
       }
   
 return dato;
}
