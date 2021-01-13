int analogApin = 0;
int LuzUV;
  
void setup() 
{
  pinMode(analogApin, INPUT);
  Serial.begin(9600);
  Serial.println("Flux");
}
 
void loop() 
{
  LuzUV = analogRead(analogApin);
  Serial.print(" Nivel UV: ");
  Serial.print(LuzUV);
  delay(200);
}
