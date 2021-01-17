  #include <DHT.h>

  #define DHTTYPE DHT22
  const int DHTPin = 5;
  
  DHT dht (DHTPin, DHTTYPE);

    void setup(){
      Serial.begin(9600);
      dht.begin();
          }

    void loop(){
        Serial.println(dht22());  
      }


String dht22(){
    String h = "";
    String t = "";
    h = dht.readHumidity();
    t = dht.readTemperature();
    String r = h + ", " + t + ", ";
    return r;
}

/*
    void (dht22){
        float h = dht.readHumidity();
        float t = dht.readTemperature();

        Serial.print("Humedad = ");
        Serial.print(h);
        Serial.print("%")
        Serial.print("Temp = ");
        Serial.print(t);
  
   }
*/
