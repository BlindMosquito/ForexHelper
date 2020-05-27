#include "IndicatorBase.h"
#include "StrategyFunctions.h"

// Constructor
IndicatorBase::IndicatorBase(const char* symbol, int period) : symbol(symbol), period(period), handle(0) { SetupIndicator(); }

// Gets the value from the indicator		
double IndicatorBase::GetValue() {
	return 0;
}

// Creates the indicator
void IndicatorBase::SetupIndicator() {
}
		
