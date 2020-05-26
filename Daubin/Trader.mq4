#include "Trader.mqh"

// Constructor
Trader::Trader(const string txt, int time) : symbol(txt), period(time), inProgress(false), order(NULL), exit(NULL)  { 
   base = new MovingAverageBase(symbol, period);
   volume = new MomentumVolume(symbol, period);
}
// Deconstructor when program closes
Trader::~Trader() {
   if(base) delete base;               // delete the baseline
   if(volume) delete volume;           // delete volume if it exists
   if(exit) delete exit;               // Get rid of exit if it is open
   if(order) delete order;             // get rid of any open orders
}

// Called each interval of period time frame
// Returns 1 if trade is open or 0 if closed
// Number is then used to calculate how many trades are open
bool Trader::Calculate(bool canTrade) {
   if(TestExistOrder()) {           // Order is open if true
      if(!exit) {
         Print("Not sure why an exit is not available at this point");
         exit = new RviExit(symbol, period);
      }
      if(exit.Calculate()) {
         order.ForceClose();
         delete exit;                  // get rid of exit indicator
         return false;
      }
      return true;
   }
   //if(!volume.Calculate()) canTrade = false;
   if (TestNewOrder(canTrade)) {
      if(exit) delete exit;
      exit = new RviExit(symbol, period);
      return true;
   }return false;
}

// Test Order if it exists
bool Trader::TestExistOrder() {
   if(!order) return false;
   return order.Calculate();
}

// Test If New Order can happen
bool Trader::TestNewOrder(bool canTrade) {
   if(!canTrade) return false;            // if false then cannot trade
   int status = base.Calculate();             // test baseline
   if(status == 0) return false;          // if zero not time to trade
   if(order) {
      delete order;
   }
   if(status == 1) order = new BuyTicket(symbol, period);   // setup for Buy
   if(status == -1) order = new SellTicket(symbol, period); // setup for Sell
   return order.Order();                  // Setup new order
}
