#include <SPI.h>                    // Lobreria para Conexion MOSI
#include <SD.h>                     // Libreria para la SD

const int chipSelect = 4;           // pin CS del modulo SD
const int periodo = 1000;
unsigned long ant_millis=0;
unsigned long dato_a_guardar=0;

File archivo;     //comando File para gestionar los archivos || <<archivo>>  nombre para los comandos


void setup() {
   Serial.begin(9600);
  while (!Serial) {                 // Espera a iniciar el puerto serial
    ;                               // Solo es necesario si se usa el puerto serie
  }
   Serial.print("Inicializando tarjeta SD ....");

  // Ver si inicializa la tarjeta
  if (!SD.begin(chipSelect)) {      // Si no inicia la tarjeta muestra el error
    Serial.println("Tarjeta fallida, o no encontrada.");
    while (1);                      // En casop de fallar la tarjeta bloquea el programa
  }
  Serial.println("Tarjeta inicializada.");  

}

void loop() {
  if((millis()-ant_millis)>periodo){    //cada (periodo) escribir el siguiente numero
        ant_millis=millis();
    dato_a_guardar++;
    //Serial.print("Dato fuera: ");Serial.println(dato_a_guardar);

    
    archivo = SD.open("datos.txt", FILE_WRITE);   //abrir el archivo en modo escritura
     
    if(archivo){
      archivo.println(dato_a_guardar);  // comando para escribir en el archivo
      archivo.close();                  // cerrar el archivo para poder abrir otro
      Serial.print("Dato en archivo: ");Serial.println(dato_a_guardar); // imprime en el serial el dato del archivo
    }else{
      Serial.println("Error al escribir");  //en caso de no poder escribir indica el error
    }
  }

}
