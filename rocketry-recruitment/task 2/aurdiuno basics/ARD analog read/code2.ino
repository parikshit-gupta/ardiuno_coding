int readpin=A3;
int val=0;
int delaytime = 100;

void setup()
{
  pinMode(A3, INPUT);
  Serial.begin(9600);//sets up the serial monitor with refresh rate of 9600
}

void loop()
{
	val = analogRead(readpin);
 //Serial.print(val);//prints val on the serial monitor
  	Serial.println(val); //prints val in a new line every time
  delay(delaytime);
}