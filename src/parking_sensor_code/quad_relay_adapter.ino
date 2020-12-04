#include "parking_sensor_code.h"

SoftwareWire myWire;

void initialize_wire(SoftwareWire myConstructedWire) {
  myWire = myConstructedWire;
}

void write_to_relay(int command) {
  myWire.beginTransmission(QUAD_DEFAULT_ADDRESS); 
  myWire.write(command);
  myWire.endTransmission();  
}

int read_command(int command) {
  write_to_relay(command);

  myWire.requestFrom(QUAD_DEFAULT_ADDRESS, 1);  
  int status = myWire.read();
  return(status);
}

void turn_all_on() {
  write_to_relay(TURN_ALL_ON);
}

void turn_all_off() {
  write_to_relay(TURN_ALL_OFF);
}

void toggle_relay(int relay) {
  if (relay == RELAY_ONE)
    write_to_relay(TOGGLE_RELAY_ONE);
  if (relay == RELAY_TWO)
    write_to_relay(TOGGLE_RELAY_TWO);
  if (relay == RELAY_THREE)
    write_to_relay(TOGGLE_RELAY_THREE);
  if (relay == RELAY_FOUR)
    write_to_relay(TOGGLE_RELAY_FOUR);
}

int get_relay_state(int relay) {
  int status; 
  if (relay == RELAY_ONE)
    status =  read_command(RELAY_ONE_STATUS);
  else if (relay == RELAY_TWO)
    status =  read_command(RELAY_TWO_STATUS);
  else if (relay == RELAY_THREE)
    status =  read_command(RELAY_THREE_STATUS);
  else if (relay == RELAY_FOUR)
    status =  read_command(RELAY_FOUR_STATUS);
  else
    return -1;
  
  if (status == QUAD_RELAY_ON) // Relay status should be consistent
    return 1; // Relay on
  else
    return QUAD_RELAY_OFF;
}

void set_relay_state(int relay, int desired_state) {
  int status = get_relay_state(relay);

  if (status == desired_state)
    return;

  toggle_relay(relay);
}

void turn_relay_on(int relay) {
  if (relay == RELAY_ONE)
    set_relay_state(RELAY_ONE, QUAD_RELAY_ON);
  if (relay == RELAY_TWO)
    set_relay_state(RELAY_TWO, QUAD_RELAY_ON);
  if (relay == RELAY_THREE)
    set_relay_state(RELAY_THREE, QUAD_RELAY_ON);
  if (relay == RELAY_FOUR)
    set_relay_state(RELAY_FOUR, QUAD_RELAY_ON);
}

void turn_relay_off(int relay) {
  if (relay == RELAY_ONE)
    set_relay_state(RELAY_ONE, QUAD_RELAY_OFF);
  if (relay == RELAY_TWO)
    set_relay_state(RELAY_TWO, QUAD_RELAY_OFF);
  if (relay == RELAY_THREE)
    set_relay_state(RELAY_THREE, QUAD_RELAY_OFF);
  if (relay == RELAY_FOUR)
    set_relay_state(RELAY_FOUR, QUAD_RELAY_OFF);
}
