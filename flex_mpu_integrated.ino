const int flexPin0 = A0; 
const int flexPin1 = A1; // Pin connected to voltage divider output
const int flexPin2 = A2; 
const int flexPin3 = A3; 
const int flexPin4 = A4; 

#include "I2Cdev.h"
#include "MPU6050.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

#define LED_PIN 13
bool blinkState = false;

MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() {
  Serial.begin(115200);
 
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
  #endif
  
  accelgyro.initialize();
  pinMode(flexPin0, INPUT);
  pinMode(flexPin1, INPUT);
  pinMode(flexPin2, INPUT);
  pinMode(flexPin3, INPUT);
  pinMode(flexPin4, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop(){
  int ADCflex0 = analogRead(flexPin0);
  int ADCflex1 = analogRead(flexPin1);
  int ADCflex2 = analogRead(flexPin2);
  int ADCflex3 = analogRead(flexPin3);
  int ADCflex4 = analogRead(flexPin4);

  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  ax >>= 7;
  ay >>= 7;
  az >>= 7;
  gx >>= 7;
  gy >>= 7;
  gz >>= 7;

  Serial.print(ADCflex0);
  Serial.print(",");
  Serial.print(ADCflex1);
  Serial.print(",");
  Serial.print(ADCflex2);
  Serial.print(",");
  Serial.print(ADCflex3);
  Serial.print(",");
  Serial.print(ADCflex4);
  Serial.print(",");
  Serial.print(ax);
  Serial.print(",");
  Serial.print(ay);
  Serial.print(",");
  Serial.print(az);
  Serial.print(",");
  Serial.print(gx);
  Serial.print(",");
  Serial.print(gy);
  Serial.print(",");
  Serial.println(gz);
  
  delay(500);
}
