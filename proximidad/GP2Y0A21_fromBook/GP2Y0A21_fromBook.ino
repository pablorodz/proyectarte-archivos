/*
    Sharp GP2Y0A21 IR ranger reader
*/

void setup() {
    // Initialize serial communications at 9600 bps
    Serial.begin(9600);
}

void loop() {
    int sensorValue = analogRead(A0);   // sensorValue = [0..1023]
    // Convert to a voltage
    float voltage = mapf(sensorValue, 0, 1023, 0, 5);
    
    float distance = 27.0 / voltage;
    
    // print sensor value
    Serial.print("sensorValue: ");
    Serial.println(sensorValue);
    Serial.print("voltage: ");
    Serial.println(voltage);
    Serial.print("distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    // wait 10ms to the next reading
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

