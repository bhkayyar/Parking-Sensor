#include <SharpIR.h>

#define green_input A0
#define yellow_input A1
#define red_input A2

#define model 1080
// ir: the pin where your sensor is attached
// model: an int that determines your sensor:  1080 for GP2Y0A21Y
//                                            20150 for GP2Y0A02Y
//                                            (working distance range according to the datasheets)

SharpIR green_sensor(green_input, model);
SharpIR yellow_sensor(yellow_input, model);
SharpIR red_sensor(red_input, model);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  delay(1000);   

  int dis_green=green_sensor.distance();
  int dis_yellow=yellow_sensor.distance();
  int dis_red=red_sensor.distance(); // this returns the distance to the object you're measuring
  
  Serial.print("Green distance: ");  // returns it to the serial monitor
  Serial.println(dis_green);
  
  Serial.print("Yellow distance: ");  // returns it to the serial monitor
  Serial.println(dis_yellow);
  
  Serial.print("Red distance: ");  // returns it to the serial monitor
  Serial.println(dis_red);
}
