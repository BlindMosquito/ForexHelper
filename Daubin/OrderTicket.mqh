#ifndef ORDER_TICKET_H
#define ORDER_TICKET_H

#include "Atr.mqh"

// Had everything for this in the Trader Class
// Seemed easier in the long run to keep things more split up
// This is the parent clas to either go long or short on an order
// This is an Abstract Parent Class
class OrderTicket {
   public:
      OrderTicket(string symbol, int period);   // Constructor
      virtual ~OrderTicket();    // Deconstructor
      virtual bool Calculate();  // Tests if Ticket is still valid
      virtual bool Order() = 0;  // Starts the order process - Abstract Method
   protected:
      // Variables
      string symbol;             // The symbol for the currency pair
      int period;                // The period of the curriency pair tested
      bool open;                 // Keeps track if order is open
      int ticket;                // Ticket of Order
      double orderPrice;         // Price at Order
      double stopLoss;           // Current Stop Loss Price - Will Change With Trailing Stop Loss Once Take Profit achieved
      double takeProfit;         // Take Profit Determined at Order - Same as Stop Loss at Order
      double current;            // The last price of the market when checked. Used in conjunction with trailing stop
      double lot;                // The current lot bought or sold
      // Class variables
      Atr * atr;                 // Atr class pointer - Will need to have deconstructor for this
      
      // Functions
      void ResetVariables();     // Resets all the trade variables back to 0;
      virtual void TestStopLoss() = 0;       // Tests the stop loss;
};

#endif