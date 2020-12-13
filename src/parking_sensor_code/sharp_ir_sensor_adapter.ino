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
