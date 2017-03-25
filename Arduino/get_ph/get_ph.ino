const int analogInPin = A2; // Analog input pin that the sensor is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to
int sensorValue = 0; // value read from the pot
int outputValue = 0; // value output to the PWM (analog out)
void setup() {
// initialize serial communications at 9600 bps:
Serial.begin(9600);
}
void loop() {
// read the analog in value:
sensorValue = analogRead(analogInPin);
// map it to the range of the analog out:
outputValue = map(sensorValue, 0, 1023, 0, 14);
// change the analog out value:
analogWrite(analogOutPin, outputValue);
// print the results to the serial monitor:
Serial.print("sensor : ");
Serial.print(sensorValue);
Serial.print(", \t PH : ");
Serial.println(analogRead(2)* 14.0 / 1024, 1);
// wait 10 milliseconds before the next loop
// for the analog-to-digital converter to settle
// after the last reading:
delay(500);
}
