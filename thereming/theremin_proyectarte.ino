// Arduino-Theremin
//
// Needs:
//   * GP2Y0A21, wide-angle distance measuring sensor.
//   * Music Instrument Shield, for playing MIDI sounds
// 

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


int sensorPin = ;
unsigned long voltage = 0;  // sensor output voltage
unsigned long distance = 0; // variable for storing the distance
int ledPin = 13;    // Notification led

void setup() {
    Serial.begin(9600);

    // declare the ledPin as an OUTPUT:
    pinMode(ledPin, OUTPUT);
}

void loop() {
    // read the value from the sensor:
    voltage = mapf(analogRead(sensorPin), 0, 1023, 0, 5);
    distance = 27.3701 * pow(voltage, -1.2014);
    
    
    
    delay();                  
}

/*
 * Re-maps a number from one range to another. That is, a value of fromLow 
 * would get mapped to toLow, a value of fromHigh to toHigh, values in-between
 * to values in-between, etc.
 * 
 * mapf(value, fromLow, fromHigh, toLow, toHigh)
 * 
 * NOTE: Floating point numbers are not exact, and may yield strange results 
 * when compared. For example 6.0 / 3.0 may not equal 2.0. You should instead 
 * check that the absolute value of the difference between the numbers is less 
 * than some small number.
 */
float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//Send a MIDI note-on message.  Like pressing a piano key
//channel ranges from 0-15
void noteOn(byte channel, byte note, byte attack_velocity) {
  talkMIDI( (0x90 | channel), note, attack_velocity);
}

//Send a MIDI note-off message.  Like releasing a piano key
void noteOff(byte channel, byte note, byte release_velocity) {
  talkMIDI( (0x80 | channel), note, release_velocity);
}

//Plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that data values are less than 127
void talkMIDI(byte cmd, byte data1, byte data2) {
  digitalWrite(ledPin, HIGH);
  mySerial.write(cmd);
  mySerial.write(data1);

  //Some commands only have one data byte. All cmds less than 0xBn have 2 data bytes 
  //(sort of: http://253.ccarh.org/handout/midiprotocol/)
  if( (cmd & 0xF0) <= 0xB0 || (cmd & 0xF0) == 0xE0)
    mySerial.write(data2);

  digitalWrite(ledPin, LOW);
}