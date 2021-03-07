#include <Interface.h>

/**
*  Default Constructor for interfaces
*/
Interface::Interface() {
    Serial.begin (9600);
}

/**
* Constructor for interfaces
* int _baudrate is the wanted baudrate ex. 9600S
*/
Interface::Interface(int _baudrate) {
    Serial.begin (_baudrate);
}

/**
*  Update funtion
*  returns true of there is an update from the interface
*/
bool Interface::update() {
    return Serial.available();
}

/**
* getAction
* returns action command sent from the interface
*/
String Interface::getAction() {
    if (update()) {
        String junk = Serial.readStringUntil ('[');
        String cmd = Serial.readStringUntil (']');
        return cmd;
    }
    return "";
}

/**
* write fucntion
* String cmd is command  being sent to the interface
*/
void Interface::write(String cmd) {
    Serial.println(cmd);
}
