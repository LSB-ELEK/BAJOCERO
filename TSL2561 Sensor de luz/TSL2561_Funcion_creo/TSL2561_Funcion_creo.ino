#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

String lux;
int luz;

void setup(void) 
{

  
}


void loop(void) 
{  
 
}

  
String Luz()
 {
 
  sensors_event_t event;
  tsl.getEvent(&event);
  luz = event.light;
  
  if (event.light)
   {
     lux= (String(" ,  ") + String (luz));
  
   }
    else
     {
      lux = ( String(" , ") + String("---"));
     }
 return lux;
}
