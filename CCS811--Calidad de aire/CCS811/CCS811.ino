/*
    
        TVOC(Total Volatile Organic Compounds) ---->>> Se mide en   ppb
        
    Los compuestos orgánicos son sustancias químicas que contienen 
    carbono y se encuentran en todos los elementos vivos. 
    Los compuestos orgánicos volátiles, a veces llamados VOC, o COV, 
    se convierten fácilmente en vapores o gases.

============================================================================    
    
        CO2() ---->>> Se mide en ppm(parts per million)

============================================================================

        Temperatura ---->>> Se mide en Celsius

    Mide los cambios de temperatura no la temperatura por eso mismo es bastante inexacto
    dado que hay que calibrarlo antes de medir

    .setTempOffset()          //funcion para calibrar la temperatura
    .calculateTemperature()   //funcion leer temperatura
      
*/

#include <Wire.h>
#include "Adafruit_CCS811.h"


Adafruit_CCS811 ccs;

void setup() {
  Serial.begin(9600);
  
  
  if(!ccs.begin()){
    Serial.println("Fallo al iniciar Sensor");    
  while(1);                             // bloquea el arduino
  }

                     
}

void loop() {
  if(ccs.available()){
    if(!ccs.readData()){
      Serial.print("CO2: ");
      Serial.print(ccs.geteCO2());      //Comando de CO2
      Serial.print("ppm, TVOC: ");
      Serial.print(ccs.getTVOC());      //Comando de TVOC
      Serial.println("ppb");
    }
    else{
      Serial.println("Error en la lectura de datos!!");
      while(1);
    }
  }
  delay(500);
}
