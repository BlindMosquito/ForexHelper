#pragma once
#include "ForexHelper.h"
class Atr : public ForexHelper {
	public:
		Atr(const char*, int);				// Constructor
		bool Calculate();
		double GetPips();					// Get how many pips
		double LotSize();					// Get the Lot Size
		double BuyRisk();					// Risk If buying
		double SellRisk();					// Risk If Selling
		double BuyProfit();					// Start of Profit if buying
		double SellProfit();				// Start of Profit if selling
	private:
		double CalculateRisk();				// Get the risk in money
		double CalculateProfit();			// Get the profit range for the start
		double GetATR();					// Returns the ATR Value
};

