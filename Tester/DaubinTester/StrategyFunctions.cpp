#include "StrategyFunctions.h"
#include <string>

#define rec IntrfProcsRec

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


extern "C" { __declspec(dllexport) TInterfaceProcRec IntrfProcsRec; }

//-----------------------------------------------------------------------------

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
    {
        memset(&IntrfProcsRec, 0, sizeof(TInterfaceProcRec));
        IntrfProcsRec.dwSize = sizeof(TInterfaceProcRec);
        break;
    }

    case DLL_THREAD_ATTACH:
        break;

    case DLL_THREAD_DETACH:
        break;

    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define rec IntrfProcsRec



//-----Replace PChar string with new one--------------------------------------
#pragma comment(linker, "/EXPORT:ReplaceStr=_ReplaceStr@8")
EXPORT void __stdcall ReplaceStr(char*& dest, PChar source)
{
    free((void*)dest);
    dest = (char*)malloc(strlen((char*)source) + 1);
    strcpy(dest, source);
}

//-----Sell-------------------------------------------------------------------
int StrategyFunctions::Sell(double LotSize, double StopLoss, double TakeProfit)
{
    double tp, sl;

    if (TakeProfit == 0) tp = 0; else tp = Bid() - TakeProfit * Point();
    if (StopLoss == 0) sl = 0; else sl = Bid() + StopLoss * Point();

    int result;
    SendInstantOrder(Symbol(), op_Sell, LotSize, sl, tp, "", 0, result);
    return result;
}

//-----Buy-------------------------------------------------------------------
int StrategyFunctions::Buy(double LotSize, double StopLoss, double TakeProfit)
{
    double tp, sl;

    if (TakeProfit == 0) tp = 0; else tp = Ask() + TakeProfit * Point();
    if (StopLoss == 0) sl = 0; else sl = Ask() - StopLoss * Point();

    int result;
    SendInstantOrder(Symbol(), op_Buy, LotSize, sl, tp, "", 0, result);
    return result;
}

/*
//-----Convert time to string-------------------------------------------------
function StrTime(DateTime: TDateTime): string;
{
  DateTimeToString(result, 'yyyy.mm.dd hh:nn', DateTime);
}
*/

//-----Get currency information-----------------------------------------------
bool StrategyFunctions::GetCurrencyInfo(const char * Symbol, PCurrencyInfo& info)
{
    return rec.GetCurrencyInfo(rec.pGetCurrencyInfo, Symbol, info);
}

//-----Register option--------------------------------------------------------
void StrategyFunctions::RegOption(const char * OptionName, TOptionType OptionType, void* option)
{
    rec.RegOption(rec.pRegOption, OptionName, OptionType, option);
}

//-----Add separator----------------------------------------------------------
void StrategyFunctions::AddSeparator(const char * text)
{
    rec.RegOption(rec.pRegOption, text, ot_Separator, NULL);
}

//-----Add option value (for drop down box options)---------------------------
void StrategyFunctions::AddOptionValue(const char * OptionName, PChar value)
{
    rec.AddOptionValue(rec.pAddOptionValue, OptionName, value);
}

//-----Set option range (for integer, longword and double types)--------------
void StrategyFunctions::SetOptionRange(const char * OptionName, double LowValue, double HighValue)
{
    rec.SetOptionRange(rec.pSetOptionRange, OptionName, LowValue, HighValue);
}

//-----Set option digits------------------------------------------------------
void StrategyFunctions::SetOptionDigits(const char * OptionName, Word digits)
{
    rec.SetOptionDigits(rec.pSetOptionDigits, OptionName, digits);
}

//-----Print text in "Journal" window in ForexTester--------------------------
void StrategyFunctions::Print(const char * s)
{
    rec.Print(rec.pPrint, s);
}

//-----Set strategy short name------------------------------------------------
void StrategyFunctions::StrategyShortName(const char * name)
{
    rec.StrategyShortName(rec.pStrategyShortName, name);
}

//-----Set strategy description-----------------------------------------------
void StrategyFunctions::StrategyDescription(const char * desc)
{
    rec.StrategyDescription(rec.pStrategyDescription, desc);
}

//-----Get Bid price----------------------------------------------------------
double StrategyFunctions::Bid()
{
    return rec.Bid(rec.pBid);
}

//-----Get Ask price----------------------------------------------------------
double StrategyFunctions::Ask()
{
    return rec.Ask(rec.pAsk);
}

//-----Currency name----------------------------------------------------------
const char * StrategyFunctions::Symbol()
{
    return rec.Symbol(rec.pSymbol);
}

//-----Currency digits after point--------------------------------------------
int StrategyFunctions::Digits()
{
    return rec.Digits(rec.pDigits);
}

//-----Minimal currency point-------------------------------------------------
double StrategyFunctions::Point()
{
    return rec.Point(rec.pPoint);
}

//-----Get open value---------------------------------------------------------
double StrategyFunctions::iOpen(const char * Symbol, int TimeFrame, int index)
{
    return rec.iOpen(rec.piOpen, Symbol, TimeFrame, index);
}

//-----Get close value--------------------------------------------------------
double StrategyFunctions::iClose(const char * Symbol, int TimeFrame, int index)
{
    return rec.iClose(rec.piClose, Symbol, TimeFrame, index);
}

//-----Get high value---------------------------------------------------------
double StrategyFunctions::iHigh(const char * Symbol, int TimeFrame, int index)
{
    return rec.iHigh(rec.piHigh, Symbol, TimeFrame, index);
}

//-----Get low value----------------------------------------------------------
double StrategyFunctions::iLow(const char * Symbol, int TimeFrame, int index)
{
    return rec.iLow(rec.piLow, Symbol, TimeFrame, index);
}

//-----Get volume-------------------------------------------------------------
double StrategyFunctions::iVolume(const char * Symbol, int TimeFrame, int index)
{
    return rec.iVolume(rec.piVolume, Symbol, TimeFrame, index);
}


//-----Get time of bar--------------------------------------------------------
TDateTime StrategyFunctions::iTime(const char * Symbol, int TimeFrame, int index)
{
    return rec.iTime(rec.piTime, Symbol, TimeFrame, index);
}

//-----Get number of bars-----------------------------------------------------
int StrategyFunctions::iBars(const char * Symbol, int TimeFrame)
{
    return rec.iBars(rec.piBars, Symbol, TimeFrame);
}

//-----Get open value in default currency and timeframe-----------------------
double StrategyFunctions::Open(int index)
{
    return rec.Open(rec.pOpen, index);
}

//-----Get close value in default currency and timeframe----------------------
double StrategyFunctions::Close(int index)
{
    return rec.Close(rec.pClose, index);
}

//-----Get high value in default currency and timeframe-----------------------
double StrategyFunctions::High(int index)
{
    return rec.High(rec.pHigh, index);
}

//-----Get low value in default currency and timeframe------------------------
double StrategyFunctions::Low(int index)
{
    return rec.Low(rec.pLow, index);
}

//-----Get volume in default currency and timeframe---------------------------
double StrategyFunctions::Volume(int index)
{
    return rec.Volume(rec.pVolume, index);
}

//-----Get time of bar in default currency and timeframe----------------------
TDateTime StrategyFunctions::Time(int index)
{
    return rec.Time(rec.pTime, index);
}

//-----Get number of bars in default currency and timeframe-------------------
int StrategyFunctions::Bars()
{
    return rec.Bars(rec.pBars);
}

//-----Set currency and timeframe---------------------------------------------
bool StrategyFunctions::SetCurrencyAndTimeframe(const char * Symbol, int TimeFrame)
{
    return rec.SetCurrencyAndTimeframe(rec.pSetCurrencyAndTimeframe, Symbol, TimeFrame);
}

//-----Get market information-------------------------------------------------
double StrategyFunctions::MarketInfo(const char * Symbol, TMarketInfo _type)
{
    return rec.MarketInfo(rec.pMarketInfo, Symbol, _type);
}

//-----Send instant order-----------------------------------------------------
bool StrategyFunctions::SendInstantOrder(const char * Symbol, TInstantOrderType OperationType, double LotSize,
    double StopLoss, double TakeProfit, const char * Comment, int MagicNumber, int& OrderHandle)
{
    return rec.SendInstantOrder2(rec.pSendInstantOrder2, Symbol, OperationType,
        LotSize, StopLoss, TakeProfit, Comment, MagicNumber, OrderHandle);
}

//-----Send pending order-----------------------------------------------------
bool StrategyFunctions::SendPendingOrder(const char * Symbol, TPendingOrderType OperationType, double LotSize,
    double StopLoss, double TakeProfit, double ExecutionPrice,
    const char * Comment, int MagicNumber, int& OrderHandle)
{
    return rec.SendPendingOrder2(rec.pSendPendingOrder2, Symbol, OperationType,
        LotSize, StopLoss, TakeProfit, ExecutionPrice, Comment, MagicNumber, OrderHandle);
}

//-----Modify order-----------------------------------------------------------
bool StrategyFunctions::ModifyOrder(int OrderHandle, double NewPrice, double StopLoss, double TakeProfit)
{
    return rec.ModifyOrder(rec.pModifyOrder, OrderHandle, NewPrice, StopLoss, TakeProfit);
}

//-----Delete order-----------------------------------------------------------
bool StrategyFunctions::DeleteOrder(int OrderHandle)
{
    return rec.DeleteOrder(rec.pDeleteOrder, OrderHandle);
}

//-----Close order------------------------------------------------------------
bool StrategyFunctions::CloseOrder(int OrderHandle)
{
    return rec.CloseOrder(rec.pCloseOrder, OrderHandle);
}

//-----Get order information--------------------------------------------------
bool StrategyFunctions::GetOrderInfo(int OrderHandle, TTradePosition& info)
{
    return rec.GetOrderInfo(rec.pGetOrderInfo, OrderHandle, info);
}

//-----Select order-----------------------------------------------------------
bool StrategyFunctions::OrderSelect(int index, TOrderSelectMode flags, TSearchMode pool)
{
    return rec.OrderSelect(rec.pOrderSelect, index, flags, pool);
}

//-----Get profit in dollars of selected order--------------------------------
double StrategyFunctions::OrderProfit()
{
    return rec.OrderProfit(rec.pOrderProfit);
}

//-----Get profit in pips of selected order-----------------------------------
double StrategyFunctions::OrderProfitPips()
{
    return rec.OrderProfitPips(rec.pOrderProfitPips);
}

//-----Check if order was closed----------------------------------------------
bool StrategyFunctions::OrderClosed(int OrderHandle)
{
    return rec.OrderClosed(rec.pOrderClosed, OrderHandle);
}

//-----Number of closed positions---------------------------------------------
int StrategyFunctions::HistoryTotal()
{
    return rec.HistoryTotal(rec.pHistoryTotal);
}

//-----Number of opened positions---------------------------------------------
int StrategyFunctions::OrdersTotal()
{
    return rec.OrdersTotal(rec.pOrdersTotal);
}

//-----Open time of selected order--------------------------------------------
TDateTime StrategyFunctions::OrderOpenTime()
{
    return rec.OrderOpenTime(rec.pOrderOpenTime);
}

//-----Close time of selected order-------------------------------------------
TDateTime StrategyFunctions::OrderCloseTime()
{
    return rec.OrderCloseTime(rec.pOrderCloseTime);
}

//-----Lot size of selected order---------------------------------------------
double StrategyFunctions::OrderLots()
{
    return rec.OrderLots(rec.pOrderLots);
}

//-----Handle of selected order-----------------------------------------------
int StrategyFunctions::OrderTicket()
{
    return rec.OrderTicket(rec.pOrderTicket);
}

//-----Type of the selected order---------------------------------------------
TTradePositionType StrategyFunctions::OrderType()
{
    return TTradePositionType(rec.OrderType(rec.pOrderType));
}

//-----Stop loss of selected order--------------------------------------------
double StrategyFunctions::OrderStopLoss()
{
    return rec.OrderStopLoss(rec.pOrderStopLoss);
}

//-----Take profit of selected order------------------------------------------
double StrategyFunctions::OrderTakeProfit()
{
    return rec.OrderTakeProfit(rec.pOrderTakeProfit);
}

//-----Open price of selected order-------------------------------------------
double StrategyFunctions::OrderOpenPrice()
{
    return rec.OrderOpenPrice(rec.pOrderOpenPrice);
}

//-----Close price of selected order------------------------------------------
double StrategyFunctions::OrderClosePrice()
{
    return rec.OrderClosePrice(rec.pOrderClosePrice);
}

//-----Currency of selected order---------------------------------------------
const char * StrategyFunctions::OrderSymbol()
{
    return rec.OrderSymbol(rec.pOrderSymbol);
}

//-----Get stop loss in points------------------------------------------------
int StrategyFunctions::GetStopLossPoints(int OrderHandle)
{
    int result = 0;

    if (OrderSelect(OrderHandle, SELECT_BY_TICKET, MODE_TRADES))
    {
        if (OrderStopLoss() == 0) return result;

        PCurrencyInfo pInfo;
        if (!GetCurrencyInfo(OrderSymbol(), pInfo)) return result;

        result = int((OrderOpenPrice() - OrderStopLoss()) / pInfo->Point);
        if (OrderType() == tp_Buy) result = -result;
    }

    return result;
}

//-----Get take profit points-------------------------------------------------
int StrategyFunctions::GetTakeProfitPoints(int OrderHandle)
{
    int result = 0;

    if (OrderSelect(OrderHandle, SELECT_BY_TICKET, MODE_TRADES))
    {
        if (OrderTakeProfit() == 0) return result;

        PCurrencyInfo pInfo;
        if (!GetCurrencyInfo(OrderSymbol(), pInfo)) return result;

        result = int((OrderOpenPrice() - OrderTakeProfit()) / pInfo->Point);
        if (OrderType() == tp_Sell) result = -result;
    }

    return result;
}


//-----Set stop loss in points------------------------------------------------
void StrategyFunctions::SetStopLossPoints(int OrderHandle, int NewStopLoss)
{
    if (OrderSelect(OrderHandle, SELECT_BY_TICKET, MODE_TRADES))
    {
        PCurrencyInfo pInfo;
        if (!GetCurrencyInfo(OrderSymbol(), pInfo)) return;

        switch (OrderType())
        {
        case tp_Buy:
            ModifyOrder(OrderHandle, OrderOpenPrice(),
                OrderOpenPrice() - NewStopLoss * pInfo->Point, OrderTakeProfit());
            break;

        case tp_Sell:
            ModifyOrder(OrderHandle, OrderOpenPrice(),
                OrderOpenPrice() + NewStopLoss * pInfo->Point, OrderTakeProfit());
            break;
        }
    }
}

//-----Set take profit in points----------------------------------------------
void StrategyFunctions::SetTakeProfitPoints(int OrderHandle, int NewTakeProfit)
{
    if (OrderSelect(OrderHandle, SELECT_BY_TICKET, MODE_TRADES))
    {
        PCurrencyInfo pInfo;
        if (!GetCurrencyInfo(OrderSymbol(), pInfo)) return;

        switch (OrderType())
        {
        case tp_Buy:
            ModifyOrder(OrderHandle, OrderOpenPrice(),
                OrderOpenPrice() + NewTakeProfit * pInfo->Point, OrderTakeProfit());
            break;

        case tp_Sell:
            ModifyOrder(OrderHandle, OrderOpenPrice(),
                OrderOpenPrice() - NewTakeProfit * pInfo->Point, OrderTakeProfit());
            break;
        }
    }
}

//-----Get account balance----------------------------------------------------
double StrategyFunctions::AccountBalance()
{
    if (rec.pAccountBalance == NULL) return 0;
    return rec.AccountBalance(rec.pAccountBalance);
}

//-----Get account equity-----------------------------------------------------
double StrategyFunctions::AccountEquity()
{
    if (rec.pAccountEquity == NULL) return 0;
    return rec.AccountEquity(rec.pAccountEquity);
}

//-----Get account margin-----------------------------------------------------
double StrategyFunctions::AccountMargin()
{
    if (rec.pAccountMargin == NULL) return 0;
    return rec.AccountMargin(rec.pAccountMargin);
}

//-----Get account free margin------------------------------------------------
double StrategyFunctions::AccountFreeMargin()
{
    if (rec.pAccountFreeMargin == NULL) return 0;
    return rec.AccountFreeMargin(rec.pAccountFreeMargin);
}

//-----Get account leverage---------------------------------------------------
int StrategyFunctions::AccountLeverage()
{
    if (rec.pAccountLeverage == NULL) return 0;
    return rec.AccountLeverage(rec.pAccountLeverage);
}

//-----Get account profit-----------------------------------------------------
double StrategyFunctions::AccountProfit()
{
    if (rec.pAccountProfit == NULL) return 0;
    return rec.AccountProfit(rec.pAccountProfit);
}

//-----Breakpoint-------------------------------------------------------------
void StrategyFunctions::Breakpoint(int number, const char * text)
{
    if (rec.pBreakpoint == NULL) return;
    rec.Breakpoint(rec.pBreakpoint, number, text);
}


//-----Create indicator and obtaind id----------------------------------------
int StrategyFunctions::CreateIndicator(const char * Symbol, int TimeFrame, PChar IndicatorName, PChar parameters)
{
    if (IntrfProcsRec.pCreateIndicator == NULL) return 0;
    std::string indicatorName = IndicatorName;
    indicatorName += ".dll";

    return rec.CreateIndicator(rec.pCreateIndicator, Symbol, TimeFrame,
        indicatorName.c_str(), parameters);
}

//-----Get indicator value----------------------------------------------------
double StrategyFunctions::GetIndicatorValue(int IndicatorHandle, int index, int BufferIndex)
{
    if (rec.pGetIndicatorValue == NULL) return 0;
    return rec.GetIndicatorValue(rec.pGetIndicatorValue, IndicatorHandle, index, BufferIndex);
}

//-----Get order MagicNumber--------------------------------------------------
int StrategyFunctions::OrderMagicNumber()
{
    if (rec.pOrderMagicNumber == NULL) return 0;
    return rec.OrderMagicNumber(rec.pOrderMagicNumber);
}

//-----Get order comment------------------------------------------------------
const char * StrategyFunctions::OrderComment()
{
    if (rec.pOrderComment == NULL) return "";
    return rec.OrderComment(rec.pOrderComment);
}

//-----Order swap-------------------------------------------------------------
double StrategyFunctions::OrderSwap()
{
    if (rec.pOrderSwap == NULL) return 0;
    return rec.OrderSwap(rec.pOrderSwap);
}

//-----Pause------------------------------------------------------------------
void StrategyFunctions::Pause(const char * text)
{
    if (rec.pPause == NULL) return;
    rec.Pause(rec.pPause, text);
}

//-----Resume-----------------------------------------------------------------
void StrategyFunctions::Resume()
{
    if (rec.pResume) return;
    rec.Resume(rec.pResume);
}


//-----Send instant order with selected price---------------------------------
bool StrategyFunctions::_SendInstantOrder(const char * Symbol, TInstantOrderType OperationType, double price,
    double LotSize, double StopLoss, double TakeProfit, const char * Comment, int MagicNumber, int& OrderHandle)
{
    if (rec.p_SendInstantOrder == NULL)
    {
        OrderHandle = -1;
        return false;
    }

    return rec._SendInstantOrder(rec.p_SendInstantOrder, Symbol, OperationType,
        price, LotSize, StopLoss, TakeProfit, Comment, MagicNumber, OrderHandle);
}

//-----Close order with requested price---------------------------------------
bool StrategyFunctions::_CloseOrder(int OrderHandle, double price)
{
    if (rec.p_CloseOrder == NULL) return false;
    return rec._CloseOrder(rec.p_CloseOrder, OrderHandle, price);
}

//-----Create object----------------------------------------------------------
bool StrategyFunctions::ObjectCreate(const char * name, TObjectType ObjType, int window,
    TDateTime time1, double price1, TDateTime time2, double price2,
    TDateTime time3, double price3)
{
    if (rec.pObjectCreate == NULL) return false;
    return rec.ObjectCreate(rec.pObjectCreate, name, ObjType,
        window, time1, price1, time2, price2, time3, price3);
}

//-----Delete object by name--------------------------------------------------
void StrategyFunctions::ObjectDelete(const char * name)
{
    if (rec.pObjectDelete == NULL) return;
    rec.ObjectDelete(rec.pObjectDelete, name);
}

//-----Check if object already exists-----------------------------------------
bool StrategyFunctions::ObjectExists(const char * name)
{
    if (rec.pObjectExists == NULL) return false;
    return rec.ObjectExists(rec.pObjectExists, name);
}

//-----Get object type--------------------------------------------------------
TObjectType StrategyFunctions::ObjectType(const char * name)
{
    if (rec.pObjectType == NULL) return obj_Text;
    return TObjectType(rec.ObjectType(rec.pObjectType, name));
}

//-----Set object property----------------------------------------------------
bool StrategyFunctions::ObjectSet(const char * name, int index, double value)
{
    if (rec.pObjectSet == NULL) return false;
    return rec.ObjectSet(rec.pObjectSet, name, index, value);
}

//-----Get object property----------------------------------------------------
double StrategyFunctions::ObjectGet(const char * name, int index)
{
    if (rec.pObjectGet == NULL) return 0;
    return rec.ObjectGet(rec.pObjectGet, name, index);
}

//-----Delete all objects-----------------------------------------------------
void StrategyFunctions::ObjectsDeleteAll(int window, TObjectType ObjType)
{
    if (rec.pObjectsDeleteAll == NULL) return;
    rec.ObjectsDeleteAll(rec.pObjectsDeleteAll, window, ObjType);
}

//-----Get interface version--------------------------------------------------
void StrategyFunctions::GetInterfaceVersion(int& MajorValue, int& MinorValue)
{
    if (rec.pGetInterfaceVersion == NULL)
    {
        MajorValue = 1;
        MinorValue = 4;
        return;
    }

    rec.GetInterfaceVersion(rec.pGetInterfaceVersion, MajorValue, MinorValue);
}

//-----Set text---------------------------------------------------------------
bool StrategyFunctions::ObjectSetText(const char * name, PChar text, int FontSize, PChar FontName, TColor Color)
{
    if (rec.pObjectSetText == NULL) return false;
    return rec.ObjectSetText(rec.pObjectSetText, name, text, FontSize, FontName, Color);
}

//-----Get text---------------------------------------------------------------
const char * StrategyFunctions::ObjectGetText(PChar name)
{
    if (rec.pObjectGetText == NULL) return NULL;
    return rec.ObjectGetText(rec.pObjectGetText, name);
}

//-----Get current time-------------------------------------------------------
TDateTime  StrategyFunctions::TimeCurrent()
{
    if (rec.pTimeCurrent == NULL) return false;
    return rec.TimeCurrent(rec.pTimeCurrent);
}

//-----Set indicator's buffer style-------------------------------------------
void StrategyFunctions::SetIndicatorBuffStyle(int IndicatorHandle, int BuffIndex, TPenStyle _style,
    int width, TColor color)
{
    if (rec.pSetIndicatorBuffStyle == NULL) return;
    rec.SetIndicatorBuffStyle(rec.pSetIndicatorBuffStyle, IndicatorHandle, BuffIndex, _style,
        width, color);
}

//-----Get bar shift by its time----------------------------------------------
int StrategyFunctions::iBarShift(const char * Symbol, int TimeFrame, TDateTime time, bool Exact)
{
    if (rec.iBarShift == NULL) return -1;
    return rec.iBarShift(rec.piBarShift, Symbol, TimeFrame, time, Exact);
}

//-----Get highest value in array---------------------------------------------
int StrategyFunctions::iHighest(const char * Symbol, int TimeFrame, int _type, int count, int index)
{
    if (rec.iHighest == NULL) return -1;
    return rec.iHighest(rec.piHighest, Symbol, TimeFrame, _type, count, index);
}

//-----Get lowest value in array----------------------------------------------
int StrategyFunctions::iLowest(const char * Symbol, int TimeFrame, int _type, int count, int index)
{
    if (rec.iLowest == NULL) return -1;
    return rec.iLowest(rec.piLowest, Symbol, TimeFrame, _type, count, index);
}

//-----Close part of position-------------------------------------------------
bool StrategyFunctions::CloseOrderPartial(int OrderHandle, double LotSize)
{
    if (rec.CloseOrderPartial == NULL) return false;
    return rec.CloseOrderPartial(rec.pCloseOrderPartial, OrderHandle, LotSize);
}
#undef rec
