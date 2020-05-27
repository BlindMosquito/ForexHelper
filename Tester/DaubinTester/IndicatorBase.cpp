#include "IndicatorBase.h"
#include "StrategyInterfaceUnit.h"

// Constructor
IndicatorBase::IndicatorBase(const char* symbol, int period) : symbol(symbol), period(period), handle(0) { SetupIndicator(); }

// Gets the value from the indicator		
double IndicatorBase::GetValue() {
	if (!handle) return 0;
	return GetIndicatorValue(handle, 0, 1);
}

// Creates the indicator
void IndicatorBase::SetupIndicator() {
	const char* name = IndicatorName();
	char buffer[1000];
	IndicatorParams(buffer);
	handle = CreateIndicator(symbol, period, name, buffer);
}
		
