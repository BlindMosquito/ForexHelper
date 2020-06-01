#include "Order.h"
#include "StrategyFunctions.h"
#include "TechnicalFunctions.h"
#include <string>

// Constructor
Order::Order(std::string symbol, int period) : symbol(symbol), period(period) { 
    ResetVariables();
	atr = new Atr(symbol, period);
}
// Deconstructor
Order::~Order() {
	if (atr) delete atr;
	if (handle) CloseOrder();
}

// Is there an open order
bool Order::Open() {
	if (!handle) return false;
    if (StrategyFunctions::OrderClosed(handle)) {
        ResetVariables();
        return false;
    } 
    TestStopLoss();
    return true;
}
// Returns the status
int Order::Status() { return status; }

// Buy a new currency
bool Order::BuyOrder() {
	if (handle) return true;
    double ask = StrategyFunctions::Ask();  // Get Ask Price
    double lotTemp = atr->LotSize();             // Get Total Lots
    double lossTemp = atr->BuyRisk();           // Get Stop Loss Price
    double profitTemp = atr->BuyProfit();          // Get Stop Profit Price
    /*std::string txt = "\n LotSize: ";
    txt += std::to_string(lotTemp);
    txt += " BuyRisk: ";
    txt += std::to_string(lossTemp);
    txt += " ATR: ";
    txt += std::to_string(atr->GetValue());
    StrategyFunctions::Print(txt.c_str());
    */
    handle = StrategyFunctions::Buy(lotTemp, lossTemp, 0); // Place order
    if (!handle) return false;                   // If order failed leave
    // Ticket has been placed by this point
    status = 1;
    orderPrice = ask;
    stopLoss = lossTemp;
    takeProfit = profitTemp;
    lotSize = lotTemp;
    return true;
}

// Sell a new currency
bool Order::SellOrder() {
	if (handle) return true;
    double bid = StrategyFunctions::Bid();  // Get Ask Price
    double lotTemp = atr->LotSize();             // Get Total Lots
    double lossTemp = atr->SellRisk();           // Get Stop Loss Price
    double profitTemp = atr->SellProfit();          // Get Stop Profit Price
    handle = StrategyFunctions::Sell(lotTemp, lossTemp, 0); // Place order
    if (!handle) return false;                   // If order failed leave
    // Ticket has been placed by this point
    status = -1;
    orderPrice = bid;
    stopLoss = lossTemp;
    takeProfit = profitTemp;
    lotSize = lotTemp;
    return true;
}

// Closes the order
bool Order::CloseOrder() {
    if (!handle) return false;
    if (!StrategyFunctions::CloseOrder(handle)) return false;
    ResetVariables();
    return true;
}


// Resets all the variables
void Order::ResetVariables() {
    handle = 0;
    status = 0;
    orderPrice = 0;
    stopLoss = 0;
    takeProfit = 0;
    lotSize = 0;
}

// Tests the stop loss and if it needs to move
bool Order::TestStopLoss() {
    return false;
}

