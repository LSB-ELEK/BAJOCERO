#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

void setup () {
  Serial.begin(9600);
  rtc.begin(); //Inicializamos el RTC
  Serial.println("Estableciendo Hora y fecha...");
  rtc.adjust(DateTime((__DATE__), (__TIME__)));
  Serial.println("DS1307 actualizado con la hora y fecha que se compilo este programa:");
  Serial.print("Fecha = ");
  Serial.print(__DATE__);
  Serial.print("  Hora = ");
  Serial.println(__TIME__);
}

void printDate(DateTime date)
{
  Serial.print(date.year(), DEC);
  Serial.print('/');
  Serial.print(date.month(), DEC);
  Serial.print('/');
  Serial.print(date.day(), DEC);
  Serial.print(" (");
  Serial.print(") ");
  Serial.print(date.hour(), DEC);
  Serial.print(':');
  Serial.print(date.minute(), DEC);
  Serial.print(':');
  Serial.print(date.second(), DEC);
  Serial.println();
}

void loop() {
  // Obtener fecha actual y mostrar por Serial
  DateTime now = rtc.now();
  printDate(now);

  delay(3000);
}
