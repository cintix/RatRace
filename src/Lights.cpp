#include  <Lights.h>
/**
 *  Initiliazing static varibles
 */
bool Lights::isLed=false;
bool Lights::isBreak=false;
bool Lights::isGo=false;
bool Lights::isStop=false;

/**
 * Constructor for Lights
 *  int _led pin index for a LED
 *  int _break pin index for the break led
 *  int _go pin index for the go led
 *  int _stop pin index for the stop led
 */
Lights::Lights(int _led, int _break, int _go, int _stop) {
    led = _led;
    break_led = _break;
    go_led = _go;
    stop_led = _stop;

    pinMode (break_led, INPUT);
    pinMode (led, OUTPUT);
    pinMode (stop_led, OUTPUT);
    pinMode (go_led, OUTPUT);

}

/**
 *  handle function - handles commands from the interface
 *  String cmd - command from the interface
 */
void Lights::handle(String cmd) {
    if (cmd == "SL070") {
        Lights::isStop = false;
        digitalWrite (Lights::stop_led, LOW);
    }

    if (cmd == "SL051") {
        Lights::isStop = true;
        digitalWrite (Lights::stop_led, HIGH);
    }

    if (cmd == "SL060") {
        Lights::isGo = false;
        digitalWrite (Lights::go_led, LOW);
    }

    if (cmd == "SL061") {
        Lights::isGo = true;
        digitalWrite (Lights::go_led, HIGH);
    }
}
