#include <windows.h>
#include "StrategyFunctions.h"
#include "TechnicalFunctions.h"
#include <ctime>


char* Currency = NULL;
int Timeframe;

EXPORT void InitStrategy() {
  StrategyFunctions::StrategyShortName("ObjectsTest");
  StrategyFunctions::StrategyDescription("Test of moving objects");

  StrategyFunctions::RegOption("Currency", ot_Currency, &Currency);

  StrategyFunctions::RegOption("Timeframe", ot_TimeFrame, &Timeframe);
  Timeframe = PERIOD_M15;
}

EXPORT void DoneStrategy() {
  free(Currency);
}

EXPORT void ResetStrategy() {}

EXPORT void GetSingleTick() {
    
    if (TechnicalFunctions::GetNumberOfOpenPositions() < 1) {
        double stopLoss = StrategyFunctions::Ask() - (100* StrategyFunctions::Point());
        double stopProfit = StrategyFunctions::Ask() + (50* StrategyFunctions::Point());
        StrategyFunctions::Buy(0.1, stopLoss, stopProfit);
    }

}
