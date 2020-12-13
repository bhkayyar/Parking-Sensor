#ifndef PARKING_SENSOR_CODE_H
#define PARKING_SENSOR_CODE_H

#include <SharpIR.h>

#define DEBUG 1

#define GREEN_LIGHT 2
#define YELLOW_LIGHT 3
#define RED_LIGHT 4

#define MS_PER_S 1000
#define CM_PER_FOOT 30.48

// 1080 for GP2Y0A21Y
// 20150 for GP2Y0A02Y
#define CAR_SENSOR_MODEL 1080

#define GREEN_LIGHT_SENSOR_PIN A0
#define YELLOW_LIGHT_SENSOR_PIN A1
#define RED_LIGHT_SENSOR_PIN A2

SharpIR green_light_sensor(GREEN_LIGHT_SENSOR_PIN, CAR_SENSOR_MODEL);
SharpIR yellow_light_sensor(YELLOW_LIGHT_SENSOR_PIN, CAR_SENSOR_MODEL);
SharpIR red_light_sensor(RED_LIGHT_SENSOR_PIN, CAR_SENSOR_MODEL);

void(* resetFunc) (void) = 0; //Reset function if things go wrong.

void turn_relay_on(int pin);
void turn_relay_off(int pin);
void turn_all_on();
void turn_all_off();

bool is_vehicle_present(SharpIR sensor, int distance_threshold_ft);
bool is_car_present(SharpIR sensor);

#endif
