#include <Lanes.h>
#include <Lights.h>
#include <Interface.h>
#define ASCII 48

/**
 * Constructor for Lanes
 * int *_lanes - references to pin array on Arduino
 * int count   - amount of pins on array
 */
Lanes::Lanes(int *_lanes, int *_rele, int count) {
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

  rele = _rele;
  bool _powerIndex[count];
  powerIndex = _powerIndex;

  for (int index = 0; index < count; index++) {
    pinMode(rele[index], OUTPUT);
    powerIndex[index] = false;
  }

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

    if (cmd.startsWith("PW0")) {
      int _index = asciiToInt(cmd.charAt(3) - 1);
      int _onOrOff = asciiToInt(cmd.charAt(4));

      if (_onOrOff == 1 && laneHasPenalty(_index)) {
        _onOrOff = 0;
      }

      if (_onOrOff == 1) {
        powerIndex[_index] = true;
        digitalWrite(rele[_index], LOW);
      } else {
        powerIndex[_index] = false;
        digitalWrite(rele[_index], HIGH);
      }
    }

}

/**
 * update function
 * Reads state of the PINs from Arduino
 * Power power - reference to power control.
 */
void Lanes::update() {

    for (int index = 0; index < lanesCount; index++) {
        laneStatus[index] = (digitalRead(lanes[index]) == HIGH) ? true : false;
    }

    for (int index = 0; index < lanesCount; index++) {
      digitalWrite(lanes[index],(falseStart.validateLane(lanes[index], index)) ? HIGH : LOW);
    }

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

/**
 * asciiToInt function - converts a single Ascii character to a int
 * char c - character to convert
 */
int Lanes::asciiToInt(char c) {
  int value = int(c - ASCII);
  return value;
}

/**
 * trackHasPower function
 * int index - pin index number.
 * returns if the requested index is HIGH
 */
bool Lanes::trackHasPower(int index) { return powerIndex[index]; }

/**
 * delayedTurnOffPower function sets index pin LOW
 * int _delay - time in milleseconds to delay the command
 * int index - pin index number.
 */
void Lanes::delayedTurnOffPower(int _delay, int index) {
  delay(_delay);
  turnOffPower(index);
}

/**
 * delayedTurnOnPower function sets index pin HIGH
 * int _delay - time in milleseconds to delay the command
 * int index - pin index number.
 */
void Lanes::delayedTurnOnPower(int _delay, int index) {
  delay(_delay);
  turnOnPower(index);
}

/**
 * turnOffPower function sets index pin LOW
 * int index - pin index number.
 */
void Lanes::turnOffPower(int index) {
  powerIndex[index] = false;
  digitalWrite(rele[index], LOW);
}

/**
 * turnOnPower function sets index pin HIGH
 * int index - pin index number.
 */
void Lanes::turnOnPower(int index) {
  powerIndex[index] = false;
  digitalWrite(rele[index], HIGH);
}