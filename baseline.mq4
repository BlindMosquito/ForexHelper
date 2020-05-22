#include "baseline.mqh"

Baseline::Baseline(const string txt, int time) : location(0), period(time), symbol(txt) { }
int Baseline::Calculate() {
   double base = iIchimoku(symbol, period, 9, 26, 52, 2, 0);
   double close = Close[0];
   switch(location) {
      case -1:
         if(!BaseTrend(base, close)) return 0;
         location = 1;
         break;
      case 1:
         if(BaseTrend(base, close)) return 0;
         location = -1;
         break;
      case 0:
         if(BaseTrend(base, close)) location = 1;
         else location = -1;
         return 0;
   }
   return location;
}


bool Baseline::BaseTrend(double base, double close) {
   if (base < close) return false;
   return true;
}
