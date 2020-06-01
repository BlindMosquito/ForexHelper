#pragma once
#include <string>
#include "Atr.h"
class Order {
	public:
		Order(std::string symbol, int period);		// Constructor
		~Order();									// Deconstructor
		bool Open();								// Is there an open order
		bool BuyOrder();									// Buy a new currency
		bool SellOrder();								// Sell a new currency
		bool CloseOrder();								// Closes the order
		int Status();								// Returns the status
	private:
		std::string symbol;
		int period;
		int handle;									// handle id of order
		int status;									// is this buy or sell or none
		double orderPrice;							// Price of order
		double stopLoss;							// Stop loss
		double takeProfit;							// Take Proffit
		double lotSize;								// Lot Size
		Atr* atr;									// Used to check the Atr for info
		void ResetVariables();						// Resets all the variables
		bool TestStopLoss();						// Tests the stop loss and if it needs to move
};

