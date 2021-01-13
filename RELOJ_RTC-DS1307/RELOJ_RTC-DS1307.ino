#include <RTClib.h>
#include <Wire.h>

#define LED 3

int hora;
int mins;
int seg;
int mes; 
int dia;

RTC_DS1307 rtc;

DateTime tiempo;

void setup () {
  Serial.begin(9600);
  rtc.begin();

  hora= tiempo.hour();
  mins= tiempo.minute();
  seg= tiempo.second();
  dia= tiempo.day();
  mes= tiempo.month();
}

void loop () 
{
    Serial.print("hora = ");
    Serial.print(hora);
    Serial.print(":");
    Serial.print(mins);
    Serial.print(":");
    Serial.print(seg);
    Serial.print("  Fecha = ");
    Serial.print(dia);
    Serial.print("/");
    Serial.print(mes);
    Serial.print("/");
    delay(1000);
}
