#include "Rvi.h"
#include "StrategyFunctions.h"

// Used the formulas found in below for indicator
//# Relative Vigor Index
////# Assembled by BenTen at useThinkScript.com
//# Converted from https ://www.tradingview.com/script/0pbCZxRN-Relative-Vigour-Index-RVI-Ehlers/


const int p = 14;

Rvi::Rvi(std::string symbol, int period) : symbol(symbol), period(period), rvi(0), rviSig(0) { }

bool Rvi::Calculate(bool buy) {

	return false;
}

bool Rvi::CalculatStart(int start) {
	double CO[4] = {
		StrategyFunctions::iClose(symbol.c_str(), period, 0) - StrategyFunctions::iOpen(symbol.c_str(), period, start),
		StrategyFunctions::iClose(symbol.c_str(), period, 1) - StrategyFunctions::iOpen(symbol.c_str(), period, start+1),
		StrategyFunctions::iClose(symbol.c_str(), period, 2) - StrategyFunctions::iOpen(symbol.c_str(), period, start+2),
		StrategyFunctions::iClose(symbol.c_str(), period, 3) - StrategyFunctions::iOpen(symbol.c_str(), period, start+3)
	};
	double HL[4] = {
		StrategyFunctions::iHigh(symbol.c_str(), period, 0) - StrategyFunctions::iLow(symbol.c_str(), period, start),
		StrategyFunctions::iHigh(symbol.c_str(), period, 1) - StrategyFunctions::iLow(symbol.c_str(), period, start+1),
		StrategyFunctions::iHigh(symbol.c_str(), period, 2) - StrategyFunctions::iLow(symbol.c_str(), period, start+2),
		StrategyFunctions::iHigh(symbol.c_str(), period, 3) - StrategyFunctions::iLow(symbol.c_str(), period, start+3)
	};

	double num = CO[0];
	num += 2 * CO[1];
	num += 2 * CO[2];
	num += CO[3];
	num /= 6;

	double denum = HL[0];
	denum += 2 * HL[1];
	denum += 2 * HL[2];
	denum += HL[3];
	denum /= 6;
	return false;

	num = n

}

