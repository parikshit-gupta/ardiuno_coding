String name;
float raw_val=0;
float Tc=0;

void setup()
{
	Serial.begin(11600);
  	pinMode(12,OUTPUT);
  	pinMode(10,OUTPUT);
  	pinMode(11,OUTPUT);
  	pinMode(A2, INPUT);
}

void loop()
{
  // checking for relation between temprature output and RawData recived from sensor.
  raw_val=analogRead(A2);
  Serial.print("raw value: ");
  Serial.println(raw_val);
  
  //TEMP OUTPUT
  Tc=((165.0*raw_val)-16820.0)/338.0;
  Serial.print("Temprature(in CElCIUS): ");
  Serial.println(Tc);
  
  if (Tc>=100)
  {
	digitalWrite(12, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    Serial.println("Temp too high, Abort!!");
  }
  if (Tc<100 && Tc>=60)
  {
	digitalWrite(12, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(10, LOW);
    Serial.println("Temp approaching permissible limit");
  }
  if (Tc < 60)
  {
	digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, HIGH);
    Serial.println("All good.");
  }
  
  delay(5000);
  
}