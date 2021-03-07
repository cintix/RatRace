#include <Arduino.h>

#ifndef Lights_h
#define Lights_h

class Lights {
public:
    int led, break_led, go_led, stop_led;
    static bool isLed, isBreak, isGo, isStop;
public:
    Lights(int _led, int _break, int _go, int _stop);
    void handle(String cmd);
};

#endif
