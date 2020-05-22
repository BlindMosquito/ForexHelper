//+------------------------------------------------------------------+
//|                                                       Daubin.mq4 |
//|                        Copyright 2020, MetaQuotes Software Corp. |
//|                                             https://www.mql5.com |
//+------------------------------------------------------------------+
#include "Trader.mqh"
#property strict

const int time = 3600;
const int period = PERIOD_H1;
const string symbol = "USDJPY";
Trader trader(symbol, period);
int h = 0;
//+------------------------------------------------------------------+
//| Expert initialization function                                   |
//+------------------------------------------------------------------+
int OnInit()
  {
//--- create timer
   EventSetTimer(time);
   
//---
   return(INIT_SUCCEEDED);
  }
//+------------------------------------------------------------------+
//| Expert deinitialization function                                 |
//+------------------------------------------------------------------+
void OnDeinit(const int reason)
  {
//--- destroy timer
   EventKillTimer();
   
  }
//+------------------------------------------------------------------+
//| Expert tick function                                             |
//+------------------------------------------------------------------+
void OnTick() {
//---
   int hTemp = TimeHour(TimeCurrent());
   if(hTemp == h) return;
   h = hTemp;
   trader.Calculate(true);
   
}
//+------------------------------------------------------------------+
//| Timer function                                                   |
//+------------------------------------------------------------------+
void OnTimer() {

   
//---
   /*int direction = base.Calculate();

   if(direction == 0) return;
   
   int file= FileOpen("test.txt", FILE_READ|FILE_WRITE|FILE_TXT);
   FileSeek(file, 0, SEEK_END);
   FileWriteString(file, "\n" + IntegerToString(direction));
   
   FileClose(file);
   */
  }
//+------------------------------------------------------------------+
//| 
//+------------------------------------------------------------------+

