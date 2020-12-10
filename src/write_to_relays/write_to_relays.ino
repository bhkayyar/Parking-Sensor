#define GREEN_LIGHT 0
#define YELLOW_LIGHT 1
#define RED_LIGHT 2
#define DEBUG 1

void setup() {
 pinMode(GREEN_LIGHT, OUTPUT);
 pinMode(YELLOW_LIGHT, OUTPUT);
 pinMode(RED_LIGHT, OUTPUT);
}

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

void loop() {
  Serial.println("Entering sequence.");
  turn_relay_on(GREEN_LIGHT);
  delay(500);
  turn_relay_on(YELLOW_LIGHT);
  delay(500);
  turn_relay_on(RED_LIGHT);
  delay(1500);
  turn_relay_off(GREEN_LIGHT);
  delay(500);
  turn_relay_off(YELLOW_LIGHT);
  delay(500);
  turn_relay_off(RED_LIGHT);
  delay(1500);
  turn_all_on();
  delay(1000);
  turn_all_off();
  delay(2000);
  Serial.println("Exiting.");
}
