#include <Lanes.h>
#include <Lights.h>
#include <Interface.h>

Lanes::Lanes(int *_lanes, int count) {
  lanesCount = count;
  lanes = _lanes;

  bool _laneStatus[count];
  laneStatus = _laneStatus;

  bool _laneFlag[count];
  laneFlag = _laneFlag;

  bool _penalty[count];
  penalty = _penalty;

  unsigned long _roundTrips[count];
  roundTrips = _roundTrips;

  unsigned long _penaltyTimeout[count];
  penaltyTimeout = _penaltyTimeout;

  for (int index = 0; index < count; index++) {
      pinMode(lanes[index], INPUT);
      laneStatus[index] = (digitalRead(lanes[index]) == HIGH) ? true : false;
  }
  
}

void Lanes::setMinimumSpeederPower(int value) {
  minimumSpeederPower = value;
}

void Lanes::setPenaltyTime(int value) {
    penaltyTimeoutValue = value;
}

void Lanes::handle(String cmd) {
     if (cmd =="SL051") {
         waitingToGo = true;
     }

     if (cmd =="SL070") {
         waitingToGo = false;
     }

     if (cmd =="SL060") {
         startGiven = false;
     }

     if (cmd =="SL061") {
         startGiven = true;
         currentGoTime = millis();
     }
}


void Lanes::update(Power &power) {

  for (int index = 0; index < lanesCount; index++) {
      laneStatus[index] = (digitalRead(lanes[index]) == HIGH) ? true : false;
  }

  validateFalseStart(power);

  if (Lights::isGo || Lights::isStop) {
     unsigned long currentTime = millis();
     if (Lights::isGo) {
       for (int index = 0; index < lanesCount; index++) {
          unsigned long currentRoundTrip = currentTime - roundTrips[index];
          if (laneStatus[index] && !laneFlag[index]  && (currentRoundTrip > minimumRoundTime)) {
              laneFlag[index] = true;
              roundTrips[index] = currentTime;

              char buf[6];
              sprintf(buf,"[SF0%d]", index +1);
              Interface::write(buf);
          }
       }

     }

     for (int index = 0; index < lanesCount; index++) {
        unsigned long currentRoundTrip = currentTime - roundTrips[index];
        if (!laneStatus[index] && laneFlag[index]  && (currentRoundTrip > minimumRoundTime)) {
            laneFlag[index] = false;
            roundTrips[index] = currentTime;
        }
     }

  }

}

void Lanes::validateFalseStart(Power &power) {
    for (int index = 0; index < lanesCount; index++) {
        if (!startGiven && waitingToGo && penaltyTimeout[index] < 1) {
            power.turnOnPower(index);
            if (analogRead(lanes[index]) > minimumSpeederPower) {
                penaltyTimeout[index] = penaltyTimeoutValue;
                power.turnOffPower(index);

                char buf[6];
                sprintf(buf,"[SF0%d]", index +1);
                Interface::write(buf);
            }
        }

        unsigned long currentTimeNow = millis();
        if (!waitingToGo && startGiven && penaltyTimeout[index] > 0) {
            if (penaltyTimeout[index] < (currentTimeNow - currentGoTime)) {
                penaltyTimeout[index] = 0;
                power.turnOnPower(index);
            }
        }
    }
}
