#include <Adafruit_NeoPixel.h>
#include <HCSR04.h>

#define PIN 18          // Pin connected to the NeoPixel strip
#define NUMPIXELS 12   // Total LEDs in the strip

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Ultrasonic Sensor (Trig = 9, Echo = 10)
UltraSonicDistanceSensor distanceSensor(13,12);  

int current_Last_LED = 0;

void setup() {
  pixels.begin(); 
  pixels.clear(); 
  pixels.show();
  Serial.begin(9600);
}

void loop() {
  pixels.clear(); // Turn off all LEDs

  // Measure distance in cm
  float distance = distanceSensor.measureDistanceCm();

  // Convert distance to LED count (example: closer = more LEDs)
  // Adjust multiplier to match your tank height and LED range
  current_Last_LED = map((int)distance, 17, 2, 0, 12); // 12 active LEDs
  current_Last_LED = constrain(current_Last_LED, 0, 12);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | LEDs On: ");
  Serial.println(current_Last_LED);

  // Turn on LEDs based on the measured level
  for (int i = 0; i < current_Last_LED; i++) {
    if (i < 4) {
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));   // Red zone (bottom)
    } else if (i < 8) {
      pixels.setPixelColor(i, pixels.Color(255, 255, 0)); // Yellow zone (middle)
    } else {
      pixels.setPixelColor(i, pixels.Color(0, 255, 0));   // Green zone (top)
    }
  }

  pixels.show();  // Update LED strip
  delay(200);
}
