//measuring distances using HC-SR04 sensor

int echo_val;
float travelTime;
float raw_val=0;
float Tc;
float Tk;
float speed_sound;
float distance;

void setup(){
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(11, INPUT);
  pinMode(A2, INPUT);
}

void loop(){
  //creating the ultrasonic signal
  
  digitalWrite(12, LOW);
  delayMicroseconds(10);
  digitalWrite(12, HIGH);
  delayMicroseconds(10);
  digitalWrite(12, LOW);
  delayMicroseconds(10);
  
  //recieving signal produced by echo
  
  travelTime=pulseIn(11, HIGH);
  Serial.print("travelTime: ");
  Serial.println(travelTime);
  
  //calculating speed of sound using temp measurements
  
  raw_val=analogRead(A2);
  Tc=((165.0*raw_val)-16820.0)/338.0;
  Tk = Tc + 273.0;
  Serial.print("Temprature: ");
  Serial.println(Tk);
  
  speed_sound = (10.0*(sqrt(35.0*Tk)))/3.0;
  Serial.print("speed of sound is: ");
  Serial.println(speed_sound);
  
  //calculating distance from obstacle
  
  distance = (speed_sound*travelTime)/2000000.0;
  Serial.print("distance is: ");
  Serial.println(distance);
  Serial.println(" ");
  delay(10000); 
}
/*NOTE: the tinkercad simulator does not simulate 
change in speed of sound with temprature thus the 
travel time does not change with change in temp.*/