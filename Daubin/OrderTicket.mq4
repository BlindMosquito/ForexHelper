#include "OrderTicket.mqh"

OrderTicket::OrderTicket(string symbol, int period) : symbol(symbol), period(period) { ResetVariables(); atr = new Atr(); }
OrderTicket::~OrderTicket() { if(atr) delete atr; }

// Tests if there is an open ticket
bool OrderTicket::Calculate() {
      if(!ticket) return false;                 // If ticket does not exist return fals
      if(!TestTicket()) return false;           // If ticket is now closed then leave
      TestStopLosss();                          // Test if Stop loss needs to change
      return true;
}

// Resets all the trade variables back to 0;
void OrderTicket::ResetVariables() {
      open = false;
      ticket = 0;
      orderPrice = 0;
      stopLoss = 0;
      trail = false;
      takeProfit = 0;
      current = 0;
      lot = 0;
}

// Tests if ticket is still open
bool OrderTicket::Order() {
      if(ticket) return true;                         // Should be no ticket
      double mfi = iMFI(symbol, period, 14, 0);       // Get momentum of candle
      if(mfi < 40) return false;                      // Momentum should be over value
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