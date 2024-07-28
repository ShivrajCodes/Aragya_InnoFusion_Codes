#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 3); // RX, TX

void setup() {
  // Initialize the serial communication:
  Serial.begin(9600);
  BTSerial.begin(9600);
  
  pinMode(10, INPUT); // Setup for leads off detection LO +
  pinMode(11, INPUT); // Setup for leads off detection LO -
}

void loop() {
  static float timeIndex = 0.0; // Time index or X-axis value
  
  if ((digitalRead(10) == 1) || (digitalRead(11) == 1)) {
    Serial.println("!");
    BTSerial.println("!");
  } else {
    int ecgValue = analogRead(A0);

    // Format the data for the Bluetooth Electronics app
    BTSerial.print("*G");
    BTSerial.print("X");
    BTSerial.print(timeIndex, 1); // Time index or X-axis value with one decimal place
    BTSerial.print("Y");
    BTSerial.print(ecgValue, 1); // ECG value or Y-axis value with one decimal place
    BTSerial.print("*");

    Serial.print("*G");
    Serial.print("X");
    Serial.print(timeIndex, 1);
    Serial.print("Y");
    Serial.print(ecgValue, 1);
    Serial.print("*");
    Serial.println();

    // Increment the time index for the next data point
    timeIndex += 0.1;
    if (timeIndex > 100.0) { // Reset the time index after reaching a certain value (optional)
      timeIndex = 0.0;
    }
  }
  
  // Adjust delay as needed
  delay(50); // Wait for a bit to keep serial data from saturating
}
