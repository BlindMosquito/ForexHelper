#include "Baseline.h"
#include "StrategyFunctions.h"

Baseline::Baseline(std::string symbol, int period) : symbol(symbol), period(period), handle(0), location(0) { SetupIndicator(); }

int Baseline::Handle() { return handle; }

// Calculates the current value
int Baseline::Calculate() {
	if (!handle) return 0;
	double base = GetValue();
	double close = StrategyFunctions::iClose(symbol.c_str(), period, 1);
	switch (location) {
		case 0:
			if (BaseTrend(base, close)) location = 1;
			else location = -1;
			return 0;
		case 1:
			if (BaseTrend(base, close)) return 0;
			location = -1;
			break;
		case -1:
			if (!BaseTrend(base, close)) return 0;
			location = 1;
			break;
	}
	return location;
}

int Baseline::BaseTrend(double base, double close) {
	if (base < close) return true;
	return false;
}

// Sets up the indicator
void Baseline::SetupIndicator() { 
	handle = StrategyFunctions::CreateIndicator(symbol.c_str(), period, "MovingAverage", "8;-1;0;Simple (SMA);Close"); 
}

// Gets the value for the indicator
double Baseline::GetValue() {
	if (!handle) return 0;
	return StrategyFunctions::GetIndicatorValue(handle, 0, 1);
}
