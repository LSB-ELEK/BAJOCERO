# include <SoftwareSerial.h>
# include <TinyGPS.h>

TinyGPS gps;
SoftwareSerial softSerial(4, 3); //Pines 3 y 4 de la placa Arduino

void setup()
{
Serial.begin(115200); //GPS-Arduino
softSerial.begin(9600); //Ordenador-Arduino
}


void loop() {
//Variables a leer del GPS
bool newData = false;
unsigned long chars;
unsigned short sentences, failed;
// Intentar recibir secuencia durante un segundo
for (unsigned long start = millis(); millis() - start < 1000;)
{
while (softSerial.available())
{
char c = softSerial.read();
if (gps.encode(c)) // Nueva secuencia recibida
newData = true;
}
}
if (newData)
{
float flat, flon;
unsigned long age;
gps.f_get_position(&flat, &flon, &age);
}
}
