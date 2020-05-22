#include "Trader.mqh"

Trader::Trader(string symbol, int period) : symbol(symbol), period(period), progress(0), ticket(0), stopLoss(0), current(0), lot(0) { 
   atr = new Atr(symbol, period);
   base = new Baseline(symbol, period);
}
Trader::~Trader() {
   if(atr) delete atr;
   if(base) delete base;
}
      
int Trader::Calculate(bool canTrade) {

   
   int status = TestTicket();
   if(status > 0 || !canTrade) return status;
   
   // No Order Should Be in Place By This Time, and Program is ok with another trade
   status = base.Calculate();                            // Think -1 means to buy and 1 means to sell
   if(status == 0) return 0;                             // Not time to buy or sell
   double mfi = iMFI(symbol, period, 14, 0);
   if(mfi < 40) return 0;
   if(status == -1 && BuyOrder()) return 1;
   if(status == 1 && SellOrder()) return 1;
   return 0;
}
      
bool Trader::BuyOrder() {
   double ask = MarketInfo(symbol, MODE_ASK);
   double lotTemp = atr.LotSize();
   double stopTemp = atr.SellRisk();
   ticket = OrderSend(symbol, OP_BUY, lotTemp, ask, 3, stopTemp, 0);
   if(ticket == 0) return false;
   progress = 1;
   stopLoss = stopTemp;
   current = ask;
   lot = lotTemp;
   return true;
}
bool Trader::SellOrder() {
   double ask = MarketInfo(symbol, MODE_BID);
   double lotTemp = atr.LotSize();
   double stopTemp = atr.BuyRisk();
   ticket = OrderSend(symbol, OP_SELL, lotTemp, ask, 3, stopTemp, 0);
   if(ticket == 0) return false;
   progress = -1;
   stopLoss = stopTemp;
   current = ask;
   lot = lotTemp;
   return true;
}

int Trader::TestTicket() {
   if(progress == 0) return 0;
   if(!OrderSelect(ticket, SELECT_BY_TICKET)) {
      ticket = 0;
      progress = 0;
      stopLoss = 0;
      current = 0;
      lot = 0;
      return 0;     // Ticket does not exist
   }
   if(!OrderCloseTime()) {                               // Ticket has no close time so order is open
      if(progress > 0) TrailStopBuy();
      else if(progress < 0) TrailStopSell();
      return 1;
   }
   ticket = 0;
   progress = 0;
   stopLoss = 0;
   current = 0;
   lot = 0;
   return 0;                                            // Order must be clsoed
}

void Trader::TrailStopBuy()  { 
   if(ticket == 0 || progress == 0 || stopLoss == 0 || current == 0 || lot == 0) return;
   double ask = MarketInfo(symbol, MODE_ASK);
   if(ask <= current) return;
   double stopTemp = stopLoss + (ask - current);
   if(OrderModify(ticket, 0, stopTemp, 0, 0)) {
      stopLoss = stopTemp;
      current = ask;
   }
}
void Trader::TrailStopSell() { 
   if(ticket == 0 || progress == 0 || stopLoss == 0 || current == 0 || lot == 0) return;
   double ask = MarketInfo(symbol, MODE_ASK);
   if(ask >= current) return;
   double stopTemp = stopLoss - (current - ask);
   if(OrderModify(ticket, 0, stopTemp, 0, 0)) {
      stopLoss = stopTemp;
      current = ask;
   }
}
