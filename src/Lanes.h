#include <Arduino.h>
#include <Power.h>
#include <FalseStart.h>


#ifndef Lanes_h
#define Lanes_h

class Lanes {
public:
    Lanes(int * _lanes, int count);
    void update(Power &power);
    void handle(String cmd);
    void setPenaltyTime(int value);
    void setMinimumSpeederPower(int value);
    bool laneHasPenalty(int index);
private:
    FalseStart falseStart;
    int lanesCount;
    int *lanes;
    bool *laneStatus;
    bool *laneFlag;
    unsigned long *roundTrips;
    unsigned long minimumRoundTime = 100;
};

#endif
