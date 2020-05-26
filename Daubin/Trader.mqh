#ifndef TRADER_H
#define TRADER_H

#include "baseline.mqh"
#include "ExitIndicator.mqh"
#include "SellTicket.mqh"
#include "BuyTicket.mqh"
#include "VolumeIndicator.mqh"

class Trader {
   public:
      Trader(const string, int);
      ~Trader();
      bool Calculate(bool canTrade);
   private:
      // Properties
      string symbol;
      int period;
      bool inProgress;        // Tests if a trade is open

      // Class Variables 
      Baseline * base;        // Baseline tells if ready to buy or sell
      VolumeIndicator * volume;  // Determines the volume
      ExitIndicator * exit;   // Exit Indicator
      OrderTicket * order;    // Makes a Long or Short Order
      
      // Functions
      bool TestExistOrder();    // Test Order if it exists
      bool TestNewOrder(bool canTrade);      // Test If New Order can happen
};

#endif 