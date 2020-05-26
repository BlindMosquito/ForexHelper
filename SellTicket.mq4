#include "SellTicket.mqh"

SellTicket::SellTicket(const string txt, int time) : OrderTicket(txt, time) { }

// Signal went through that it is ready to buy
bool SellTicket::OrderChild() {
    double bid = MarketInfo(symbol, MODE_BID);  // Get bid Price
    double lotTemp = atr.LotSize();             // Get Total Lots
    double lossTemp = atr.BuyRisk();           // Get Stop Loss Price
    double profitTemp = atr.SellProfit();          // Get Stop Profit Price
    ticket = OrderSend(symbol, OP_SELL, lotTemp, bid, 3, lossTemp, 0); // Place order
    if(!ticket) return false;                   // If order failed leave
    // Ticket has been placed by this point
    open = true;
    orderPrice = bid;
    stopLoss = lossTemp;
    takeProfit = profitTemp;
    lot = lotTemp;
    return true;
}

// Adjust your stoploss
bool SellTicket::AdjustStopLoss() {
   double ask = MarketInfo(symbol, MODE_ASK);      // Use ask as that will be the sell price
   if(ask > takeProfit) return false;              // If ask is more than takeProfit return
   double tTakeProfit = atr.SellProfit();             // Temp Take Profit
   double tStopLoss;                               // temp stop loss
    if(!stopMove) {                                 // Is this first move
      tStopLoss = orderPrice;
   } else {
      tStopLoss = stopLoss - (stopLoss - tTakeProfit);
   }
   if(!OrderModify(ticket, 0, tStopLoss, 0, 0)) return false;
   stopLoss = tStopLoss;
   takeProfit = tTakeProfit;
   stopMove = true;
   return stopMove;
}

// Close open orders
bool SellTicket::ChildClose() {
   return OrderClose(ticket, lot, MarketInfo(symbol, MODE_ASK), 5);
}