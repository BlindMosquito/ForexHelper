#pragma once
#include <string>
class Baseline {
	public:
		Baseline(std::string, int period);
		int Calculate();
		void SetupIndicator();
		int Handle();
	private:
		std::string symbol;
		int period;
		int handle;
		int location;
		double GetValue();
		int BaseTrend(double base, double close);
};

