int analogApin = 0;
int UV;
  
void setup() 
{
  pinMode(analogApin, INPUT);
  Serial.begin(9600);
  Serial.println("Flux");
}
 
void loop() 
{
 LuzUV;
}

void LuzUV()
{
  UV = analogRead(analogApin);
  Serial.print(" Nivel UV: ");
  Serial.print(UV);
  delay(200);
}
