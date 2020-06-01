#pragma once
#include <string>
class ExitIndicator {
	public:
		static bool Calculate(std::string symbol, int period, bool buy);								// Pass in true if bought or false if sold returns if ready to sell
};

