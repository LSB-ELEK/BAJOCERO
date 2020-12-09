#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);


void setup(void) 
{
  Serial.begin(9600);
  Serial.println("Light Sensor Test"); Serial.println("");
  
}


void loop(void) 
{  
  
  sensors_event_t event;
  tsl.getEvent(&event);
 
 
  if (event.light)
  {
    Serial.print(event.light); Serial.println(" luz");
  }
  else
  {
   //Puede ser que el sensor se sature (Luz = 0) por si pasa eso
    Serial.println("Sensor overload");
  }
  delay(250);
}
