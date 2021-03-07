#include <FalseStart.h>
#include <Interface.h>

/**
 * setup function
 * setups internal references for penalty arrays
 */
void FalseStart::setup(int size) {
    bool _penalty[size];
    penalty = _penalty;

    lanesCount = size;
    unsigned long _penaltyTimeout[size];
    penaltyTimeout = _penaltyTimeout;
}

/**
 * setPenaltyTime function
 * Define amount of time a penalty is going to last
 */
void FalseStart::setPenaltyTime(int value) {
    penaltyTimeoutValue = value;
}

/**
 * setMinimumSpeederPower function
 * Define amount of power present on the speeder, before triggering falsestart
 */
void FalseStart::setMinimumSpeederPower(int value) {
    minimumSpeederPower = value;
}

/**
 * handle function
 * Handle commands sent from the interface
 */
void FalseStart::handle(String cmd) {
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

/**
 * validateLanes function
 * Validates if a false start is being triggered.
 * int *lanes   - reference to lanes pins array
 *  Power power - reference to the power control
 */
void FalseStart::validateLanes(int *lanes, Power &power) {
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

/**
 * hasPenalty function
 * returns true if the current track index has a penalty
 */
bool FalseStart::hasPenalty(int index) {
    return penaltyTimeout[index] > 0;
}
