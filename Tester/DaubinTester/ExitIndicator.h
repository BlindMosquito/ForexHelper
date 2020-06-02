#pragma once
#include <string>
#include "Atr.h"
class ExitIndicator {
	public:
		static bool Calculate(std::string symbol, int period, bool buy, Atr * atr);								// Pass in true if bought or false if sold returns if ready to sell
};

