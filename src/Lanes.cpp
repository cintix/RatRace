#include <Lanes.h>
#include <Lights.h>
#include <Interface.h>

/**
 * Constructor for Lanes
 * int *_lanes - references to pin array on Arduino
 * int count   - amount of pins on array
 */
Lanes::Lanes(int *_lanes, int count) {
    lanesCount = count;
    lanes = _lanes;

    bool _laneStatus[count];
    laneStatus = _laneStatus;

    bool _laneFlag[count];
    laneFlag = _laneFlag;

    unsigned long _roundTrips[count];
    roundTrips = _roundTrips;

    for (int index = 0; index < count; index++) {
        pinMode(lanes[index], INPUT);
        laneStatus[index] = (digitalRead(lanes[index]) == HIGH) ? true : false;
    }

    falseStart.setup(count);
}

/**
 * hasPenalty function
 * returns true if the current track index has a penalty
 */
bool Lanes::laneHasPenalty(int index) {
    return falseStart.hasPenalty(index);
}

/**
 * setMinimumSpeederPower function
 * Define amount of power present on the speeder, before triggering falsestart
 */
void Lanes::setMinimumSpeederPower(int value) {
    falseStart.setMinimumSpeederPower(value);
}

/**
 * setPenaltyTime function
 * Define amount of time a penalty is going to last
 */
void Lanes::setPenaltyTime(int value) {
    falseStart.setPenaltyTime(value);
}

/**
 * handle function
 * Handle commands sent from the interface
 */
void Lanes::handle(String cmd) {
    falseStart.handle(cmd);
}

/**
 * update function
 * Reads state of the PINs from Arduino
 * Power power - reference to power control.
 */
void Lanes::update(Power &power) {

    for (int index = 0; index < lanesCount; index++) {
        laneStatus[index] = (digitalRead(lanes[index]) == HIGH) ? true : false;
    }

    falseStart.validateLanes(lanes, power);

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
