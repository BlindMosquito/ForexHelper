#include "Atr.h"
#include <stdio.h>
#include <math.h>
#include "StrategyFunctions.h"

const double PIP_LOSS = 1;
const double PIP_PROFIT = 1;

// Constructor
Atr::Atr(std::string symbol, int period) : symbol(symbol), period(period), handle(0) { SetupIndicator(); }

// Gets the value for the indicator
double Atr::GetValue() {
	if (!handle) return 0;
	return StrategyFunctions::GetIndicatorValue(handle, 0, 1);
}

// Get how many pips
double Atr::GetPips() { 
	int digits = StrategyFunctions::Digits();
	return GetValue() * pow(10, --digits); 
}
// Get the Lot Size
double Atr::LotSize() { 
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


// Sets up the indicator
void Atr::SetupIndicator() {
	handle = StrategyFunctions::CreateIndicator(symbol.c_str(), period, "ATR", "14;Close");
}
		
// Returns the handle
int Atr::Handle() { return handle; }
