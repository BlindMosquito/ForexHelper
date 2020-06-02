#include "ProgramFlow.h"
#include "StrategyFunctions.h"
#include "ExitIndicator.h"
#include <ctime>

// Constructor
ProgramFlow::ProgramFlow() : period(0), baseline(NULL), order(NULL), lastChecked(0) { symbol = std::string(); }

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
	if (!lastChecked) { TestTime(); return; }
	bool newHour = TestTime();				// Sees if an hour has passed since last check
	if(TestOpen(newHour)) return;			// If there is an open order then nothing left to do
	TestNew(newHour);						// Test if ready for new order
}
		
// Sets up the indicators
bool ProgramFlow::InitIndicators() {
	if (symbol.empty() || period == 0) return false;
	if (!baseline) baseline = new Baseline(symbol, period);
	if (!baseline->Handle()) return false;
	if (!order) order = new Order(symbol, period);
	return true;
}

// Get the current hour and see if it is ready for update
bool ProgramFlow::TestTime() {
	double current = StrategyFunctions::iClose(symbol.c_str(), period, 1);
	if (lastChecked == current) return false;
	lastChecked = current;
	return true;
}
// Test if order is open and if needs to close
bool ProgramFlow::TestOpen(bool newHour) {
	if (!order->Open()) return false;		// If not open then leave
	if (!newHour) return true;			// If not enough time has passed then leave with order open
	bool close = false;
	int status = order->Status();
	if (!ExitIndicator::Calculate(symbol, period, (status == 1))) return true;	// Not ready to sell if false is returned
	order->CloseOrder();
	return false;
}
// Test if ready for new order
void ProgramFlow::TestNew(bool newHour) {
	if (!newHour) return;
	int status = baseline->Calculate();
	if (status == 1) order->BuyOrder();
	else if (status == -1) order->SellOrder();
}
