#include<Wire.h>
#include<Adafruit_BNO055.h>
#include<Adafruit_Sensor.h>
#include<math.h>

Adafruit_BNO055 myIMU= Adafruit_BNO055();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  myIMU.begin();
  delay(1000);
  myIMU.setExtCrystalUse(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t system, gyr, accel, mg=0;
  myIMU.getCalibration(&system, &gyr, &accel, &mg);

  imu::Quaternion qut= myIMU.getQuat();
  imu::Vector<3> lin_acc=myIMU.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);

  Serial.print(qut.w());
  Serial.print(',');
  Serial.print(qut.x());
  Serial.print(',');
  Serial.print(qut.y());
  Serial.print(',');
  Serial.print(qut.z());
  Serial.print(',');
  Serial.print(lin_acc.x());
  Serial.print(',');
  Serial.print(lin_acc.y());
  Serial.print(',');
  Serial.print(lin_acc.z());
  Serial.print(',');
  Serial.print(system);
  Serial.print(',');
  Serial.print(gyr);
  Serial.print(',');
  Serial.print(accel);
  Serial.print(',');
  Serial.println(mg);

  delay(1000);
}
