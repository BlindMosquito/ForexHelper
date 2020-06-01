#include "ProgramFlow.h"
#include "StrategyFunctions.h"

// Constructor
ProgramFlow::ProgramFlow() : period(0), baseline(NULL), order(NULL) { symbol = std::string(); }

// Deconstructor
ProgramFlow::~ProgramFlow() {
	if (baseline) delete baseline;
	if (order) delete order;
}

// Checks if variables are set yet
bool ProgramFlow::Variables(std::string symbol, int period) {
	this->symbol = symbol;
	this->period = period;
	if (this->symbol.empty()) return false;
	return true;
}

// Each iteration this is called
void ProgramFlow::Calculate() {
	if (!InitIndicators()) return;
	if(order->Open()) return;					// If there is an open order then nothing left to do
	int status = baseline->Calculate();
	if (status == 1) order->BuyOrder();
	else if (status == -1) order->SellOrder();
}
		
// Sets up the indicators
bool ProgramFlow::InitIndicators() {
	if (symbol.empty() || period == 0) return false;
	if (!baseline) baseline = new Baseline(symbol, period);
	if (!baseline->Handle()) return false;
	if (!order) order = new Order(symbol, period);
	return true;
}
