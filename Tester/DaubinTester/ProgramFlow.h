#pragma once
#include <string>
#include "Baseline.h"

class ProgramFlow {
	public:
		ProgramFlow();				// Constructor
		~ProgramFlow();				// Deconstructor
		bool Variables(std::string symbol, int period);
		void Calculate();			// Each iteration this is called
	private:
		std::string symbol;			// Symbol the program is using
		int period;					// Period timeframe required
		bool open;					// If order is open
		Baseline * baseline;		// Baseline

		bool InitIndicators();		// Sets up the indicators

};

