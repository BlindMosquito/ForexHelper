#include <windows.h>
#include "StrategyInterfaceUnit.h"
#include "TechnicalFunctions.h"
#include <ctime>


char* Currency = NULL;
int Timeframe;

EXPORT void InitStrategy() {
  StrategyShortName("ObjectsTest");
  StrategyDescription("Test of moving objects");

  RegOption("Currency", ot_Currency, &Currency);

  RegOption("Timeframe", ot_TimeFrame, &Timeframe);
  Timeframe = PERIOD_M15;
}

EXPORT void DoneStrategy() {
  free(Currency);
}

EXPORT void ResetStrategy() {}

EXPORT void GetSingleTick() {
    time_t now = time(0);
    tm* local = localtime(&now);
    int hour = local->tm_hour;
    int handle = 0;
    if (hour == 8 && OrdersTotal == 0) {
        double stopLoss = Ask() - (100* Point());
        double stopProfit = Ask() + (50* Point());

        SendInstantOrder(Symbol(), op_Buy, 0.1, stopLoss, stopProfit, "NA", 0, handle);
    }
    
}
