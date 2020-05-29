#include <windows.h>
#include "StrategyFunctions.h"
#include "TechnicalFunctions.h"
#include <ctime>
#include "ProgramFlow.h"


char* currency = NULL;
int timeframe;
ProgramFlow flow;
bool assigned = false;


EXPORT void InitStrategy() {
  StrategyFunctions::StrategyShortName("ObjectsTest");
  StrategyFunctions::StrategyDescription("Test of moving objects");

  StrategyFunctions::RegOption("Currency", ot_Currency, &currency);

  StrategyFunctions::RegOption("Timeframe", ot_TimeFrame, &timeframe);
}

EXPORT void DoneStrategy() {
  free(currency);
}

EXPORT void ResetStrategy() {}

EXPORT void GetSingleTick() {
    if (!assigned) assigned = flow.Variables(currency, timeframe);
    flow.Calculate();
}
