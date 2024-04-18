#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP280.h>
#include <SPI.h>
#include <SD.h>
const int chipselect = 4;
float alti1;
float alti;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1  // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_BMP280 bmp_obj = Adafruit_BMP280();
void setup() {
  bmp_obj.begin();
  SD.begin(chipselect);
  Serial.begin(9600);
  Serial.println("card initialized.");
  alti1=bmp_obj.readAltitude(); //first reading
  delay(2000);
}
void loop() {
  alti=bmp_obj.readAltitude()-alti1; // returns altitute in meters assuming sea level presure to be 1013.25hpa if not specified.
  Serial.println();
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(alti);
    dataFile.close();
    // print to the serial port too:
    Serial.println(alti);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
  delay(50);
}