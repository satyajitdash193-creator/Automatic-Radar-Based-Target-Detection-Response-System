#  Automatic Radar-Based Target Detection System

##  Overview
This project is an Arduino-based radar scanning system that detects nearby objects using an ultrasonic sensor and responds automatically using a servo-based actuation mechanism.

It simulates a defense-inspired system for object detection, tracking, and automated response.

##  Components Used
- Arduino Uno
- Ultrasonic Sensor (HC-SR04)
- Servo Motors (2x)
- Buzzer
- LED
- Jumper Wires
- Power Supply

##  Working Principle
- The radar servo continuously scans from 0° to 180°
- The ultrasonic sensor measures distance in real time
- If an object is detected within 30 cm:
  - Alarm (LED + Buzzer) is triggered
  - Launcher servo performs an action (simulation of response)
- System then resets and continues scanning
##  Demo Video
   https://youtu.be/VeAUMNAeR-A

##  Code Features
- Real-time radar scanning
- Distance calculation using ultrasonic sensor
- Servo-based tracking system
- Audio-visual alert system
- Automated response mechanism

##  Future Improvements
- AI-based object classification
- Camera integration (Computer Vision)
- Wireless monitoring using IoT
- Mobile app control
- Target tracking optimization using PID control

##  Applications
- Surveillance systems
- Smart security systems
- Obstacle detection robots
- Defense simulation prototypes

##  Author
Satyajit Dash
