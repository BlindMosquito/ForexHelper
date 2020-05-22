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
      // Properties
      string symbol;
      int period;
      int progress;           // 0 means no trade, -1 sell, 1 buy
      int ticket;             // the ticket belonging to the order
      double orderPrice;      // Keep track of price that was bought;
      double stopLoss;        // Keep track of stop loss for trail
      double takeProfit;      // Determine point to start trailing stop loss
      double current;         // Keep track of current price
      double lot;             // Lot size taken
      // Class Properties
      Atr * atr;              // Atr figures out pips and prices
      Baseline * base;        // Baseline tells if ready to buy or sell
      
      // Functions
      void ResetOrderVar();   // Resets the variables that have to do with orders
      bool BuyOrder();        // Buys a new order
      bool SellOrder();       // Sells a new order
      int TestTicket();       // Tests if ticket is still open
      void TrailStopBuy();    // Sets up a trailing stop loss if bought
      void TrailStopSell();   // Sets up a trailing stop loss if sold
};

#endif 