//---------------------------------------------------------------------------
// Support library, additional useful functions
//
// Ver 1.0
//---------------------------------------------------------------------------
#pragma once
#include <math.h>

enum TPriceType {pt_Close, pt_Open, pt_High, pt_Low, pt_HL2, pt_HLC3, pt_HLCC4};
enum TMAType {ma_SMA, ma_EMA, ma_WMA, ma_SSMA};

class TechnicalFunctions {
	public:
		static double GetPrice(int index, TPriceType PriceType);
		static void LRCChannelParams(int Offset, int period, TPriceType PriceType,
			double& StartValue, double& EndValue, double& Height, double& Top, double& Bottom);

		// close all opened positions (except pending orders)
		static void CloseAllOpenPos();

		// delete all pending orders
		static void DeleteAllPendingOrders();

		// close all open positions and delete all pending orders
		static void CloseAndDeleteAll();

		// Get number of open positions
		static int GetNumberOfOpenPositions();

		// Get number of pending orders
		static int GetNumberOfPendingOrders();

		// Get profit for open positions
		static double GetOpenPosProfit();

		// Convert price type to string
		static const char * StrPriceType(TPriceType ptype);

		// Convert moving average type to string
		static const char * StrMAType(TMAType matype);

		static void RegMATypeOption(int& option, const char* name);

		static void RegApplyToPriceOption(int& option, const char* name);
};
