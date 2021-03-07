#include <Interface.h>

Interface::Interface() {
    Serial.begin (9600);
}

Interface::Interface(int _baudrate) {
    Serial.begin (_baudrate);
}

bool Interface::update() {
    return Serial.available();
}

String Interface::getAction() {
    if (update()) {
        String junk = Serial.readStringUntil ('[');
        String cmd = Serial.readStringUntil (']');
        return cmd;
    }
    return "";
}
// - [PO01010]
void Interface::write(String cmd) {
    Serial.println(cmd);
}
