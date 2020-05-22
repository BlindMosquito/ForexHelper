#include "BuyTicket.mqh"

BuyTicket::BuyTicket(string symbol, int period) : OrderTicket(symbol, period) { }

// Signal went through that it is ready to buy
bool BuyTicket::OrderChild() {
    double ask = MarketInfo(symbol, MODE_ASK);  // Get Ask Price
    double lotTemp = atr.LotSize();             // Get Total Lots
    double lossTemp = atr.SellRisk();           // Get Stop Loss Price
    double profitTemp = atr.BuyRisk();          // Get Stop Profit Price
    ticket = OrderSend(symbol, OP_BUY, lotTemp, ask, 3, lossTemp, 0); // Place order
    if(!ticket) return false;                   // If order failed leave
    // Ticket has been placed by this point
    open = true;
    orderPrice = ask;
    stopLoss = lossTemp;
    takeProfit = profitTemp;
    current = ask;
    lot = lotTemp;
    return true;
}

// Tests the stop loss;
void BuyTicket::TestStopLoss() {
    if(!ticket || !open || !stopLoss || !lot) return; // If no ticket then leave
    double ask = MarketInfo(symbol, MODE_ASK);  // get current value of market
    if(!trail) {                                // If trail has not been hit
        TrailReady(ask);                        // Test if ready for a trail
        return;                                 // Leave after the test
    }
    // Should have a trail ready now
    if(ask <= current) return;                  // Not ready to move stop loss
    double stopTemp = stopLoss
    if(OrderModify(ticket, 0, 
}

// Test if the order is ready for a trailing stop
// trail should be set to false by this point and should have a ticket
bool BuyTicket::TrailReady(double ask) {
    if(takeProfit > ask) {
        if(!OrderClose(ticket, (lot/2), ask, 3)) return false;
        current = ask;                          // Set the current order to the asking price
        tail = true;                            // Order should of partially closed
        lot /= 2;                               // half the lots left
        if(!OrderModify(ticket, 0, orderPrice, 0, 0)) return true; // modify order stop loss
        stopLoss = orderPrice;
        return true;
    }
    return tail;
}