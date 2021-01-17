#include <Wire.h>
#include "Adafruit_CCS811.h"

Adafruit_CCS811 ccs;


void setup() {
  Serial.begin(9600);
  
  
  if(!ccs.begin()){
    Serial.println("Fallo al iniciar Sensor");                  
  }

}

void loop() {
  Serial.println(CCS811());

}

String CCS811(){
    String z="";
    String co2="";
    String tvoc="";
    if(ccs.available()){
        if(!ccs.readData()){
            co2 = ccs.geteCO2();              
            tvoc = ccs.getTVOC();
            z = co2 + ", " + tvoc + ", ";
        }
        else{
            Serial.println("Error en la lectura de datos!!");
            co2 = "---";                        //EN CASO DE ERROR DE LECTURA IMPRIME "---" EN LUGAR DEL DATO
            tvoc = "---";
            z = co2 + ", " + tvoc + ", ";
        }
    }else{
        co2 = "xxx";
        tvoc = "xxx";                           //EN CASO DE FALLO DEL SENSOR IMPRIME "xxx" EN LUGAR DEL DATO
        z = co2 + ", " + tvoc + ", ";
    }
    return z;
}
