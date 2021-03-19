#include <Arduino.h>
#ifndef FalseStart_h
#define FalseStart_h
class FalseStart {
public:
    void setPenaltyTime(int value);
    void handle(String cmd);
    bool hasPenalty(int index);
    void setup(int size);
    bool validateLane(int lanePin, int laneIndex);
    void setMinimumSpeederPower(int value);
private:
  int lanesCount;
  bool *penalty;
  unsigned long *penaltyTimeout;
  int penaltyTimeoutValue;
  bool waitingToGo = false;
  bool startGiven = false;
  unsigned long currentGoTime;
  int minimumSpeederPower = 250;
};

#endif
