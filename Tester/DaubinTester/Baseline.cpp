#include "Baseline.h"
#include "StrategyFunctions.h"

Baseline::Baseline(std::string symbol, int period) : symbol(symbol), period(period), handle(0), location(0) { SetupIndicator(); }

int Baseline::Handle() { return handle; }

// Calculates the current value
int Baseline::Calculate() {
	double close = StrategyFunctions::iClose(symbol.c_str(), period, 1);
	/*double lowest = StrategyFunctions::iLowest(symbol.c_str(), period, MODE_CLOSE, 14, 1);
	double highest = StrategyFunctions::iHighest(symbol.c_str(), period, MODE_CLOSE, 14, 1);

	double k = close - lowest;
	k /= highest - lowest;
	k *= 100;
	/*
	if (!handle) return 0;
	double base = GetValue();
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
	if (location == 1) if (k > 70) return 0;
	else if (location == -1) if (k < 30) return 0;
	*/
	double open = StrategyFunctions::iOpen(symbol.c_str(), period, 1);
	if (open < close) location = 1;
	else location = -1;
	/*if (k > 80) return 0;
	else if (k < 20) return 0;
	if (location != 0) {
		double nOpen = StrategyFunctions::iOpen(symbol.c_str(), 1440, 0);
		double bid = StrategyFunctions::Ask();
		if (location > 0 && nOpen > bid) return 0;
		if (location < 0 && nOpen < bid) return 0;
	}
	*/
	return location;
}

bool Baseline::BaseTrend(double base, double close) {
	if (base < close) return true;
	return false;
}

// Sets up the indicator
void Baseline::SetupIndicator() { 
	handle = StrategyFunctions::CreateIndicator(symbol.c_str(), period, "MovingAverage", "6;-1;0;Simple (SMA);Close"); 
}

// Gets the value for the indicator
double Baseline::GetValue() {
	if (!handle) return 0;
	return StrategyFunctions::GetIndicatorValue(handle, 0, 1);
}
