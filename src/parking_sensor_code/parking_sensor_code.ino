#include <TimedAction.h>
#include <SharpIR.h>
#include <Wire.h>
#include "SparkFun_Qwiic_Relay.h"

#define GREEN_LIGHT_SENSOR_PIN A0
#define YELLOW_LIGHT_SENSOR_PIN A1
#define RED_LIGHT_SENSOR_PIN A2
#define BIKE_SENSOR_PIN A3

#define GREEN_LIGHT 1
#define YELLOW_LIGHT 2
#define RED_LIGHT 3

// 1080 for GP2Y0A21Y
// 20150 for GP2Y0A02Y
#define CAR_SENSOR_MODEL 1080
#define BIKE_SENSOR_MODEL 1080

#define MS_PER_S 1000
#define CM_PER_FOOT 30.48

#define RELAY_ADDR 0x6D // Alternate address 0x6C
Qwiic_Relay quadRelay(RELAY_ADDR);

SharpIR green_light_sensor(GREEN_LIGHT_SENSOR_PIN, CAR_SENSOR_MODEL);
SharpIR yellow_light_sensor(YELLOW_LIGHT_SENSOR_PIN, CAR_SENSOR_MODEL);
SharpIR red_light_sensor(RED_LIGHT_SENSOR_PIN, CAR_SENSOR_MODEL);
SharpIR bike_sensor(BIKE_SENSOR_PIN, BIKE_SENSOR_MODEL);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin(); 

  if(!quadRelay.begin())
    Serial.println("Check connections to Qwiic Relay.");
  else
    Serial.println("Ready to flip some switches.");
}

bool is_vehicle_present(SharpIR sensor, int distance_threshold_ft) {
  int vehicle_distance = sensor.distance();
  Serial.print("Distance: ");
  Serial.println(vehicle_distance);
  bool is_vehicle_present = (vehicle_distance <= (distance_threshold_ft * CM_PER_FOOT));
  delay(1000);
  vehicle_distance = sensor.distance();
  Serial.print("Distance: ");
  Serial.println(vehicle_distance);
  is_vehicle_present &= (vehicle_distance <= (distance_threshold_ft * CM_PER_FOOT));
  return is_vehicle_present;
}

bool is_car_present(SharpIR sensor) {
  return (is_vehicle_present(sensor, 2));
}

bool is_bike_present() {
  return (is_vehicle_present(bike_sensor, 2));
}

void do_parking_sequence() {
  quadRelay.turnRelayOn(GREEN_LIGHT);

  while (!quadRelay.getState(RED_LIGHT)) {
    if (!is_car_present(green_light_sensor))
      return;
    
    if (is_car_present(green_light_sensor)
    && (is_car_present(yellow_light_sensor))) {
      quadRelay.turnRelayOff(GREEN_LIGHT);
      quadRelay.turnRelayOn(YELLOW_LIGHT);
    }

    if (is_car_present(green_light_sensor)
    && (is_car_present(yellow_light_sensor)
    && (is_car_present(red_light_sensor))) {
      quadRelay.turnRelayOff(YELLOW_LIGHT);
      quadRelay.turnRelayOn(RED_LIGHT);
    }
  }

  delay(5 * MS_PER_S);
  quadRelay.turnAllRelaysOff();
  delay(25 * MS_PER_S);
}

void loop() {  
  if (is_bike_present() 
  && is_car_present(green_light_sensor)
  && !is_car_present(yellow_light_sensor)) {
    do_parking_sequence();
  }
  
  delay(1 * MS_PER_S);
}
