#include<Wire.h>
#include<Adafruit_Sensor.h>
#include<Adafruit_BNO055.h>
#include<utility/imumaths.h>

//creating sensor object
Adafruit_BNO055 myIMU = Adafruit_BNO055();

//variables to store raw data from sensors
int ax;
int ay;
int az;
int gx;
int gy;
int gz;
int mx;
int my;
int mz;


void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
    myIMU.begin();
    delay(1000);
    int8_t temp = myIMU.getTemp();
    myIMU.setExtCrystalUse(true);

}

void loop() {
  // put your main code here, to run repeatedly:

  // calibrating the 3 sensors
  uint8_t system, gyr, accel, mg=0;
  myIMU.getCalibration(&system, &gyr, &accel, &mg);

  //reading data from the sensors into a vector variable
  imu::Vector<3> acc = myIMU.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  imu::Vector<3> gyro = myIMU.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  imu::Vector<3> mag = myIMU.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);

  //reading raw data into components
  ax=acc.x();
  ay=acc.y();
  az=acc.z();
  gx=gyro.x();
  gy=gyro.y();
  gz=gyro.z();
  mx=mag.x();
  my=mag.y(); 
  mz=mag.z();  

}
