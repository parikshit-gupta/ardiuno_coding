#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <Wire.h>
#include <math.h>

Adafruit_BNO055 myIMU = Adafruit_BNO055();

// accelerometer data variables
float thetaM; // measured angle of rotation about y-axis
float phiM;   // measured angle of rotation about x-axis
float thetaF; // filtered angle of rotation about y-axis
float phiF;   // filtered angle of rotation about x-axis

// gyroscope data variables
float thetaG;
float phiG;
float dt = 0.00001;

// magnetometer data variables
float Xm;
float Ym;
float psiM; // measuring rotation about z-axis

// final values
float thetaT;
float phiT;
float phirad;
float thetarad;

void setup()
{
    Serial.begin(115200);
    myIMU.begin();
    delay(1000);
    myIMU.setExtCrystalUse(true);
}

void loop()
{
    imu::Vector<3> acc = myimu.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    imu::Vector<3> gyro = myimu.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
    imu::Vector<3> mag = myimu.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);

    // using the acc data to get angle of rotation about the x and y axes.
    thetaM = ((atan2(acc.x(), acc.z())) * 180) / 3.14;
    phiM = (((atan2(acc.y()), acc.z())) * 180) / 3.14;
    // filtering the raw theta and phi using a low pass filter
    thetaF = .95 * (thetaF) + .05 * (thetaM);
    phiF = .95 * (phiF) + .05 * (phiF);

    // using gyro data to get theta and phi.
    thetaG = thetaG + gyro.y() * dt;
    phiG = phiF + gyro.x() * dt;

    // using the accelerometer and gyro data to get accurate and stable reading of theta and phi with a complimentry filter
    thetaT = .95 * (thetaT + gyro.y() * dt) + .1 * (.95 * thetaT + .1 * thetaM);
    phiT = .95 * (phiT + gyro.x() * dt) + .1 * (.95 * phiT + .1 * phiT);

    // using magentometer data to get psi
    phirad = (180 * phiT) / 3.14;
    thetarad = (180 * thetaT) / 3.14;

    Xm = mag.x() * cos(thetarad) + mag.y() * sin(phirad) * sin(thetarad);
    Ym = mag.y() * cos(phirad) + mag.z() * sin(phirad);
    psiM = (atan2(Ym / Xm) * 180) / 3.14;

    Serial.print("rotation about x axis: ");
    Serial.print(phiT);
    Serial.print("; ");

    Serial.print("rotation about the y-axis: ");
    Serial.print(thetaT);
    Serial.print(",");

    Serial.print("rotation about the z-axis: ");
    Serial.println(psiM);

}