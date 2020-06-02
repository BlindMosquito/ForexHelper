#pragma once

#include <string>
class Atr  {
	public:
		Atr(std::string, int);				// Constructor
		double GetValue(int count = 8);					// Gets the value for the indicator
		double GetPips();					// Get how many pips
		double LotSize();					// Get the Lot Size
		double BuyRisk();					// Risk If buying
		double SellRisk();					// Risk If Selling
		double BuyProfit();					// Start of Profit if buying
		double SellProfit();				// Start of Profit if selling
	private:
		std::string symbol;
		int period;
		double CalculateRisk();				// Get the risk in money
		double CalculateProfit();			// Get the profit range for the start
		double PipValue();					// Determines the pip value
};

