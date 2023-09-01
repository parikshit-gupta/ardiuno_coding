#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <SPI.h>
#define sealevelpressure_hpa 1013.25// this is the reference which will have to be known prior to testing the sensor to get accurate results.

Adafruit_BMP280 bmp_obj = Adafruit_BMP280();
float temp;
float pres;
float alti;
float real_alti;
void setup() {
  // put your setup code here, to run once:
  bmp_obj.begin();
  Serial.begin(9600);
  if (!bmp_obj.begin())
  {
    Serial.println("BMP sensor not found.");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  temp=bmp_obj.readTemperature();
  pres=bmp_obj.readPressure(); // returns pressure at current locaation in Pa.
  alti=bmp_obj.readAltitude(); // returns altitute in meters assuming sea level presure to be 1013.25hpa if not specified.
  real_alti = bmp_obj.readAltitude(sealevelpressure_hpa); // takes sealevel pressure in hpa as argument. hpa-hectopascal(10^-2)

  /*
  Serial.print("temprature: ");
  Serial.print(temp);
  Serial.print(",");

  Serial.print("pressure: "); 
  Serial.print(pres);
  Serial.print(",");

  Serial.print("altitude: ");
  Serial.print(alti);
  Serial.print(",");
  
  Serial.print("real-altitude: ");
  Serial.print(real_alti);
  Serial.println(",");*/

  Serial.print(temp);
  Serial.print(",");
  Serial.print(pres);
  Serial.print(",");
  Serial.print(alti);
  Serial.print(",");
  Serial.print(real_alti);
  Serial.println(",");
  delay(5000);
}
