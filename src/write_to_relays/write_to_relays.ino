#include <SoftwareWire.h>

SoftwareWire softWire(2, 3, true, false);
#define GREEN_LIGHT 1
#define YELLOW_LIGHT 2
#define RED_LIGHT 3
#define DEBUG 1

void setup() {
  softWire.begin();
  softWire.setClock(120000);
  pinMode(LED_BUILTIN, OUTPUT);
  initialize_wire(softWire);

  if (DEBUG) {
    Serial.begin(115200);
    Serial.println("Starting up.");
  }
}

void do_parking_sequence() {
//  turn_relay_on(GREEN_LIGHT);
//  delay(1000);
//  turn_relay_off(GREEN_LIGHT);
//  delay(1000);

//  turn_relay_on(YELLOW_LIGHT);
//  delay(1000);
//  turn_relay_off(YELLOW_LIGHT);
//  delay(1000);
//
//  turn_relay_on(RED_LIGHT);
//  delay(1000);
//  turn_relay_off(RED_LIGHT);
//  delay(1000);

  Serial.println("All on.");
  turn_all_on();
  delay(1000);
  Serial.println("All off.");
  turn_all_off();
  delay(1000);
}

void loop() {
  Serial.println("Entering sequence.");
  do_parking_sequence();
  Serial.println("Exiting.");
}
