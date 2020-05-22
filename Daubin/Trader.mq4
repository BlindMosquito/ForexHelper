#include "Trader.mqh"

// Constructor
Trader::Trader(string symbol, int period) : symbol(symbol), period(period), progress(0), ticket(0), 
   orderPrice(0), stopLoss(0), takeProfit(0), current(0), lot(0) { 
   atr = new Atr(symbol, period);
   base = new Baseline(symbol, period);
}
// Deconstructor when program closes
Trader::~Trader() {
   if(atr) delete atr;
   if(base) delete base;
}


// Resets the variables that have to do with orders
void Trader::ResetOrderVar() {
   progress = 0;
   ticket = 0;
   orderPrice = 0;
   stopLoss = 0;
   takeProfit = 0;
   current = 0;
   lot = 0;
}

// Called each interval of period time frame
// Returns 1 if trade is open or 0 if closed
// Number is then used to calculate how many trades are open
// Probabbly could work as a bool being just 0 or 1      
int Trader::Calculate(bool canTrade) {
   int status = TestTicket();                            // Get the status of any open orders
   if(status > 0 || !canTrade) return status;            // 
   
   // No Order Should Be in Place By This Time, and Program is ok with another trade
   status = base.Calculate();                            // Think -1 means to buy and 1 means to sell
   if(status == 0) return 0;                             // Not time to buy or sell
   double mfi = iMFI(symbol, period, 14, 0);
   if(mfi < 40) return 0;
   if(status == -1 && BuyOrder()) return 1;
   if(status == 1 && SellOrder()) return 1;
   return 0;
}

// Used To Buy a new Order   
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

// Used to Short a new order
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

// Used to test any open tickets
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

// Used to set the trailing stop loss if bought
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

// Used to set the trailing stop loss if shorted
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
