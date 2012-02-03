/*
 *  Test program for the accelerometer (MMA7341L)
 * 
 *  Pins:
 *    * TEST = 2
 *    * GSEL = 3
 *    * /SLP = 4
 *    * zeroG = 5
 *    * x = A0
 *    * y = A1
 *    * z = A2
 *  
 *  .Vdd = 3.3v
 *  .x, y, z -> 0g = 1.65v
 *  .Initial state depends on position (see MMA7341L datasheet)
 *  
 *  NOTA: La funcion map mapea numeros enteros.
 */
 
#include <SoftwareSerial.h>

int TEST = 2;
int GSEL = 3;
int noSLP = 4;
int zeroG = 5;  // Zero g = free fall
int xAxis = A0;
int yAxis = A1;
int zAxis = A2;

const int high33 = int(3.3 * 255 / 5.0);  // HIGH constant for Vdd = 3.3v

void setup() {
  Serial.begin(9600);
  
  // 
  pinMode(TEST, OUTPUT);
  pinMode(GSEL, OUTPUT);
  pinMode(noSLP, OUTPUT);
  pinMode(zeroG, INPUT);
  pinMode(xAxis, INPUT);
  pinMode(yAxis, INPUT);
  pinMode(zAxis, INPUT);
  
  digitalWrite(TEST, 0);  // No testing
  digitalWrite(GSEL, 0);  // g-Range = 3g, sensitivity = 440 mv/g

  analogWrite(noSLP, high33);  // Active    
}

void loop() {
  Serial.println("Reading...");
//  float xVoltage = analogRead(xAxis) * 3.3 / 1024;  //map(analogRead(xAxis), 0, 1023, 0.0, 3.3);
//  float yVoltage = analogRead(yAxis) * 3.3 / 1024;  //map(analogRead(yAxis), 0, 1023, 0.0, 3.3);
//  float zVoltage = analogRead(zAxis) * 3.3 / 1024;  //map(analogRead(zAxis), 0, 1023, 0.0, 3.3);
  
  int x = analogRead(xAxis);
  int y = analogRead(yAxis);
  int z = analogRead(zAxis);
  float xVoltage = mapf(x, 0, 1023, 0.0, 3.3);
  float yVoltage = mapf(y, 0, 1023, 0.0, 3.3);
  float zVoltage = mapf(z, 0, 1023, 0.0, 3.3);
  
  Serial.print("X-Axis: ");
  Serial.print(x); Serial.print(" - ");
  Serial.println(xVoltage,4);
  Serial.print("Y-Axis: ");
  Serial.print(y); Serial.print(" - ");
  Serial.println(yVoltage,4);
  Serial.print("Z-Axis: ");
  Serial.print(z); Serial.print(" - ");
  Serial.println(zVoltage,4);
  
  delay(1000);
}

/*
 * Re-maps a number from one range to another. That is, a value of fromLow 
 * would get mapped to toLow, a value of fromHigh to toHigh, values in-between
 * to values in-between, etc.
 * 
 * map(value, fromLow, fromHigh, toLow, toHigh)
 * 
 * NOTE: Floating point numbers are not exact, and may yield strange results 
 * when compared. For example 6.0 / 3.0 may not equal 2.0. You should instead 
 * check that the absolute value of the difference between the numbers is less 
 * than some small number.
 */
float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
