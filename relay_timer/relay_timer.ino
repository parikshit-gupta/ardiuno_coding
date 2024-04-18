int readpin = 6;
int relaypin = 7;
int val = 0;
int time = 0;

void setup() {
  pinMode(6, INPUT);
  pinMode(10, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(readpin);
  int curr_time = millis();
  if (val == 1) {
    while (time <= 10) {
      time=millis()-curr_time;
      Serial.println(time);
      delay(1000);
    }
    digitalWrite(relaypin, HIGH);
  }
  delay(50);
}
