//blinking LED number of times user wants
int n;
int i=0;

void setup()
{
	Serial.begin(9600);
  	pinMode(12, OUTPUT);
}

void loop()
{
  Serial.println("enter the number of times you want LED to blink: ");
  while (Serial.available()==0){
  }
  n=Serial.parseInt();//for int and flost use parse and for strings use read
  for(i=0;i<n;i++){
    digitalWrite(12, 1);
    delay(200);
    digitalWrite(12,0);
    delay(200);
  }
}