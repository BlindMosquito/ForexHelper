#pragma once

#include <string>
class Atr  {
	public:
		Atr(std::string, int);				// Constructor
		double GetValue();					// Gets the value for the indicator
		double GetPips();					// Get how many pips
		double LotSize();					// Get the Lot Size
		double BuyRisk();					// Risk If buying
		double SellRisk();					// Risk If Selling
		double BuyProfit();					// Start of Profit if buying
		double SellProfit();				// Start of Profit if selling
		int Handle();						// Returns the handle
	private:
		std::string symbol;
		int period;
		int handle;
		void SetupIndicator();				// Sets up the indicator
		double CalculateRisk();				// Get the risk in money
		double CalculateProfit();			// Get the profit range for the start
};

