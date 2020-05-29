#include "ProgramFlow.h"
#include "StrategyFunctions.h"

// Constructor
ProgramFlow::ProgramFlow() : period(0), baseline(NULL) { symbol = std::string(); }

// Deconstructor
ProgramFlow::~ProgramFlow() {
	if (baseline) delete baseline;
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
	
}
		
// Sets up the indicators
bool ProgramFlow::InitIndicators() {
	if (symbol.empty() || period == 0) return false;
	if (!baseline) baseline = new Baseline(symbol, period);
	if (!baseline->Handle()) return false;
	return true;
}
