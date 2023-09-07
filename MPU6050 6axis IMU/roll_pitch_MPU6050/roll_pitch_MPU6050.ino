#include <Wire.h>
#include <MPU6050.h>
#include <math.h>

MPU6050 mpu;

float rollA;
float pitchA;
float yawA;

float rollG;   //about x axis
float pitchG;  // about z axis
float yawG;    // about y axis

float rollF;
float pitchF;
float yawF;
float pitchN;
float rollN;
float pitchO;
float rollO;

float dt;
unsigned long millisold;

void setup() {
  Serial.begin(115200);

  Wire.begin();

  mpu.initialize();

  // You can calibrate the sensor by uncommenting these lines and following the calibration procedure.
  mpu.CalibrateGyro();
  mpu.setDMPEnabled(true);

  //millis returns the time in milli sec from when the ardiuno board started.
  millisold=millis();
}

void loop() {
  // Read raw accelerometer and gyro data
  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Convert raw values to actual values in m/s^2 and degrees/s
  float accelX = ax / 16384.0;  // sensitivity scale factor for accelerometer
  float accelY = ay / 16384.0;
  float accelZ = az / 16384.0;

  rollA = ((atan2(accelY, accelZ))*180)/3.14; // rotation about the x axis (of the sensor) x-y plane is the sensors plane
  pitchA = ((atan2(accelX, accelZ))*180)/3.14;  // rotation about the y axis (of the sensor)

  rollN=.9*(rollN)+(rollA)*.1;
  pitchN=.9*(pitchN)+(pitchA)*.1;


  float gyroX = gx / 131.0;  // sensitivity scale factor for gyroscope
  float gyroY = gy / 131.0;
  float gyroZ = gz / 131.0;

  dt=(millis()-millisold)/1000.0;
  millisold=millis();

  rollG = rollG + gyroX * dt;
  yawG = yawG + gyroZ * dt;
  pitchG = pitchG + gyroY * dt;

  //complimentry filter

  rollF = .9*(rollG) +.1*(rollN);
  pitchF = .9*(pitchG) +.1*(pitchN);

  //printing final filtered data on the serial monitor

  Serial.print(rollF);
  Serial.print(',');
  Serial.print(pitchF);
  Serial.print(',');
  Serial.print(rollA);
  Serial.print(',');
  Serial.println(pitchA);
  
  delay(100);  // Adjust the delay based on your requirements
}