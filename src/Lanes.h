#include <Arduino.h>
#include <Power.h>

#ifndef Lanes_h
#define Lanes_h

class Lanes {
public:
    Lanes(int * _lanes, int count);
    void update(Power &power);
    void handle(String cmd);
    void setPenaltyTime(int value);
    void setMinimumSpeederPower(int value);
private:
    int lanesCount;
    int *lanes;
    int penaltyTimeoutValue;
    bool *laneStatus;
    bool *laneFlag;
    bool *penalty;
    unsigned long *roundTrips;
    unsigned long *penaltyTimeout;
    unsigned long minimumRoundTime = 100;
    int minimumSpeederPower = 250;
    unsigned long currentGoTime;
    bool waitingToGo = false;
    bool startGiven = false;
private:
    void validateFalseStart(Power &power);
};

#endif
