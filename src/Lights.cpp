#include  <Lights.h>

bool Lights::isLed=false;
bool Lights::isBreak=false;
bool Lights::isGo=false;
bool Lights::isStop=false;

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

void Lights::handle(String cmd) {

    if (cmd == "SL070") {
        Lights::isStop = false;
//    digitalWrite (Lights::stop_led, LOW);
    }

    if (cmd == "SL051") {
        Lights::isStop = true;
//    digitalWrite (Lights::stop_led, HIGH);
    }

    if (cmd == "SL060") {
        Lights::isGo = false;
//    digitalWrite (Lights::go_led, LOW);
    }

    if (cmd == "SL061") {
        Lights::isGo = true;
//    digitalWrite (Lights::go_led, HIGH);
    }


}
