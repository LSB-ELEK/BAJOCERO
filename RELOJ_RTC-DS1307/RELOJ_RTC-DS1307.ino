#include <RTClib.h>
#include <Wire.h>

#define LED 3

int hora;
int mins;
int seg;
int ano;
int mes; 
int dia;


RTC_DS1307 rtc;



void setup () {
  Serial.begin(9600);
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  

}

void loop () {
  Serial.println(RTC());
    delay(100);
}

String RTC(){
    String X;
    DateTime now = rtc.now();
    String shora;
    int hora = now.hour();
    int mins = now.minute();
    int seg = now.second();
    int dia = now.day();
    int mes = now.month();
    int ano = now.year();
    
    shora = (String) hora +"" ;
Serial.println(shora);
    return X;
}
