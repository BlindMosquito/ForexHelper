#include "Atr.h"
#include <stdio.h>
#include <math.h>
#include "StrategyFunctions.h"

const double PIP_LOSS = 0.5;
const double PIP_PROFIT = .5;
const double RISK = 0.04;

// Constructor
Atr::Atr(std::string symbol, int period) : symbol(symbol), period(period) { }

// Gets the value for the indicator
double Atr::GetValue(int count) {
	++count;
	double sum = 0;
	for (int i = 1; i < count; ++i) {
		double open = StrategyFunctions::iHigh(symbol.c_str(), period, i);
		double close = StrategyFunctions::iLow(symbol.c_str(), period, i);
		if (open > close) sum += open - close;
		else sum += open - close;
	}
	--count;
	return sum / count;
}

// Get how many pips
double Atr::GetPips() { 
	int digits = StrategyFunctions::Digits();
	return GetValue() * pow(10, digits); 
}
// Get the Lot Size
double Atr::LotSize() { 
//	double tick_value = PipValue();
	double tick_value = 1.0;
	// Author from https://mql4tradingautomation.com/mql4-calculate-position-size/
	double risk = StrategyFunctions::AccountBalance() * RISK;
	double stopTick = GetPips() * PIP_LOSS * tick_value;
	return risk / stopTick / 10;
}

// Risk If buying
double Atr::BuyRisk() { return StrategyFunctions::Bid() - CalculateRisk(); }

// Risk If Selling
double Atr::SellRisk() { return StrategyFunctions::Ask() + CalculateRisk(); }

// Start of Profit if buying
double Atr::BuyProfit() { return StrategyFunctions::Ask() + CalculateProfit(); }

// Start of Profit if selling
double Atr::SellProfit() { return StrategyFunctions::Bid() - CalculateProfit(); }

// Get the risk in money
double Atr::CalculateRisk() { return GetValue() * PIP_LOSS; }

// Get the profit range for the start
double Atr::CalculateProfit() { return GetValue() * PIP_PROFIT; }


// Determines the pip value
double Atr::PipValue() {
	if (symbol.c_str() == "USDCHF") return 0.72633773;
	if (symbol.c_str() == "USDCAD") return 0.72633773;
	if (symbol.c_str() == "NZDJPY") return 0.92790201;
	if (symbol.c_str() == "EURJPY") return 0.92790201;
	if (symbol.c_str() == "USDJPY") return 0.92790201;
	if (symbol.c_str() == "EURGBP") return 1.23456000;
	return 1.0;
}
