#include "ExitIndicator.h"
#include "StrategyFunctions.h"


// Static Function. true for buy if bought, or false for sold. Will return True if time to sell or false if not ready
bool ExitIndicator::Calculate(std::string symbol, int period, bool buy) {
	bool shouldClose = false;
	double currentClose = StrategyFunctions::iClose(symbol.c_str(), period, 1);
	double previousClose = StrategyFunctions::iOpen(symbol.c_str(), period, 2);
	if (buy && currentClose < previousClose) shouldClose = true;
	else if (!buy && currentClose > previousClose) shouldClose = true;
	return shouldClose;
}
