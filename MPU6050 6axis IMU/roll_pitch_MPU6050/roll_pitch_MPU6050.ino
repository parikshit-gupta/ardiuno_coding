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
float dt = .01;

float rollF;
float pitchF;
float yawF;

void setup() {
  Serial.begin(9600);

  Wire.begin();

  mpu.initialize();

  // You can calibrate the sensor by uncommenting these lines and following the calibration procedure.
  mpu.CalibrateGyro();
  mpu.setDMPEnabled(true);
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

  rollA = ((atan2(accelZ, accelY))*180)/3.14;
  pitchA = ((atan2(accelX, accelY))*180)/3.14;

  float gyroX = gx / 131.0;  // sensitivity scale factor for gyroscope
  float gyroY = gy / 131.0;
  float gyroZ = gz / 131.0;

  rollG = rollG + gyroX * dt;
  yawG = yawG + gyroY * dt;
  pitchG = pitchG + gyroZ * dt;

  //complimentry filter

  rollF = .95*(rollF + gyroX*dt) +.1*(.95*rollF+.1*rollA);
  pitchF = .95*(pitchF + gyroY*dt) +.1*(.95*pitchF+.1*pitchA);


  // Print the sensor data
  Serial.print("Accel (m/s^2): ");
  Serial.print(accelX);
  Serial.print("\t");
  Serial.print(accelY);
  Serial.print("\t");
  Serial.print(accelZ);
  Serial.print("\t");

  Serial.print("Gyro (deg/s): ");
  Serial.print(gyroX);
  Serial.print("\t");
  Serial.print(gyroY);
  Serial.print("\t");
  Serial.print(gyroZ);
  Serial.print('\t');

  Serial.print(rollF);
  Serial.print('\t');
  Serial.print(pitchF);
  Serial.print('\t');
  Serial.print(rollA);
  Serial.print('\t');
  Serial.println(pitchA);


  delay(1000);  // Adjust the delay based on your requirements
}