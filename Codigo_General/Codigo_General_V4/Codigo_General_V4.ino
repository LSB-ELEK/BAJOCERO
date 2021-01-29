#include <SD.h>
#include <SPI.h>
#include <RTClib.h>
#include <Wire.h>
#include <TinyGPS.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_CCS811.h>
#include <DHT.h>
#define DHTTYPE DHT22
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
#include <LiquidCrystal_I2C.h>


int analogApin = 0;
bool waitGPS = false;

  int GPSyear;
  byte GPSmonth, GPSday, GPShour, GPSminute, GPSsecond;

File LOG_DATA;
RTC_DS1307 rtc;
TinyGPS gps;
Adafruit_BMP280 bmp;
Adafruit_CCS811 ccs;
const int DHTPin = 5;
DHT dht (DHTPin, DHTTYPE);
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);
LiquidCrystal_I2C LCD(0x27, 16, 2);

const int CSpin = 53;

String First_Line = "FECHA, HORA, LATITUD, LONGITUD, SATELITES, PRECISION, AGE, TEMPERATURA_BMP, PRESION_BMP, ALTITUD_BMP, CO2, TVOC, HUMEDAD_DHT, TEMPERATURA_DHT, LUZ_TSL, LUZ_UV";
bool first_line = 0;

String datos = "";
String dato_gps = "";

long ant_millis=0;
long ant_millis_lcd=0;

unsigned int contador_datos = 1;
unsigned int contador_archivos = 1;
bool lcd_apagado = false;

String ARCHIVO = "dato_1.csv";


void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  SD.begin(CSpin);
  rtc.begin();
  bmp.begin(0x76);
  ccs.begin();
  dht.begin();
  //LCD.begin();
  LCD.noBacklight();
  LCD.noDisplay();
  while(!waitGPS){
      bool waitGPS = false;  //Funcion para saber si hay dato_gpss
     
     // Intentar recibir secuencia durante un segundo
      for (unsigned long start = millis(); millis() - start < 1000;)
      {
          while (Serial1.available())
          {
             char c = Serial1.read();  //Guarda dentro de c los valores que de el GPS
             if (gps.encode(c))  //Desodifica la nueva secuencia recibida
                waitGPS = true;
          }
      }
  }
  get_date(gps);
  rtc.adjust(DateTime(GPSyear, GPSmonth, GPSday, GPShour, GPSminute, GPSsecond));
  
}

void loop() {

  if(millis()-ant_millis>30000){
    ant_millis = millis();
  datos = RTC() + GPS() + BAROMETRO() + CCS811() + dht22() + TSL() + LuzUV() ;
  SDdatalogger(datos);
  //LED();
  //lcd();
  Serial.print("Nº Archivo: ");Serial.println(ARCHIVO);
  Serial.print("Nº Dato: ");Serial.println(contador_datos);
  contador_datos++;

  }
  if(contador_datos > 100){
      contador_archivos++;
      ARCHIVO = "dato_" + (String) contador_archivos + ".csv";
      contador_datos = 1;
  }
  if((millis()-ant_millis_lcd>5000)&&(lcd_apagado==false)){
    ant_millis_lcd = millis();
    LCD.noBacklight();
    LCD.noDisplay();
    lcd_apagado = true;
  }
}

void SDdatalogger(String x){
    LOG_DATA = SD.open(ARCHIVO, FILE_WRITE);
        
        if(!first_line){
            LOG_DATA.println(First_Line);
            first_line++;
        }
        if(LOG_DATA){
            LOG_DATA.println(x);
            Serial.println(x);
            LOG_DATA.close();
        }
    
}

String RTC(){
    String X;
    DateTime now = rtc.now();
    int hora = now.hour();
    int mins = now.minute();
    int seg = now.second();
    int dia = now.day();
    int mes = now.month();
    int ano = now.year();
    
    X = (String) dia + "/" + (String) mes + "/" + (String) ano + ", " + (String) hora + 
    ":" + (String) mins + ":" + (String) seg + ", ";
    
    return X;
}

String GPS(){
   
   bool newData = false;  //Funcion para saber si hay dato_gpss
   
   // Intentar recibir secuencia durante un segundo
   for (unsigned long start = millis(); millis() - start < 1000;)
   {
      while (Serial1.available())
      {
         char c = Serial1.read();  //Guarda dentro de c los valores que de el GPS
         if (gps.encode(c))  //Desodifica la nueva secuencia recibida
            newData = true;
      }
   }
 
   if (newData)
    {
      float flat, flon;   //Variables de latitud y longitud
      unsigned long age;
      gps.f_get_position(&flat, &flon, &age);

      //Guardamos en el String todos los dato_gpss
      dato_gps=(
      String(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6) + String(", ") + //Latitud
      String(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6) +  String(", ") + //Longitud
      String(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites()) + String(", ") + //Cantidad de satelites
      String(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop()) + String(", ") + //Precision de la informacion
      String(age) + String(", ")
      );
      
     }else
       {
          dato_gps = String("---") + String(", ") + String("---") + String(", ") + String("---") + 
          String(", ") + String("---") + String(", ") + String("---") +String(", ");
       }
   
 return dato_gps;
}

String BAROMETRO(){
    String temperatura = "";
    String presion = "";
    String altitud = "";
    temperatura = bmp.readTemperature();
    presion = bmp.readPressure()/100;
    altitud = bmp.readAltitude(1013.25);
    String b = temperatura + ", " + presion + ", " + altitud + ", ";
    return b;
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

String dht22(){
    String h = "";
    String t = "";
    h = dht.readHumidity();
    t = dht.readTemperature();
    String r = h + ", " + t + ", ";
    return r;
}

String TSL(){
  String lux;
  int luz;
  sensors_event_t event;
  tsl.getEvent(&event);
  luz = event.light;
  
  if (event.light)
   {
     lux= String (luz) + ", ";
  
   }
    else
     {
      lux = String("---") + ", ";
     }
 return lux;
}

String LuzUV()
{
  String UVIndex = "0";
  int sensorValue = 0;
  
  sensorValue = analogRead(A0);
  int voltage = (sensorValue * (5.0 / 1023.0))*1000;
  
  if(voltage<50)
  {
    UVIndex = "0";
  }else if (voltage>50 && voltage<=227)
  {
    UVIndex = "0";
  }else if (voltage>227 && voltage<=318)
  {
    UVIndex = "1";
  }
  else if (voltage>318 && voltage<=408)
  {
    UVIndex = "2";
  }else if (voltage>408 && voltage<=503)
  {
    UVIndex = "3";
  }
  else if (voltage>503 && voltage<=606)
  {
    UVIndex = "4";
  }else if (voltage>606 && voltage<=696)
  {
    UVIndex = "5";
  }else if (voltage>696 && voltage<=795)
  {
    UVIndex = "6";
  }else if (voltage>795 && voltage<=881)
  {
    UVIndex = "7";
  }
  else if (voltage>881 && voltage<=976)
  {
    UVIndex = "8";
  }
  else if (voltage>976 && voltage<=1079)
  {
    UVIndex = "9";
  }
  else if (voltage>1079 && voltage<=1170)
  {
    UVIndex = "10";
  }else if (voltage>1170)
  {
    UVIndex = "11";
  }
  return UVIndex;
}

void LED(){
    digitalWrite(3, HIGH);
    //tone(4, 5000, 1000);
    delay(1000);
    digitalWrite(3, LOW);
}

void lcd(){
  
  LCD.backlight();
  LCD.display();
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("N");LCD.print((char)223);LCD.print(" ARCHIVO: ");LCD.print(contador_archivos);
  LCD.setCursor(0, 1);
  LCD.print("N");LCD.print((char)223);LCD.print(" DATO: ");LCD.print(contador_datos);
  ant_millis_lcd = millis();
  lcd_apagado = false;
  
}

void get_date(TinyGPS &gps){
  
  byte hundredths;
  unsigned long age;
  gps.crack_datetime(&GPSyear, &GPSmonth, &GPSday, &GPShour, &GPSminute, &GPSsecond, &hundredths, &age);
  if (age == TinyGPS::GPS_INVALID_AGE)
    Serial.print("********** ******** ");
  else
  {
    gps.crack_datetime(&GPSyear, &GPSmonth, &GPSday, &GPShour, &GPSminute, &GPSsecond);
  }
}
