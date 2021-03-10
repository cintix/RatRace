#include <Power.h>
#define ASCII 48

/**
* Constructor for Power
* int _rele is a reference to a array of arduino pins
* int count amount of pins in the array.
*/
Power::Power(int * _rele, int count) {
    rele = _rele;
    bool _powerIndex[count];
    powerIndex = _powerIndex;
    setup(count);
}

/**
 * setup function - setups pins on the arduino
 * int size -  amount of pins in the array.
 */
void Power::setup(int size) {
    for(int index = 0; index < size; index++) {
        pinMode(rele[index], OUTPUT);
        powerIndex[index] = false;
    }
}

/**
 * trackHasPower function
 * int index - pin index number.
 * returns if the requested index is HIGH
 */
bool Power::trackHasPower(int index) {
    return powerIndex[index];
}

/**
 * delayedTurnOffPower function sets index pin LOW
 * int _delay - time in milleseconds to delay the command
 * int index - pin index number.
 */
void delayedTurnOffPower(int _delay, int index){
    delay(_delay);
    turnOffPower(index);
}

/**
 * delayedTurnOnPower function sets index pin HIGH
 * int _delay - time in milleseconds to delay the command
 * int index - pin index number.
 */
void delayedTurnOnPower(int _delay, int index){
    delay(_delay);
    turnOnPower(index);
}

/**
 * turnOffPower function sets index pin LOW
 * int index - pin index number.
 */
void Power::turnOffPower(int index) {
    powerIndex[index] = false;
    digitalWrite(rele[index], LOW);
}

/**
 * turnOnPower function sets index pin HIGH
 * int index - pin index number.
 */
void Power::turnOnPower(int index) {
    powerIndex[index] = false;
    digitalWrite(rele[index], HIGH);
}

/**
 * handle function - reads commands from the interface
 * String cmd - command sent from interface.
 */
void Power::handle(Lanes &lane, String cmd) {

    if (cmd.startsWith("PW0")) {
        int _index   = asciiToInt(cmd.charAt(3)-1);
        int _onOrOff = asciiToInt(cmd.charAt(4));

        if (_onOrOff == 1 && lane.laneHasPenalty(_index)) {
            _onOrOff = 0;
        }

        if(_onOrOff == 1) {
            powerIndex[_index] = true;
            digitalWrite(rele[_index], LOW);
        } else  {
            powerIndex[_index] = false;
            digitalWrite(rele[_index], HIGH);
        }
    }
}

/**
 * asciiToInt function - converts a single Ascii character to a int
 * char c - character to convert
 */
int  Power::asciiToInt(char c) {
    int value = int(c-ASCII);
    return value;
}
