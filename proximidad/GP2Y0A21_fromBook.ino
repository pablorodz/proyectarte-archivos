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
    float voltage = map(sensorValue, 0, 1023, 0, 5);  // devuelve float??
    
    float distance = 27.0 / voltage;
    
    // print sensor value
    Serial.print(distance);
    Serial.println(" cm");
    // wait 10ms to the next reading
    delay(10);
}