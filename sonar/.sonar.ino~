/*
 * Test program for LV-MaxSonar-EZ0 High Performance Sonar Range Finder
 *
 * NOTES:
 * 
 *  * Readings can occur up to every 50mS, (20-Hz rate)
 *  * Free run operation can continually measure and output range information
 *  * Triggered operation provides the range reading as desired
 *  * All interfaces are active simultaneously
 *    * Serial, 0 to Vcc, 9600Baud, 81N
 *    * Analog, (Vcc/512) / inch
 *    * Pulse width, (147uS/inch)
 *  * 250mS after power-up, the LV-MaxSonar-EZ0 is ready to accept the RX command.
 *    The sensor will first run a calibration cycle (49mS), and then it will 
 *    take a range reading (49mS). After the power up delay, the first reading
 *    will take an additional ~100mS.
 *
 * Pin Out:
 * 
 * TX
 *  When the *BW is open or held low, the TX output delivers
 *  asynchronous serial with an RS232 format, except voltages are 0-
 *  Vcc. The output is an ASCII capital “R”, followed by three ASCII
 *  character digits representing the range in inches up to a maximum of
 *  255, followed by a carriage return (ASCII 13). The baud rate is
 *  9600, 8 bits, no parity, with one stop bit. Although the voltage of 0-
 *  Vcc is outside the RS232 standard, most RS232 devices have
 *  sufficient margin to read 0-Vcc serial data. If standard voltage level
 *  RS232 is desired, invert, and connect an RS232 converter such as a
 *  MAX232. When BW pin is held high the TX output sends a single
 *  pulse, suitable for low noise chaining. (no serial data).
 * 
 * RX
 *  This pin is internally pulled high. The EZ0 will continually
 *  measure range and output if RX data is left unconnected or held high.
 *  If held low the EZ0 will stop ranging. Bring high for 20uS or more
 *  to command a range reading.
 *
 * AN
 *  Outputs analog voltage with a scaling factor of (Vcc/512) per
 *  inch. A supply of 5V yields ~9.8mV/in. and 3.3V yields ~6.4mV/in.
 *  The output is buffered and corresponds to the most recent range data.
 * 
 * PW
 *  This pin outputs a pulse width representation of range. The
 *  distance can be calculated using the scale factor of 147uS per inch.
 * 
 * BW
 *  *Leave open or hold low for serial output on the TX output.
 *  When BW pin is held high the TX output sends a pulse (instead of
 *  serial data), suitable for low noise chaining.
 */

#include <SoftwareSerial.h>

// These constants won't change.  They're used to give names to the pins used:
const int TXpin = 0;
const int RXpin = 1;
const int ANpin = A0;
const int PWpin = 2;
const int BWpin = 3;
const int VCC = 4;
const int ledPin = 13;

// Variables for the indivial calculated distances (Inches)
float distancePW = 0;
float distanceSerial = 0;
float distanceAN = 0;

// Define serial communication
SoftwareSerial mySerial(RXpin, TXpin);

void setup() {
  mySerial.begin(9600);   // Init serial
  pinMode(ANpin, INPUT);
  pinMode(PWpin, INPUT);
  pinmode(BWpin, OUTPUT);
  
  digitalWrite(BWpin, LOW); // For serial communication
  
  // 250mS after power-up, the LV-MaxSonar -EZ0 is ready to accept the RX command
  digitalWrite(VCC, HIGH);
  delay(250)  // ¿? 
  
  // Calibrating (first reading)
  calibrate();
  
}

void loop() {
  // Each 49mS period starts by the RX being high or open, after which the 
  //LV-MaxSonar -EZ0 sends thirteen 42KHz waves
  
  // Start ranging
  startPulse()
  
  // after which the pulse width pin (PW) is set high. When a target is 
  // detected the PW pin is pulled low. The PW pin is high for up to 37.5mS 
  //if no target is detected.
  
  // Measure pulse duration
  distancePW = rangePW();
  
  // The remainder of the 49mS time (less 4.7mS) is spent adjusting the analog
  // voltage to the correct level. When a long distance is measured immediately
  // after a short distance reading, the analog voltage may not reach the exact
  // level within one read cycle.
  //  During the last 4.7mS, the serial data is sent.
  
  // Read distance through serial
  distanceSerial = rangeSerial();
  
  // Measure analog voltage
  distanceAN = rangeAN();
  
  // Do something
  // ...
}

/* 
 * Start ranging
 */
void startPulse() {
  digitalWrite(RXpin, HIGH);
  delay(22);  // Delay higher than 20uS
  digitalWrite(RXpin, LOW);
}

/*
 * Measure pulse duration
 *
 * Distance = pulseDuration / 147uS per inch
 * If distance = -1, no target was detected
 */ 
float rangePW() {
  float distance = 0;
  unsigned long pulseDuration = pulseIn(PWpin, HIGH);
  
  if ( pulseDuration < 37.5 ) {
    distance = (float)pulseDuration / 147.0;  // Inches
  }
  else {
    // No target was detected
    distance = -1;
  }
  
  return distance;
}
  
/*
 * Read distance through serial
 *
 * The output is an ASCII capital “R”, followed by three ASCII
 * character digits representing the range in inches up to a maximum of
 * 255, followed by a carriage return (ASCII 13)
 */
float rangeSerial() {  // -> Integer
  float distance = 0;
  char incomingData = 0;
  String data = "";
  
//   while ( Serial.available() > 0 ) {
//     // Read the incoming byte
//     incomingData = Serial.read(); // "R" or carriage return
//     
//     if ( incomingData == 'R' ) {
//       for (int i=0; i<3; i++) {
//         incomingData = Serial.read();
//         data.concat(incomingData);
//       }
//     }
//   }
//   
  
  while ( Serial.available() > 0 ) {
    // Read the incoming byte
    incomingData = Serial.read();  // 'R' or carriage return
    
    if ( incomingData == 'R' ) {
      for (int i=0; i<3; i++) {
        incomingData = Serial.read();
        data.concat(incomingData);
      }
    }
    
    if ( incomingData == 13 ) {  // == '\r'
      Serial.flush();  // Clean buffer
    }
  }
  
  // String to integer
  char t[str.length()+1];
  str.toCharArray(t, sizeof(t));
  distance = (float) atoi(t);  // Inches
  
  return distance;
}

/*
 * Measure analog voltage
 *
 * A supply of 5V yields ~9.8mV/in. and 3.3V yields ~6.4mV/in. (Vcc/512)
 */
float rangeAN() {
  int voltage = mapf(analogRead(ANpin), 0, 1023, 0, 5);
  distanceAN = voltage / 0.0098;  // Inches
  
  return distance;
}

/*
 * Calibrating (first reading)
 *
 * The first reading will take an additional ~100mS
 * It is important that objects not be close to the sensor during this 
 * calibration cycle.
 */
void calibrate() {
  // Start-reading pulse
  startPulse();
  digitalWrite(ledPin, HIGH);
  delay(150);  //
  digitalWrite(ledPin, LOW);
}
  
/*
 * Reset the sensor and calibrate
 */
void reset() {
  digitalWrite(VCC, LOW);  // Power-off
  delay(50);  // Some time
  digitalWrite(VCC, HiGH);
  
  calibrate()
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