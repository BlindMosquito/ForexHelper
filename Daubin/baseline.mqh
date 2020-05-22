#ifndef BASELINE_H
#define BASELINE_H

class Baseline {
   public:
      Baseline(string, int);
      int Calculate();
   private:
      int location;
      int period;
      string symbol;
      
      bool BaseTrend(double base, double close);
};

#endif 