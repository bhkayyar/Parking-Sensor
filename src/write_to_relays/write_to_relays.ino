#define GREEN_LIGHT 2
#define YELLOW_LIGHT 3
#define RED_LIGHT 4
#define UNUSED_RELAY 5

#define DEBUG 1

void setup() {
 pinMode(GREEN_LIGHT, OUTPUT);
 pinMode(YELLOW_LIGHT, OUTPUT);
 pinMode(RED_LIGHT, OUTPUT);
 pinMode(UNUSED_RELAY, OUTPUT);
}

void loop() {
  Serial.println("Entering sequence.");
  turn_relay_on(GREEN_LIGHT);
  delay(1500);
  turn_relay_on(YELLOW_LIGHT);
  delay(1500);
  turn_relay_on(RED_LIGHT);
  delay(1500);
  turn_relay_on(UNUSED_RELAY);
  delay(2500);
  turn_relay_off(GREEN_LIGHT);
  delay(1500);
  turn_relay_off(YELLOW_LIGHT);
  delay(1500);
  turn_relay_off(RED_LIGHT);
  delay(1500);
  turn_relay_off(UNUSED_RELAY);
  delay(2500);
  turn_all_on();
  delay(2000);
  turn_all_off();
  delay(2000);
  Serial.println("Exiting.");
}
