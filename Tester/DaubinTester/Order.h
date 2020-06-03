#pragma once
#include <string>
#include "Atr.h"
class Order {
	public:
		Order(std::string symbol, int period);		// Constructor
		~Order();									// Deconstructor
		bool Open(Atr * atr, bool canEdit);								// Is there an open order
		bool BuyOrder(Atr * atr);									// Buy a new currency
		bool SellOrder(Atr * atr);								// Sell a new currency
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
		void ResetVariables();						// Resets all the variables
		bool TestStopBuy(Atr * atr);						// Tests the stop loss and if it needs to move
		bool TestStopSell(Atr * atr);						// Tests the stop loss and if it needs to move
		bool SetExitBuy(Atr* atr, double open, double close);
		bool SetExitSell(Atr* atr, double open, double close);
};

