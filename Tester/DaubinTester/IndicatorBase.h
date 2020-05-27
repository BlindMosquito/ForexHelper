#pragma once
class IndicatorBase {
	public:
		IndicatorBase(const char*, int);			// Constructor
		double GetValue();							// Gets the value from the indicator
	protected:
		const char* symbol;
		int period;
		int handle;									// Handle for indicator
		void SetupIndicator();						// Creates the indicator
		virtual const char* IndicatorName() = 0;			// Returns the Indicator Name
		virtual char* IndicatorParams(char * buff) = 0;	// Sets the buffer sent in to the parameters
};

