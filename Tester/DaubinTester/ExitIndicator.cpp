#include "ExitIndicator.h"
#include "StrategyFunctions.h"


// Static Function. true for buy if bought, or false for sold. Will return True if time to sell or false if not ready
bool ExitIndicator::Calculate(std::string symbol, int period, bool buy, Atr * atr) {
	if (!atr) return false;
	double dist = atr->GetValue();
	dist /= 4;
	bool shouldClose = false;
	double currentClose = StrategyFunctions::iClose(symbol.c_str(), period, 1);
	double previousClose = StrategyFunctions::iOpen(symbol.c_str(), period, 2);

	if (buy && currentClose + dist < previousClose) shouldClose = true;
	else if (!buy && currentClose - dist > previousClose) shouldClose = true;
	return shouldClose;
}


// Get the last hour
int ExitIndicator::LastHour(std::string symbol, int period) {
	double tm = StrategyFunctions::iTime(symbol.c_str(), period, 1);
	int offset = tm;				// Get value without decimal portion
	tm -= offset;					// tm is only = to decimal portion now which is hours in day
	return tm * 24;					// multiply time by 24 as it should of been a fraction before, but only return actual hour in integer
}

