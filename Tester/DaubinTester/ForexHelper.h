#pragma once
class ForexHelper
{
	public:
		ForexHelper(const char*, int);
		virtual bool Calculate() = 0;
	protected:
		const char * symbol;
		int period;
};

