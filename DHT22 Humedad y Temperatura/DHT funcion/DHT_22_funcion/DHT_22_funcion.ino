  #include <DHT.h>

  #define DHTYTPE DHT22
  const int DHTPin = 5;
  
  DHT dht (DHTPin, DHTTYPE);

    void setup(){
      Serial.begin(9600);
      dht.begin;
      if(!dht.begin){
        Serial.println("Fallo al iniciar DHT22")
        }
          }

    void loop(){
        Serial.println(dht22);  
      }

    void (dht22){
        float h = dht.readHumidity();
        float t = dht.readTemperature();

        Serial.print("Humedad = ");
        Serial.print(h);
        Serial.print("%")
        Serial.print("Temp = ");
        Serial.print(t);
      }
