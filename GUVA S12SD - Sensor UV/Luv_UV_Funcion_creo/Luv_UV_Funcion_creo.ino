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
 
}

String LuzUV()
{
  String uv = "";
  uv = analogRead(analogApin);
  String p = uv + ", " ;
  return p;
}
