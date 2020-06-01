#include "ExitIndicator.h"
#include "StrategyFunctions.h"


// Static Function. true for buy if bought, or false for sold. Will return True if time to sell or false if not ready
bool ExitIndicator::Calculate(std::string symbol, int period, bool buy) {
	double currentClose = StrategyFunctions::iClose(symbol.c_str(), period, 0);
	double previousClose = StrategyFunctions::iClose(symbol.c_str(), period, 1);
	if (buy && currentClose < previousClose) return true;
	if (!buy && currentClose > previousClose) return true;
	return false;
}