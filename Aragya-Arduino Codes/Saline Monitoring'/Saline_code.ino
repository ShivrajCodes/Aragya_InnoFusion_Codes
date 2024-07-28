#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// Use pins 2 and 3 to communicate with DFPlayer Mini
static const uint8_t PIN_MP3_TX = 2; // Connects to module's RX 
static const uint8_t PIN_MP3_RX = 3; // Connects to module's TX 
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

// Create the Player object
DFRobotDFPlayerMini player;

// Define pins for the ultrasonic sensor
const int triggerPin = 4;
const int echoPin = 5;

void setup() {
  // Init USB serial port for debugging
  Serial.begin(9600);
  // Init serial port for DFPlayer Mini
  softwareSerial.begin(9600);

  // Start communication with DFPlayer Mini
  if (player.begin(softwareSerial)) {
    Serial.println("DFPlayer Mini OK");

    // Set volume to maximum (0 to 30)
    player.volume(30);

    // Initialize the ultrasonic sensor
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);

  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
}

void loop() {
  // Measure distance
  long duration, distance;
  
  // Send a pulse to the trigger pin
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  // Read the pulse from the echo pin
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance (duration / 2) * speed of sound (0.034 cm/us)
  distance = (duration / 2) * 0.034;

  // Print distance to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Check if distance is less than 10 cm
  if (distance >= 13 && distance <= 20 ) {
    // Play MP3 file
    player.play(1);
    
    // Delay to prevent multiple triggers in a short period
    delay(5000);  // Adjust as needed
  }
  
  // Short delay before the next reading
  delay(100);
}
