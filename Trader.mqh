#ifndef TRADER_H
#define TRADER_H

#include  "Atr.mqh"
#include  "baseline.mqh"

class Trader {
   public:
      Trader(string, int);
      ~Trader();
      int Calculate(bool canTrade);  //
   private:
      string symbol;
      int period;
      int progress;     // 0 means no trade, -1 sell, 1 buy
      int ticket;       // the ticket belonging to the order
      double stopLoss;  // Keep track of stop loss for trail
      double current;   // Keep track of current price
      double lot;       // lot size taken
      Atr * atr;
      Baseline * base;
      
      bool BuyOrder();
      bool SellOrder();
      int TestTicket();
      void TrailStopBuy();
      void TrailStopSell();
};

#endif 