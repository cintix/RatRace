#include <Arduino.h>
#include <Interface.h>
#include <Power.h>
#include <Lights.h>
#include <Lanes.h>

//[PW010101]

int relePins[] = {6, 7, 8, 9}; // all pins in order for reles
int lanePins[] = {2, 3, 4, 5}; // all pins in order for lanes

Interface interface(9600); //interface(baudrate) to talk to PCLapCounter
Lights lights(13, 10 , 11, 12); // LED, Break, GO, STOP
Power power(relePins, 4);
Lanes lanes(lanePins, 4);

void setup() {}

void loop() {
  // read lanes senors snd validate false start
  lanes.update(power);

  // handle input from PCLapCounter
  if (interface.update()) {
    String action = interface.getAction();
    power.handle(action);
    lights.handle(action);
  }

}