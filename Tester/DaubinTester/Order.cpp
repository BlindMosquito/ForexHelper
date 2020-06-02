#include "Order.h"
#include "StrategyFunctions.h"
#include "TechnicalFunctions.h"
#include "ExitIndicator.h"
#include <string>

// Constructor
Order::Order(std::string symbol, int period) : symbol(symbol), period(period) { 
    ResetVariables();}
// Deconstructor
Order::~Order() {	
    if (handle) CloseOrder();
}

// Is there an open order
bool Order::Open(Atr * atr, bool canEdit) {
	if (!handle || !atr) return false;
    if (StrategyFunctions::OrderClosed(handle)) {
        ResetVariables();
        return false;
    }
    if (!canEdit) return true;
    if(status > 0) TestStopBuy(atr);
    else TestStopSell(atr);
    return true;
}
// Returns the status
int Order::Status() { return status; }

// Buy a new currency
bool Order::BuyOrder(Atr * atr) {
	if (handle || !atr) return true;
    double ask = StrategyFunctions::Ask();  // Get Ask Price
    double lotTemp = atr->LotSize();             // Get Total Lots
    double lossTemp = atr->BuyRisk();           // Get Stop Loss Price
    double profitTemp = atr->BuyProfit();          // Get Stop Profit Price
    if (lotTemp > 3) lotTemp = 1;
    double volume = atr->GetValue(2) - atr->GetValue(14);
    int tm = ExitIndicator::LastHour(symbol, period);
    if (tm < 4 || tm > 16) return false;
    if (volume < 0) return false;
    handle = StrategyFunctions::Buy(lotTemp, lossTemp, 0, std::to_string(volume).c_str()); // Place order
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
bool Order::SellOrder(Atr * atr) {
	if (handle || !atr) return true;
    double bid = StrategyFunctions::Bid();  // Get Ask Price
    double lotTemp = atr->LotSize();             // Get Total Lots
    double lossTemp = atr->SellRisk();           // Get Stop Loss Price
    double profitTemp = atr->SellProfit();          // Get Stop Profit Price
    if (lotTemp > 3) lotTemp = 1;
    double volume = atr->GetValue(2) - atr->GetValue(14);
    if (volume < 0) return false;
    int tm = ExitIndicator::LastHour(symbol, period);
    if (tm < 4 || tm > 16) return false;
    handle = StrategyFunctions::Sell(lotTemp, lossTemp, 0, std::to_string(volume).c_str()); // Place order
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
bool Order::TestStopBuy(Atr * atr) {
    double open = StrategyFunctions::iOpen(symbol.c_str(), period, 1);
    double close = StrategyFunctions::iClose(symbol.c_str(), period, 1);
    if (close < open) return false;
    double change = stopLoss + (close - open);
    if (!StrategyFunctions::ModifyOrder(handle, 0, change, 0)) return false;
    stopLoss = change;
    return true;

    /*double current = StrategyFunctions::Bid();
    if (current < takeProfit) return false;
    double pips = atr->GetValue();
    double fract = pips / 6;
    pips = takeProfit - pips;
    if (pips < orderPrice) pips = orderPrice + fract;
    if (!StrategyFunctions::ModifyOrder(handle, 0, pips, 0)) return false;
    stopLoss = pips;
    takeProfit = atr->BuyProfit();
    return true;
    */
}

// Tests the stop loss and if it needs to move
bool Order::TestStopSell(Atr* atr) {
    double open = StrategyFunctions::iOpen(symbol.c_str(), period, 1);
    double close = StrategyFunctions::iClose(symbol.c_str(), period, 1);
    if (close > open) return false;
    double change = stopLoss - (open - close);
    if (!StrategyFunctions::ModifyOrder(handle, 0, change, 0)) return false;
    stopLoss = change;
    return true;

    /*
	double current = StrategyFunctions::Ask();
    if (current > takeProfit) return false;
    double pips = atr->GetValue();
    double fract = pips / 6;
    pips = takeProfit + pips;
    if (pips > orderPrice) pips = orderPrice - fract;
    if (!StrategyFunctions::ModifyOrder(handle, 0, pips, 0)) return false;
    stopLoss = pips;
    takeProfit = atr->SellProfit();
    return true;
    */
}
