void turn_relay_on(int pin) {
  digitalWrite(pin, LOW);
}

void turn_relay_off(int pin) {
  digitalWrite(pin, HIGH);
}

void turn_all_on() {
  turn_relay_on(GREEN_LIGHT);
  turn_relay_on(YELLOW_LIGHT);
  turn_relay_on(RED_LIGHT);
}

void turn_all_off() {
  turn_relay_off(GREEN_LIGHT);
  turn_relay_off(YELLOW_LIGHT);
  turn_relay_off(RED_LIGHT);
}
