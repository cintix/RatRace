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
 * validateLane function
 * Validates if a false start is being triggered.
 * int lane   - reference to lanes pins array
 */
bool FalseStart::validateLane(int lanePin, int laneIndex) {

    if (!startGiven && waitingToGo && penaltyTimeout[laneIndex] < 1) {
      if (analogRead(lanePin) > minimumSpeederPower) {
        penaltyTimeout[laneIndex] = penaltyTimeoutValue;
        char buf[6];
        sprintf(buf, "[SF0%d]", laneIndex + 1);
        Interface::write(buf);
        return false;
      }
    }

    unsigned long currentTimeNow = millis();
    if (!waitingToGo && startGiven && penaltyTimeout[laneIndex] > 0) {
      if (penaltyTimeout[laneIndex] < (currentTimeNow - currentGoTime)) {
        penaltyTimeout[laneIndex] = 0;
        return true;
      }
    }
  
  return true;
}

/**
 * hasPenalty function
 * returns true if the current track index has a penalty
 */
bool FalseStart::hasPenalty(int index) {
    return penaltyTimeout[index] > 0;
}
