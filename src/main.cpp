#include <Arduino.h>
#include <Interface.h>
#include <Lights.h>
#include <Lanes.h>

//[PW010101]

int relePins[] = {6, 7, 8, 9}; // all pins in order for reles
int lanePins[] = {2, 3, 4, 5}; // all pins in order for lanes

Interface interface(9600);     // interface(baudrate) to talk to PCLapCounter
Lights lights(13, 10, 11, 12); // LED, Break, GO, STOP
Lanes lanes(lanePins, relePins, 4);

void setup() {
  lanes.setPenaltyTime(3000); // 3 seconds penalty for false start.
  lanes.setMinimumSpeederPower(250);
}

void loop() {
  // read lanes senors and validate false start
  lanes.update();

  // handle input from PCLapCounter
  if (interface.update()) {
    String action = interface.getAction();
    lanes.handle(action);
    lights.handle(action);
  }
}
