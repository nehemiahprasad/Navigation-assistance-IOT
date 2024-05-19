#include "pitches2.h"

#define TRIG_PIN1  D1 // The ESP8266 pin D1 connected to the first Ultrasonic Sensor's TRIG pin
#define ECHO_PIN1  D2 // The ESP8266 pin D2 connected to the first Ultrasonic Sensor's ECHO pin
#define TRIG_PIN2  D5 // The ESP8266 pin D5 connected to the second Ultrasonic Sensor's TRIG pin
#define ECHO_PIN2  D6 // The ESP8266 pin D6 connected to the second Ultrasonic Sensor's ECHO pin
#define TRIG_PIN3  D3 // The ESP8266 pin D3 connected to the third Ultrasonic Sensor's TRIG pin
#define ECHO_PIN3  D4 // The ESP8266 pin D4 connected to the third Ultrasonic Sensor's ECHO pin
#define BUZZER_PIN D7 // The ESP8266 pin D7 connected to Piezo Buzzer's pin
#define DISTANCE_THRESHOLD 50 // centimeters

float duration_us1, distance_cm1;
float duration_us2, distance_cm2;
float duration_us3, distance_cm3;

// Melody for Ultrasonic Sensor 1
int melody1[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// Melody for Ultrasonic Sensor 2
int melody2[] = {
  NOTE_E5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_D5
};

// Melody for Ultrasonic Sensor 3
int melody3[] = {
  NOTE_A5, NOTE_B5, NOTE_C6, NOTE_D6, NOTE_C6, NOTE_B5, NOTE_A5, 0
};

// Note durations for all melodies
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
  pinMode(TRIG_PIN1, OUTPUT);   // Configure the ESP8266 pin to the output mode for the first sensor
  pinMode(ECHO_PIN1, INPUT);    // Configure the ESP8266 pin to the input mode for the first sensor
  pinMode(TRIG_PIN2, OUTPUT);   // Configure the ESP8266 pin to the output mode for the second sensor
  pinMode(ECHO_PIN2, INPUT);    // Configure the ESP8266 pin to the input mode for the second sensor
  pinMode(TRIG_PIN3, OUTPUT);   // Configure the ESP8266 pin to the output mode for the third sensor
  pinMode(ECHO_PIN3, INPUT);    // Configure the ESP8266 pin to the input mode for the third sensor
}

void loop() {
  // Measure distance from the first sensor
  digitalWrite(TRIG_PIN1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN1, LOW);
  duration_us1 = pulseIn(ECHO_PIN1, HIGH);
  distance_cm1 = 0.017 * duration_us1;

  // Measure distance from the second sensor
  digitalWrite(TRIG_PIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN2, LOW);
  duration_us2 = pulseIn(ECHO_PIN2, HIGH);
  distance_cm2 = 0.017 * duration_us2;

  // Measure distance from the third sensor
  digitalWrite(TRIG_PIN3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN3, LOW);
  duration_us3 = pulseIn(ECHO_PIN3, HIGH);
  distance_cm3 = 0.017 * duration_us3;

  // Check if any sensor detects an obstacle and play the corresponding melody
  if (distance_cm1 < DISTANCE_THRESHOLD) {
    playMelody(melody1);
  } else if (distance_cm2 < DISTANCE_THRESHOLD) {
    playMelody(melody2);
  } else if (distance_cm3 < DISTANCE_THRESHOLD) {
    playMelody(melody3);
  }

  delay(500);
}

// Function to play a melody
void playMelody(int melody[]) {
  int size = sizeof(noteDurations) / sizeof(int);

  for (int thisNote = 0; thisNote < size; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(BUZZER_PIN, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZER_PIN);
  }
}
