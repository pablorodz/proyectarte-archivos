/*
    Sharp GP2Y0A21 IR ranger reader
*/

// GP2Y0A21
//   - Anolog output
//   - range = 10-80 cm --> NOT LINEAR
//     - Segun LibreOffice -> dist(v0) = 27.3701 v0^(-1.2014)
//     - Segun el fabricante es lineal. dist aprox 27 [V*cm] / V0.
//   - LED Pulse Cycle Duration: 32 ms
//   - Range: 10 to 80 cm
//   - Typical response time: 39 ms
//   - Typical start up delay: 44 ms
//   - Average Current Consumption: 30 mA
//   - Detection Area Diameter @ 80 cm: 12 cm
void setup() {
    // Initialize serial communications at 9600 bps
    Serial.begin(9600);
}

void loop() {
  
  int sensorValue = analogRead(A0);   // sensorValue = [0..1023]
  // Convert to a voltage
  float voltage = mapf(sensorValue, 0, 1023, 0, 5);
  float distance = 27.3701 * pow(voltage, -1.2014);

    
    if (distance < 10) {
      Serial.println("Muy cerca!");
      Serial.println();
    }
    else if (distance > 80) {
      Serial.println("Muy lejos!");
      Serial.println();
    }
    else {
      // print sensor value
      Serial.print("sensorValue: ");
      Serial.println(sensorValue);
      Serial.print("voltage: ");
      Serial.println(voltage);
      Serial.print("distance: ");
      Serial.print(distance);
      Serial.println(" cm");
      Serial.println();
      // wait 10ms to the next reading

      delay(1000);
    }
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