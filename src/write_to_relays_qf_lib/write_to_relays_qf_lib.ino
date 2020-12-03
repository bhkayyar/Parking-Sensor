#include <Wire.h>
#include "SparkFun_Qwiic_Relay.h"

#define GREEN_LIGHT 1
#define YELLOW_LIGHT 2
#define RED_LIGHT 3

#define RELAY_ADDR 0x6D // Alternate address 0x6C
Qwiic_Relay quadRelay(RELAY_ADDR);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("A.");
  bool relay_start = quadRelay.begin();
  Serial.println("B.");

  if(!relay_start) {
      Serial.println("Check connections to Qwiic Relay.");
    } else {
      Serial.println("Ready to flip some switches.");
    }

  if (!relay_start) {
    // If the relay seems down, flash an error code and reset the board to try again. 
    for (int i = 0; i < 3; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(250);
      digitalWrite(LED_BUILTIN, LOW);
      delay(250);
    }
  }
}


void loop() {
  // TODO: If the car is at the first sensor but not at the second, it is either entering or exiting. Need to figure out

}
