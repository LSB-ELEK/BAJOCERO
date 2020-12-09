

#include "SD.h"
#include"SPI.h"

const int periodo = 5000;
unsigned long ant_millis=0;

const int CSpin = 4;

String datoString =""; 
float sensorReading1 = 2316.21; 
float sensorReading2 = 6789.1; 
float sensorReading3 = 32.93; 
int contador = 1;

bool primera = 1;
String infoCol = String("Contador") + "," + String("dato1") + "," + String("dato2") + "," + String("dato3");

File sensorData;



void setup(){

  Serial.begin(9600);
  Serial.print("Initializando tarjeta SD...");

  if (!SD.begin(CSpin)) {
    Serial.println("Tarjeta fallida, o no encontrada.");
    while(1);
  }
  Serial.println("Tarjeta iniciada.");
  
}



void loop(){
  if((millis()-ant_millis)>periodo){    //cada (periodo) escribir el siguiente numero
        ant_millis=millis();
    datoString =String(contador) + "," + String(sensorReading1) + "," + String(sensorReading2) + "," + String(sensorReading3);
    guardarDatos(); 
  }

}



void guardarDatos(){ 

  sensorData = SD.open("datos.csv", FILE_WRITE);
    if (primera){
      sensorData.println(infoCol);
      Serial.println(infoCol);
      primera = 0;
    }
    if (sensorData){
      sensorData.println(datoString);
      Serial.println(datoString );
      sensorData.close();
    }
  contador++;
  
}
