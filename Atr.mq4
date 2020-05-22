#include "Atr.mqh"
const double PIP_DISPLACE = 1.3;
const double MAX_RISK = .02;

Atr::Atr(const string txt, int time) : symbol(txt), period(time) { }
double Atr::Calculate() { 
   return iATR(symbol, period, 14, 0);
}
double Atr::CalculateRisk() { return Calculate() * PIP_DISPLACE; }

double Atr::BuyRisk() {
   double bid = MarketInfo(symbol, MODE_BID);
   return bid + CalculateRisk();
}
double Atr::SellRisk() {
   double bid = MarketInfo(symbol, MODE_BID);
   return bid - CalculateRisk();
}
double Atr::GetPips() {
   double atr = Calculate();
   return atr * MathPow(10, MarketInfo(symbol, MODE_DIGITS)-1);
}
double Atr::GetPipsRisk() {
  return GetPips() * PIP_DISPLACE;
}
double Atr::LotSize() {
   double tick_value = MarketInfo(symbol, MODE_TICKVALUE);
   // Author from https://mql4tradingautomation.com/mql4-calculate-position-size/
   double risk = AccountBalance()*MAX_RISK;
   double stopTick = GetPipsRisk() * tick_value;
   return risk / stopTick / 10;
}