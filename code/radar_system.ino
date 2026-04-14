#include <Servo.h>

// Ultrasonic Sensor Pins
const int trigPin = 7;
const int echoPin = 6;

// Servo Objects
Servo launcherServo;  // Servo 1 - Launcher
Servo radarServo;     // Servo 2 - Radar Scanner

// LED and Buzzer Pins
const int ledPin = 3;
const int buzzerPin = 2;

// Servo Pins
const int launcherPin = 9;
const int radarPin = 10;

// Variables
long duration;
int distance;
int radarAngle = 0;
int radarDirection = 1; // 1 for increasing, -1 for decreasing
bool targetDetected = false;
const int detectionDistance = 30; // Distance in cm to trigger launcher

void setup() {
  // Initialize pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Attach servos
  launcherServo.attach(launcherPin);
  radarServo.attach(radarPin);
  
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Reset launcher to ready position (90 degrees)
  launcherServo.write(90);
  
  Serial.println("Missile Launcher System Ready!");
  Serial.println("Radar Scanning...");
}

void loop() {
  // Radar scanning motion
  radarScan();
  
  // Measure distance
  distance = getDistance();
  
  // Display radar information
  displayRadarInfo();
  
  // Check if target is detected
  if (distance <= detectionDistance && distance > 0) {
    if (!targetDetected) {
      targetDetected = true;
      triggerAlarm();
      fireMissile();
    }
  } else {
    targetDetected = false;
  }
  
  delay(50); // Small delay for stability
}

int getDistance() {
  // Clear trig pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Set trig pin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read echo pin, returns sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance (speed of sound = 343 m/s = 0.0343 cm/μs)
  // Distance = time × speed ÷ 2 (go and return)
  int dist = duration * 0.0343 / 2;
  
  return dist;
}

void radarScan() {
  // Update radar angle
  radarAngle += radarDirection;
  
  // Change direction at limits
  if (radarAngle >= 180) {
    radarDirection = -1;
  } else if (radarAngle <= 0) {
    radarDirection = 1;
  }
  
  // Move radar servo
  radarServo.write(radarAngle);
}

void displayRadarInfo() {
  Serial.print("Radar Angle: ");
  Serial.print(radarAngle);
  Serial.print("° | Distance: ");
  Serial.print(distance);
  Serial.print(" cm");
  
  if (targetDetected) {
    Serial.print(" | TARGET LOCKED!");
  }
  
  Serial.println();
}

void triggerAlarm() {
  Serial.println("ALERT! TARGET DETECTED!");
  
  // Flash LED and sound buzzer
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000); // 1000 Hz tone
    delay(200);
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    delay(200);
  }
}

void fireMissile() {
  Serial.println("FIRING MISSILE!");
  
  // Additional alarm before firing
  digitalWrite(ledPin, HIGH);
  tone(buzzerPin, 1500);
  delay(1000);
  
  // Fire missile - rotate servo from 90 to 0 degrees
  for (int pos = 90; pos >= 0; pos--) {
    launcherServo.write(pos);
    delay(15); // Adjust speed of firing
  }
  
  Serial.println("MISSILE FIRED!");
  
  // Keep alarm on for 2 seconds after firing
  delay(2000);
  digitalWrite(ledPin, LOW);
  noTone(buzzerPin);
  
  // Reset launcher after 3 seconds
  delay(3000);
  launcherServo.write(90);
  Serial.println("Launcher Reset - Ready for next target");
}
