#include "Order.h"
#include "StrategyFunctions.h"
#include <string>

// Constructor
Order::Order(std::string symbol, int period) : symbol(symbol), period(period), handle(0), status(0) { 
	atr = new Atr(symbol, period);
}
// Deconstructor
Order::~Order() {
	if (atr) delete atr;
	if (handle) Close();
}

// Is there an open order
bool Order::Open() {

}

// Buy a new currency
bool Order::Buy() {
	if (handle) return true;
	
	
}

// Sell a new currency
bool Order::Sell() {

}

// Closes the order
bool Order::Close() {

}

// Tests the stop loss and if it needs to move
bool Order::TestStopLoss() {

}

