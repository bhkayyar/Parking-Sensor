#include "parking_sensor_code.h"

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(GREEN_LIGHT, OUTPUT);
  pinMode(YELLOW_LIGHT, OUTPUT);
  pinMode(RED_LIGHT, OUTPUT);

  if (DEBUG) {
    Serial.begin(115200);
    Serial.println("Starting up.");
  }
}

void do_parking_sequence() {
  turn_all_on();
  delay(0.5 * MS_PER_S);
  turn_all_off();
  turn_relay_on(GREEN_LIGHT);
  unsigned long t0 = millis();
  
  while (true) {
    delay(1* MS_PER_S);
    // If the car is not at the first sensor at any point in the sequence, reset. This is probably not a legitimate
    // parking situation or the car is leaving.
    if (!is_car_present(green_light_sensor)) {
      delay(1 * MS_PER_S);
      if (!is_car_present(green_light_sensor)) {
        if (DEBUG) {
          Serial.println("Car not found at green light sensor within parking sequence. Goodbye!");
        }
      
        turn_all_off();
        return; 
      }
    } else {
      // Here we are certain that the car is present at the green light sensor.
      if (is_car_present(yellow_light_sensor)) {
        turn_relay_on(YELLOW_LIGHT);
        turn_relay_off(GREEN_LIGHT);
        if (DEBUG) {
          Serial.println("At yellow.");
        }
      }
      else {
        turn_relay_off(YELLOW_LIGHT);
        turn_relay_on(GREEN_LIGHT);
        if (DEBUG) {
          Serial.println("Turning yellow off.");
        }
      }
      
      if (is_car_present(yellow_light_sensor) && is_car_present(red_light_sensor)) {
        turn_relay_on(RED_LIGHT);
        turn_relay_off(YELLOW_LIGHT);
        if (DEBUG) {
          Serial.println("Turning red on.");
        }

        break;
      }
    }

    if ((millis() - t0)/MS_PER_S > 15) {
      if (DEBUG) {
        Serial.println("Been inside parking sequence for 15s with no red light. Bye!");
      }

      turn_all_off();
      return;
    }
  }

  if (DEBUG) {
    Serial.println("Parking sequence complete.");
  }

  // Keep the red light on for 10s and then turn everything off for 25s.
  delay(10 * MS_PER_S);
  turn_all_off();
  delay(15 * MS_PER_S);
}

void loop() {
  // TODO: If the car is at the first sensor but not at the second, it is either entering or exiting. Need to figure out
  // how to differentiate between the two.

  // If the car is at the first sensor and not at the second, check again in 1s to eliminate noise. If the car is
  // indeed at the first sensor, begin parking sequence.
  if (is_car_present(green_light_sensor)
  && !is_car_present(red_light_sensor)) {
    delay(1 * MS_PER_S);

    if (is_car_present(green_light_sensor)
    && !is_car_present(red_light_sensor)) {
      if (DEBUG) {
        Serial.println("Entering parking sequence!");
      }
      do_parking_sequence();
    }
  }

  turn_all_off();
  delay(1 * MS_PER_S);
}
