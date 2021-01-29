#include <SoftwareSerial.h>
#include <TinyGPS.h>

TinyGPS gps;

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);

}

void loop()
{

}

while(!waitGPS){
    bool waitGPS = false;  //Funcion para saber si hay dato_gpss
   
   // Intentar recibir secuencia durante un segundo
   for (unsigned long start = millis(); millis() - start < 1000;)
   {
      while (Serial1.available())
      {
         char c = Serial1.read();  //Guarda dentro de c los valores que de el GPS
         if (gps.encode(c))  //Desodifica la nueva secuencia recibida
            waitGPS = true;
      }
   }
}

rtc.adjust(DateTime(get_date(TinyGPS &gps)));





String get_date(TinyGPS &gps)
{
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned long age;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  if (age == TinyGPS::GPS_INVALID_AGE)
    Serial.print("********** ******** ");
  else
  {
    String sz;
    sz = (String) year + ", " + (String) month + ", " + (String) day + ", " + (String) hour + ", " + (String) minute + ", " + (String) second;
    return sz;
  }
}
