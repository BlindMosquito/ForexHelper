#include "OrderTicket.mqh"

OrderTicket::OrderTicket(const string txt, int time) : symbol(txt), period(time), stopMove(false) { ResetVariables(); atr = new Atr(symbol, period); }
OrderTicket::~OrderTicket() { if(atr) delete atr; ForceClose(); }

// Tests if there is an open ticket
bool OrderTicket::Calculate() {
      if(!ticket) return false;                 // If ticket does not exist return false
      if(!TestTicket()) return false;           // If ticket is now closed then leave
      AdjustStopLoss();
      return true;
}

// Resets all the trade variables back to 0;
void OrderTicket::ResetVariables() {
      open = false;
      ticket = 0;
      orderPrice = 0;
      stopLoss = 0;
      takeProfit = 0;
      lot = 0;
}

// Tests if ticket is still open
bool OrderTicket::Order() {
      if(ticket) return true;                         // Should be no ticket
      return OrderChild();                            // Call child to place order
}

// Tests if Ticket is still Open
// Should have a ticket number by this point
bool OrderTicket::TestTicket() {
      if(OrderSelect(ticket, SELECT_BY_TICKET)) { // See if order has a close time
            // I am assuming that partial closed orders will still return a 0
            if(!OrderCloseTime()) return true;
      }
      ResetVariables();                         // Reset everything if order is closed
      return false;
}


// Force Close the Order
// Don't know why, but do not leave order open
void OrderTicket::ForceClose() {
      if(ticket)
      ChildClose();
}