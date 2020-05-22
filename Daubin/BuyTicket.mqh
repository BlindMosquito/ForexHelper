#ifndef Buy_TICKET_H
#define Buy_TICKET_H

#include "OrderTicket.mqh"

// Child class for Order Ticket
// Used for going long on an order
class BuyTicket: public OrderTicket {
   public:
      BuyTicket(string symbol, int period);   // Constructor
      bool Order();
      
   protected:
      void TestStopLoss();
};

#endif