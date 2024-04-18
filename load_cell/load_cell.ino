#include "HX711.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <SD.h>
#define DOUT 3
#define CLK 5
const int chipSelect = 4;
HX711 scale;

float weight;
float calibration_factor = -211.101165;  // for me this value works just perfect 419640


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1  // Reset pin # (or -1 if sharing Arduino reset pin)


void setup() {
  Serial.begin(9600);
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1)
      ;
  }
  Serial.println("card initialized.");

  scale.begin(DOUT, CLK);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");
  scale.set_scale();
  scale.tare();                             //Reset the scale to 0
  long zero_factor = scale.read_average();  //Get a baseline reading
  Serial.print("Zero factor: ");            //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);

  delay(2000);
}
void loop() {
  scale.set_scale(calibration_factor);  //Adjust to this calibration factor
  scale.set_offset(263862);
  Serial.print("Reading: ");
  weight = scale.get_units(5);
  if (weight < 0) {
    weight = 0.00;
  }
  //Serial.print(scale.get_units(), 2);
  // Serial.print(" lbs"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
  Serial.print("gram:");
  Serial.print(weight);
  Serial.print(" g");

  Serial.println();
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(weight);
    dataFile.close();
    // print to the serial port too:
    Serial.println(weight);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
  delay(10);
}