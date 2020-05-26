#include "BuyTicket.mqh"

BuyTicket::BuyTicket(const string txt, int time) : OrderTicket(txt, time) { }

// Signal went through that it is ready to buy
bool BuyTicket::OrderChild() {
    double ask = MarketInfo(symbol, MODE_ASK);  // Get Ask Price
    double lotTemp = atr.LotSize();             // Get Total Lots
    double lossTemp = atr.SellRisk();           // Get Stop Loss Price
    double profitTemp = atr.BuyProfit();          // Get Stop Profit Price
    ticket = OrderSend(symbol, OP_BUY, lotTemp, ask, 3, lossTemp, 0); // Place order
    if(!ticket) return false;                   // If order failed leave
    // Ticket has been placed by this point
    open = true;
    orderPrice = ask;
    stopLoss = lossTemp;
    takeProfit = profitTemp;
    lot = lotTemp;
    return true;
}


// Adjust your stoploss
bool BuyTicket::AdjustStopLoss() {
   double bid = MarketInfo(symbol, MODE_BID);      // Use bid as that will be the sell price
   if(bid < takeProfit) return false;              // If bid is less than takeProfit return
   double tTakeProfit = atr.BuyProfit();             // Temp Take Profit
   double tStopLoss;                               // temp stop loss
   if(!stopMove) {                                 // Is this first move
      tStopLoss = orderPrice;
   } else {
      tStopLoss = stopLoss + (tTakeProfit - stopLoss);
   }
   if(!OrderModify(ticket, 0, tStopLoss, 0, 0)) return false;
   stopLoss = tStopLoss;
   takeProfit = tTakeProfit;
   stopMove = true;
   return stopMove;
}

// Close open orders
bool BuyTicket::ChildClose() {
   double price = MarketInfo(symbol, MODE_BID);
   return OrderClose(ticket, lot, price, 5);
}
