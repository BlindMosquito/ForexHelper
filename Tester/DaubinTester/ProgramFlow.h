#pragma once
#include <string>
#include "Baseline.h"
#include "Order.h"
#include "Atr.h"

class ProgramFlow {
	public:
		ProgramFlow();				// Constructor
		~ProgramFlow();				// Deconstructor
		bool Variables(std::string symbol, int period);
		void Calculate();			// Each iteration this is called
	private:
		std::string symbol;			// Symbol the program is using
		int period;					// Period timeframe required
		Baseline * baseline;		// Baseline
		Order* order;				// Sets up the orders
		Atr* atr;

		double lastChecked;			// Hour last checked

		bool InitIndicators();		// Sets up the indicators
		bool TestTime();			// Get the current hour and see if it is ready for update
		bool TestOpen(bool);			// Test if order is open and if needs to close
		void TestNew(bool);				// Test if ready for new order

};

