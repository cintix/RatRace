#include <Arduino.h>
#include <Lanes.h>

#ifndef Power_h
#define Power_h

class Power {
private:
    void setup(int size);
private:
    int asciiToInt(char c);
public:
    int *rele;
    bool *powerIndex;
public:
    Power(int *_rele, int count);
    bool trackHasPower(int index);
    void turnOffPower(int index);
    void turnOnPower(int index);
    void handle(Lanes &lane, String cmd);
};

#endif
