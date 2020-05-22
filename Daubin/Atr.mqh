#ifndef ATR_H
#define ATR_H

class Atr{
   public:
      Atr(const string, int);
      double Calculate();
      double CalculateRisk();
      double BuyRisk();
      double SellRisk();
      double GetPips();
      double GetPipsRisk();
      double LotSize();
   private:
      string symbol;
      int period;
};

#endif