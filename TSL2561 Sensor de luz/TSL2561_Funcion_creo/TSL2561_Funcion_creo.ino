#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

String luz;

void setup(void) 
{
  Serial.begin(9600);
  Serial.println("Light Sensor Test"); Serial.println("");
  
}


void loop(void) 
{  
 
}

  
String Luz()
 {
 
  sensors_event_t event;
  tsl.getEvent(&event);
 
  if (event.light)
   {
     String luz = "";
     Serial.print(event.light); Serial.println(" luz");
     luz = event.light;
   }
    else
     {
     Serial.println("Sensor overload");
     }
  return luz;
}
