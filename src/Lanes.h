#include <Arduino.h>

#ifndef Lanes_h
#define Lanes_h
#include <FalseStart.h>

class Lanes {
public:
  Lanes(int *_lanes, int *_rele, int count);
  void update();
  void handle(String cmd);
  void setPenaltyTime(int value);
  void setMinimumSpeederPower(int value);
  bool laneHasPenalty(int index);
  bool trackHasPower(int index);
  void turnOffPower(int index);
  void turnOnPower(int index);
  void delayedTurnOnPower(int _delay, int index);
  void delayedTurnOffPower(int _delay, int index);
private:
    FalseStart falseStart;
    int lanesCount;
    int *lanes;
    bool *laneStatus;
    bool *laneFlag;
    int *rele;
    bool *powerIndex;
    unsigned long *roundTrips;
    unsigned long minimumRoundTime = 100;
    int asciiToInt(char c);
};

#endif
