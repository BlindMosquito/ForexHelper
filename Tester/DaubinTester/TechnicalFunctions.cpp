#include "TechnicalFunctions.h"
#include "StrategyFunctions.h"

//-----Get price--------------------------------------------------------------
double TechnicalFunctions::GetPrice(int index, TPriceType PriceType)
{
    switch (PriceType)
    {
    case pt_Close: return StrategyFunctions::Close(index);
    case pt_Open:  return StrategyFunctions::Open(index);
    case pt_High:  return StrategyFunctions::High(index);
    case pt_Low:   return StrategyFunctions::Low(index);
    case pt_HL2:   return (StrategyFunctions::High(index) + StrategyFunctions::Low(index)) / 2;
    case pt_HLC3:  return (StrategyFunctions::High(index) + StrategyFunctions::Low(index) + StrategyFunctions::Close(index)) / 3;
    case pt_HLCC4: return (StrategyFunctions::High(index) + StrategyFunctions::Low(index) + StrategyFunctions::Close(index) * 2) / 4;
    default:       return 0;
    }
}

//-----Get channel params-----------------------------------------------------
void TechnicalFunctions::LRCChannelParams(int Offset, int period, TPriceType PriceType,
    double& StartValue, double& EndValue, double& Height, double& Top, double& Bottom)
{
    // Variable initialization
    double sum_x = 0;
    double sum_y = 0;
    double sum_xy = 0;
    double sum_x2 = 0;

    double y, z, max;
    int x;

    // Calculating sums for regression line

    int i = Offset;
    for (x = 0; x < period; x++)
    {
        y = GetPrice(i, PriceType);
        sum_x += x;
        sum_y += y;
        sum_xy += x * y;
        sum_x2 += x * x;
        i++;
    }

    // Calculating regression line
    double b = (period * sum_xy - sum_x * sum_y) / (period * sum_x2 - sum_x * sum_x);
    double a = (sum_y - b * sum_x) / period;

    // Calculating channel height
    i = Offset;
    max = 0;
    for (x = 0; x < period; x++)
    {
        y = a + b * x;
        z = fabs(GetPrice(i, PriceType) - y);
        if (z > max) max = z;
        i++;
    }

    // Returning channel values
    StartValue = a + b * period;
    EndValue = a;
    Height = max;
    Top = a + max;
    Bottom = a - max;
}

//-----Close all open positions-----------------------------------------------
void TechnicalFunctions::CloseAllOpenPos()
{
    int total = StrategyFunctions::OrdersTotal();
    for (int i = total - 1; i >= 0; i--)
    {
        if (!StrategyFunctions::OrderSelect(i, SELECT_BY_POS, MODE_TRADES)) continue;

        switch (StrategyFunctions::OrderType())
        {
        case tp_Buy: case tp_Sell:
            StrategyFunctions::CloseOrder(StrategyFunctions::OrderTicket());
            break;
        }
    }
}

//-----Delete all pending orders----------------------------------------------
void TechnicalFunctions::DeleteAllPendingOrders()
{
    int total = StrategyFunctions::OrdersTotal();
    for (int i = total - 1; i >= 0; i--)
    {
        if (!StrategyFunctions::OrderSelect(i, SELECT_BY_POS, MODE_TRADES)) continue;

        switch (StrategyFunctions::OrderType())
        {
        case tp_BuyStop: case tp_SellStop:
        case tp_BuyLimit: case tp_SellLimit:
            StrategyFunctions::DeleteOrder(StrategyFunctions::OrderTicket());
            break;
        }
    }
}

//-----Close all open positions and delete all orders-------------------------
void TechnicalFunctions::CloseAndDeleteAll()
{
    int total = StrategyFunctions::OrdersTotal();
    for (int i = total; i >= 0; i--)
    {
        if (!StrategyFunctions::OrderSelect(i, SELECT_BY_POS, MODE_TRADES)) continue;

        switch (StrategyFunctions::OrderType())
        {
        case tp_Buy: case tp_Sell:
            StrategyFunctions::CloseOrder(StrategyFunctions::OrderTicket());
            break;

        case tp_BuyStop: case tp_SellStop:
        case tp_BuyLimit: case tp_SellLimit:
            StrategyFunctions::DeleteOrder(StrategyFunctions::OrderTicket());
            break;
        }
    }
}

//-----Get number of open positions-------------------------------------------
int TechnicalFunctions::GetNumberOfOpenPositions()
{
    int result = 0;

    int total = StrategyFunctions::OrdersTotal();
    for (int i = total; i >= 0; i--)
    {
        if (!StrategyFunctions::OrderSelect(i, SELECT_BY_POS, MODE_TRADES)) continue;

        switch (StrategyFunctions::OrderType())
        {
        case tp_Buy: case tp_Sell:
            result++;
            break;
        }
    }

    return result;
}

//-----Get number of pending orders-------------------------------------------
int TechnicalFunctions::GetNumberOfPendingOrders()
{
    int result = 0;

    int total = StrategyFunctions::OrdersTotal();
    for (int i = total; i >= 0; i--)
    {
        if (!StrategyFunctions::OrderSelect(i, SELECT_BY_POS, MODE_TRADES)) continue;

        switch (StrategyFunctions::OrderType())
        {
        case tp_BuyStop: case tp_SellStop:
        case tp_BuyLimit: case tp_SellLimit:
            result++;
            break;
        }
    }

    return result;
}

//-----Get profit for open positions------------------------------------------
double TechnicalFunctions::GetOpenPosProfit()
{
    return (StrategyFunctions::AccountEquity() - StrategyFunctions::AccountBalance());
}

//-----Convert price type to string-------------------------------------------
const char * TechnicalFunctions::StrPriceType(TPriceType ptype)
{
    switch (ptype)
    {
    case pt_Close: return "Close";
    case pt_Open:  return "Open";
    case pt_High:  return "High";
    case pt_Low:   return "Low";
    case pt_HL2:   return "(High + Low)/2";
    case pt_HLC3:  return "(High + Low + Close)/3";
    case pt_HLCC4: return "(High + Low + Close + Close)/4";
    default:       return "";
    }
}

//-----Convert moving average type to string----------------------------------
const char * TechnicalFunctions::StrMAType(TMAType matype)
{
    switch (matype)
    {
    case ma_SMA:  return "Simple (SMA)";
    case ma_EMA:  return "Exponential (EMA)";
    case ma_WMA:  return "Weighted (WMA)";
    case ma_SSMA: return "Smoothed (SSMA)";
    default:      return "";
    }
}

//-----Create "MA type" option-------------------------------------------------
void TechnicalFunctions::RegMATypeOption(int& option, const char * name)
{
    if (strcmp(name, "") == 0) name = "MA type";
    StrategyFunctions::RegOption(name, ot_EnumType, &option);
    StrategyFunctions::AddOptionValue(name, "Simple (SMA)");
    StrategyFunctions::AddOptionValue(name, "Exponential (EMA)");
    StrategyFunctions::AddOptionValue(name, "Weighted (WMA)");
    StrategyFunctions::AddOptionValue(name, "Smoothed (SSMA)");
    option = 0;
}


//-----Create "Apply to price" option------------------------------------------
void TechnicalFunctions::RegApplyToPriceOption(int& option, const char * name)
{
    if (strcmp(name, "") == 0) name = "Apply to price";
    StrategyFunctions::RegOption(name, ot_EnumType, &option);
    StrategyFunctions::AddOptionValue(name, "Close");
    StrategyFunctions::AddOptionValue(name, "Open");
    StrategyFunctions::AddOptionValue(name, "High");
    StrategyFunctions::AddOptionValue(name, "Low");
    StrategyFunctions::AddOptionValue(name, "(High + Low)/2");
    StrategyFunctions::AddOptionValue(name, "(High + Low + Close)/3");
    StrategyFunctions::AddOptionValue(name, "(High + Low + Close + Close)/4");
    option = 0;
}
