String name;

void setup()
{
	Serial.begin(9600);
  	pinMode(12,OUTPUT);
  	pinMode(10,OUTPUT);
  	pinMode(11,OUTPUT);
}

void loop()
{
  Serial.println("enter the LED to glow up");
  while (Serial.available()==0){
  }
  name=Serial.readString();
  if (name=="RED")
  {
	digitalWrite(12, HIGH);
    delay(1000);
    digitalWrite(12,LOW);
  }
  if (name=="YELLOW")
  {
	digitalWrite(10, HIGH);
    delay(1000);
    digitalWrite(10,LOW);
  }
  if (name=="GREEN")
  {
	digitalWrite(11, HIGH);
    delay(1000);
    digitalWrite(11,LOW);
  }
}