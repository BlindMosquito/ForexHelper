#pragma once
#include <string>
#include "Atr.h"
class Order {
	public:
		Order(std::string symbol, int period);		// Constructor
		~Order();									// Deconstructor
		bool Open();								// Is there an open order
		bool Buy();									// Buy a new currency
		bool Sell();								// Sell a new currency
		bool Close();								// Closes the order
	private:
		std::string symbol;
		int period;
		int handle;									// handle id of order
		int status;									// is this buy or sell or none
		Atr* atr;									// Used to check the Atr for info
		bool TestStopLoss();						// Tests the stop loss and if it needs to move
};

