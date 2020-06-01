#pragma once
#include <string>
class Rvi {
	public:
		Rvi(std::string symbol, int period);
		bool Calculate(bool buy);

	private:
		std::string symbol;
		int period;
		double rvi;
		double rviSig;
		bool Calculate(int start);
};

