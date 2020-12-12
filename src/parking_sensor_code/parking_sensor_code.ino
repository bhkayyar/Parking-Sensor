#include <SharpIR.h>

#define DEBUG 1

#define GREEN_LIGHT_SENSOR_PIN A0
#define YELLOW_LIGHT_SENSOR_PIN A1
#define RED_LIGHT_SENSOR_PIN A2

#define GREEN_LIGHT 2
#define YELLOW_LIGHT 3
#define RED_LIGHT 4

// 1080 for GP2Y0A21Y
// 20150 for GP2Y0A02Y
#define CAR_SENSOR_MODEL 1080

#define MS_PER_S 1000
#define CM_PER_FOOT 30.48

SharpIR green_light_sensor(GREEN_LIGHT_SENSOR_PIN, CAR_SENSOR_MODEL);
SharpIR yellow_light_sensor(YELLOW_LIGHT_SENSOR_PIN, CAR_SENSOR_MODEL);
SharpIR red_light_sensor(RED_LIGHT_SENSOR_PIN, CAR_SENSOR_MODEL);

void(* resetFunc) (void) = 0; //Reset function if things go wrong.

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

bool is_vehicle_present(SharpIR sensor, int distance_threshold_ft) {
  int vehicle_distance = sensor.distance();
  bool is_vehicle_present = (vehicle_distance <= (distance_threshold_ft * CM_PER_FOOT));

  if (DEBUG) {
    Serial.print("Distance: ");
    Serial.println(vehicle_distance);
  }

  return is_vehicle_present;
}

bool is_car_present(SharpIR sensor) {
  return (is_vehicle_present(sensor, 2));
}

void do_parking_sequence() {
  turn_all_on();
  delay(250);
  turn_all_off();
  turn_relay_on(GREEN_LIGHT);
  unsigned long t0 = millis();
  
  while (true) {
    delay(1000);
    // If the car is not at the first sensor at any point in the sequence, reset. This is probably not a legitimate
    // parking situation or the car is leaving.
    if (!is_car_present(green_light_sensor)) {
      if (DEBUG) {
        Serial.println("Car not found at green light sensor within parking sequence. Goodbye!");
      }
      
      turn_all_off();
      return;
    } else {
      // Here we are certain that the car is present at the green light sensor.
      if (is_car_present(yellow_light_sensor)) {
        turn_relay_on(YELLOW_LIGHT);
        turn_relay_off(GREEN_LIGHT);
        Serial.println("At yellow.");
      }
      else {
        turn_relay_off(YELLOW_LIGHT);
        turn_relay_on(GREEN_LIGHT);
        Serial.println("Turning yellow off.");
      }
      
      if (is_car_present(yellow_light_sensor) && is_car_present(red_light_sensor)) {
        turn_relay_on(RED_LIGHT);
        turn_relay_off(YELLOW_LIGHT);
        Serial.println("Car not found at green light sensor within parking sequence. Goodbye!");

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

  // Keep the red light on for 5s and then turn everything off for 25s.
  delay(5 * MS_PER_S);
  turn_all_off();
  delay(25 * MS_PER_S);
}

void loop() {
  // TODO: If the car is at the first sensor but not at the second, it is either entering or exiting. Need to figure out
  // how to differentiate between the two.

  // If the car is at the first sensor and not at the second, check again in 1s to eliminate noise. If the car is
  // indeed at the first sensor, begin parking sequence.
  if (is_car_present(green_light_sensor)
  && !is_car_present(yellow_light_sensor)
  && !is_car_present(red_light_sensor)) {
    delay(1 * MS_PER_S);

    if (is_car_present(green_light_sensor)
    && !is_car_present(yellow_light_sensor)
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
