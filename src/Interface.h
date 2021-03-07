#include <Arduino.h>

#ifndef Interface_h
#define Interface_h

class Interface {
public:
    Interface();
    Interface(int _baudrate);
    bool update();
    String getAction();
    static void write(String cmd);
};
#endif
