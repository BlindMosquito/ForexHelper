#ifndef VOLUMEINDICATOR_H
#define VOLUMEINDICATOR_H

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Abstract class to determine if enough volume is there for trade
///////////////////////////////////////////////////////////////////////////////////////////////////////
class VolumeIndicator {
   public:
      VolumeIndicator(const string, int);// Constructor
      virtual bool Calculate() = 0;    // Tests if trade should close
   protected:
      string symbol;                   // Currency Pair
      int period;                      // Timeframe testing
};
///////////////////////////////////////////////////////////////////////////////////////////////////////

class MomentumVolume : public VolumeIndicator {
   public:
      MomentumVolume(const string, int);   // Constructor
      bool Calculate();                   // True if able to buy, false if not enough volume
};
#endif 