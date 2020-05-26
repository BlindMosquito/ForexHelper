//+------------------------------------------------------------------+
//|                                                       Daubin.mq4 |
//|                        Copyright 2020, MetaQuotes Software Corp. |
//|                                             https://www.mql5.com |
//+------------------------------------------------------------------+

// New version is using the chart for everything
// Since this can be attached to multiple charts
// Might not work on a remote computer so will keep things the same
// with the all the modular classes still accepting the symbol type in constructor.

#include "Trader.mqh"
#property strict

const int time = 3600;
const int period = Period();
const int symbol = Symbol();
Trader trader(Symbol(), Period());
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
   if(h > 16 || h < 4){
      trader.Calculate(false);
   }
   else {
      trader.Calculate(true);
   }
   
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

