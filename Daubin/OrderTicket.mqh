#ifndef ORDER_TICKET_H
#define ORDER_TICKET_H

#include "Atr.mqh"

// Had everything for this in the Trader Class
// Seemed easier in the long run to keep things more split up
// This is the parent clas to either go long or short on an order
// This is an Abstract Parent Class
class OrderTicket {
   public:
      OrderTicket(const string, int);   // Constructor
      virtual ~OrderTicket();    // Deconstructor
      virtual bool Calculate();  // Tests if Ticket is still valid
      bool Order();              // Starts the order process - Abstract Method
      void ForceClose();         // Force Close the Order
   protected:
      // Variables
      string symbol;             // The symbol for the currency pair
      int period;                // The period of the curriency pair tested
      bool open;                 // Keeps track if order is open
      int ticket;                 // Ticket of Order
      double orderPrice;         // Price at Order
      double stopLoss;           // Current Stop Loss Price
      double takeProfit;         // Take Profit Determined at Order - Same as Stop Loss at Order
      double lot;                // The current lot bought or sold
      bool stopMove;             // True if price has been adjusted
      // Class variables
      Atr * atr;                 // Atr class pointer - Will need to have deconstructor for this
      
      // Functions
      void ResetVariables();     // Resets all the trade variables back to 0;
      bool TestTicket();         // Test if Ticket is open
      virtual bool AdjustStopLoss() = 0;     // Adjust your stoploss
      virtual bool OrderChild() = 0;  // For the child to create order
      virtual bool ChildClose() = 0;   // Close the open order
};

#endif