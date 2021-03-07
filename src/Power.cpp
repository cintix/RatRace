#include <Power.h>
#define ASCII 48

Power::Power(int * _rele, int count) {
    rele = _rele;
    bool _powerIndex[count];
    powerIndex = _powerIndex;
    setup(count);
}

void Power::setup(int size) {
    for(int index = 0; index < size; index++) {
        pinMode(rele[index], OUTPUT);
        powerIndex[index] = false;
    }
}

bool Power::trackHasPower(int index) {
    return powerIndex[index];
}

void Power::turnOffPower(int index) {
    //  Serial.print(printf("Turning off power to index %d\n", index));
    powerIndex[index] = false;
//    digitalWrite(rele[index], LOW);
}

void Power::turnOnPower(int index) {
    powerIndex[index] = false;
//    digitalWrite(rele[index], HIGH);
}

void Power::handle(String cmd) {

    if (cmd.startsWith("PW0")) {
        int _index   = asciiToInt(cmd.charAt(3)-1);
        int _onOrOff = asciiToInt(cmd.charAt(4));

        if(_onOrOff == 1) {
            powerIndex[_index] = true;
//      digitalWrite(rele[_index], LOW);
        } else  {
            powerIndex[_index] = false;
//      digitalWrite(rele[_index], HIGH);
        }

    }

}

int  Power::asciiToInt(char c) {
    int value = int(c-ASCII);
    return value;
}
