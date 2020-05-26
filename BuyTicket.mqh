#ifndef Buy_TICKET_H
#define Buy_TICKET_H

#include "OrderTicket.mqh"

// Child class for Order Ticket
// Used for going long on an order
class BuyTicket: public OrderTicket {
   public:
      BuyTicket(const string, int);   // Constructor
      
   protected:
      bool OrderChild();
      bool AdjustStopLoss();        // Adjust your stoploss
      bool ChildClose();            // Close open orders
};

#endif