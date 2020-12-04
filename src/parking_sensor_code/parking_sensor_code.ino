#include <SoftwareWire.h>
#include <SharpIR.h>

#define DEBUG 1

#define GREEN_LIGHT_SENSOR_PIN A0
#define YELLOW_LIGHT_SENSOR_PIN A1
#define RED_LIGHT_SENSOR_PIN A2

#define GREEN_LIGHT 1
#define YELLOW_LIGHT 2
#define RED_LIGHT 3

// 1080 for GP2Y0A21Y
// 20150 for GP2Y0A02Y
#define CAR_SENSOR_MODEL 1080

#define MS_PER_S 1000
#define CM_PER_FOOT 30.48

// SoftwareWire constructor.
// Parameters:
//   (1) pin for the software sda
//   (2) pin for the software scl
//   (3) use internal pullup resistors. Default true. Set to false to disable them.
//   (4) allow the Slave to stretch the clock pulse. Default true. Set to false for faster code.
//
// Using pin 2 (software sda) and 3 (software scl) in this example.
SoftwareWire softWire(2, 3);

SharpIR green_light_sensor(GREEN_LIGHT_SENSOR_PIN, CAR_SENSOR_MODEL);
SharpIR yellow_light_sensor(YELLOW_LIGHT_SENSOR_PIN, CAR_SENSOR_MODEL);
SharpIR red_light_sensor(RED_LIGHT_SENSOR_PIN, CAR_SENSOR_MODEL);

void(* resetFunc) (void) = 0; //Reset function if things go wrong.

void setup() {
  softWire.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  initialize_wire(softWire);

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
  turn_relay_on(GREEN_LIGHT);

  while (!get_relay_state(RED_LIGHT)) {
    // If the car is not at the first sensor at any point in the sequence, reset. This is probably not a legitimate
    // parking situation.
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
      }
      
      if (is_car_present(yellow_light_sensor) && is_car_present(red_light_sensor)) {
        turn_relay_on(RED_LIGHT);
        turn_relay_off(YELLOW_LIGHT);
      }
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
  && !is_car_present(yellow_light_sensor)) {
    delay(1 * MS_PER_S);

    if (is_car_present(green_light_sensor)) {
      if (DEBUG) {
        Serial.println("Entering parking sequence!");
      }
      do_parking_sequence();
    }
  }

  delay(1 * MS_PER_S);
}
