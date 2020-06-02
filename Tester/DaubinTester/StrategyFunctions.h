#pragma once
#include "StrategyConnecter.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//-------------------------------------------
// trade position
//-------------------------------------------
struct TTradePosition {
    int ticket;                  // order handle
    TDateTime OpenTime;          // order open time
    TDateTime CloseTime;         // order close time
    int PosType;                 // position type (tp_Buy ... tp_Credit)
    double lot;                  // lot
    const char* Symbol;                // currency name
    double OpenPrice;            // open price
    double ClosePrice;           // close price
    double StopLoss;             // stop loss
    double TakeProfit;           // take profit
    double commission;           // comission
    double swap;                 // swap
    double profit;               // profit in USD
    int ProfitPips;              // profit in pips
    const char* comments;              // comments
    double margin;               // margin
};
//-------------------------------------------
// currency information
//-------------------------------------------
struct TCurrencyInfo {
    const char * Symbol;               // currency name
    int Digits;                 // number of digits after '.'
    int spread;                 // spread in pips
    double Point;               // minimal currency point
    int lot;                    // 1 lot cost
    const char * curr;                 // lot currency
    double SwapLong;            // swap points long
    double SwapShort;           // swap points short
};



// option type
enum TOptionType {
    ot_Longword = 0,
    ot_Integer = 1,
    ot_Double = 2,
    ot_String = 3,
    ot_Boolean = 4,
    ot_EnumType = 5,
    ot_TimeFrame = 6,
    ot_Currency = 7,
    ot_LineStyle = 8,
    ot_Separator = 9,
    ot_Reserved0 = 10,
    ot_Color = 11
};

// search mode
enum TSearchMode {
    MODE_TRADES = 0,
    MODE_HISTORY = 1
};

// order select mode
enum TOrderSelectMode {
    SELECT_BY_POS = 0,
    SELECT_BY_TICKET = 1
};

// market info constants
enum TMarketInfo {
    MODE_BID = 0,
    MODE_ASK = 1
};

// trade position type
enum TTradePositionType {
    tp_Buy = 0,
    tp_Sell = 1,
    tp_BuyLimit = 2,
    tp_SellLimit = 3,
    tp_BuyStop = 4,
    tp_SellStop = 5,
    tp_Balance = 6,
    tp_Credit = 7
};

// instant operation type
enum TInstantOrderType {
    op_Buy = 0,
    op_Sell = 1
};

// pending operation type
enum TPendingOrderType {
    op_BuyLimit = 0,
    op_BuyStop = 1,
    op_SellLimit = 2,
    op_SellStop = 3
};

// object types
enum TObjectType {
    obj_AnyObject = 0,
    obj_VLine = 1,
    obj_HLine = 2,
    obj_TrendLine = 3,
    obj_Ray = 4,
    obj_PolyLine = 5,
    obj_FiboRetracement = 6,
    obj_FiboTimeZones = 7,
    obj_FiboArc = 8,
    obj_FiboFan = 9,
    obj_AndrewsPitchfork = 10,
    obj_Text = 11,
    obj_TextLabel = 12
};


// indicator window
enum TOutputWindow {
    ow_ChartWindow = 0,
    ow_SeparateWindow = 1
};

// indicator interface procedures
typedef bool(__stdcall* TGetCurrencyInfoFunc) (void* ptr, PChar Symbol, TCurrencyInfo*& info);
typedef void(__stdcall* TSetPropertyProc) (void* ptr, int PropertyID, void* value);
typedef void(__stdcall* TRegOptionProc) (void* ptr, PChar OptionName, int OptionType, void* OptionPtr);
typedef void(__stdcall* TAddOptionValueProc) (void* ptr, PChar OptionName, PChar value);
typedef void(__stdcall* TSetOptionRange) (void* ptr, PChar OptionName, double LowValue, double HighValue);

typedef void(__stdcall* TSetOptionDigitsProc) (void* ptr, PChar OptionName, Word digits);
typedef void(__stdcall* TPrintProc) (void* ptr, PChar s);
typedef double(__stdcall* TGetDoubleFunc) (void* ptr);
typedef PChar(__stdcall* TGetPCharFunc) (void* ptr);
typedef int(__stdcall* TGetIntegerFunc) (void* ptr);

typedef TDateTime(__stdcall* TGetDateTimeFunc) (void* ptr);
typedef double(__stdcall* TGet_iOHLCVFunc) (void* ptr, PChar Symbol, int TimeFrame, int index);
typedef TDateTime(__stdcall* TGet_iTimeFunc) (void* ptr, PChar Symbol, int TimeFrame, int index);
typedef unsigned long int(__stdcall* TGet_iBarsFunc) (void* ptr, PChar Symbol, int TimeFrame);
typedef double(__stdcall* TGetOHLCVFunc) (void* ptr, int index);

typedef TDateTime(__stdcall* TGetTimeFunc) (void* ptr, int index);
typedef unsigned long int(__stdcall* TGetBarsFunc) (void* ptr);

typedef bool(__stdcall* TSendInstantOrderFunc) (void* ptr, PChar Symbol, int OperationType,
    double LotSize, double StopLoss, double TakeProfit, int& OrderHandle);

typedef bool(__stdcall* TSendInstantOrder2Func) (void* ptr, PChar Symbol, int OperationType,
    double LotSize, double StopLoss, double TakeProfit, PChar comment, int MagicNumber, int& OrderHandle);

typedef bool(__stdcall* T_SendInstantOrderFunc) (void* ptr, PChar Symbol, int OperationType,
    double price, double LotSize, double StopLoss, double TakeProfit, PChar comment, int MagicNumber, int& OrderHandle);

typedef bool(__stdcall* TSendPendingOrderFunc) (void* ptr, PChar Symbol, int OperationType,
    double LotSize, double StopLoss, double TakeProfit, double ExecutionPrice, int& OrderHandle);

typedef bool(__stdcall* TSendPendingOrder2Func) (void* ptr, PChar Symbol, int OperationType,
    double LotSize, double StopLoss, double TakeProfit, double ExecutionPrice, PChar comment, int MagicNumber, int& OrderHandle);

typedef bool(__stdcall* TModifyOrderFunc) (void* ptr, int OrderHandle, double NewPrice, double StopLoss, double TakeProfit);
typedef bool(__stdcall* TDeleteOrderFunc) (void* ptr, int OrderHandle);
typedef bool(__stdcall* TCloseOrderFunc) (void* ptr, int OrderHandle);
typedef bool(__stdcall* T_CloseOrderFunc) (void* ptr, int OrderHandle, double peice);
typedef bool(__stdcall* TGetOrderInfoFunc) (void* ptr, int OrderHandle, TTradePosition& info);

typedef bool(__stdcall* TSetCurrencyAndTimeframeFunc) (void* ptr, PChar Symbol, int TimeFrame);
typedef bool(__stdcall* TOrderSelectFunc) (void* ptr, int index, int flags, int pool);
typedef bool(__stdcall* TOrderClosedFunc) (void* ptr, int OrderHandle);
typedef double(__stdcall* TMarketInfoFunc) (void* ptr, PChar Symbol, int _type);
typedef void(__stdcall* TStrategyShortNameProc) (void* ptr, PChar name);

typedef void(__stdcall* TStrategyDescriptionProc) (void* ptr, PChar desc);
typedef void(__stdcall* TBreakpointProc) (void* ptr, int number, PChar text);
typedef int(__stdcall* TCreateIndicatorFunc) (void* ptr, PChar CurrencyName, int Timeframe,
    PChar IndicatorName, PChar parameters);

typedef double(__stdcall* TGetIndicatorValueFunc) (void* ptr, int IndicatorHandle, int index, int BufferIndex);
typedef void(__stdcall* TPauseProc) (void* ptr, PChar text);
typedef void(__stdcall* TResumeProc) (void* ptr);
typedef void(__stdcall* TGetInterfaceVersionProc) (void* ptr, int& MajorValue, int& MinorValue);

typedef bool(__stdcall* TObjectCreateFunc) (void* ptr, PChar name, int ObjType, int window,
    TDateTime time1, double price1, TDateTime time2, double price2, TDateTime time3, double price3);

typedef void(__stdcall* TObjectDeleteProc) (void* ptr, PChar name);
typedef bool(__stdcall* TObjectExistsFunc) (void* ptr, PChar name);
typedef int(__stdcall* TObjectTypeFunc) (void* ptr, PChar name);
typedef bool(__stdcall* TObjectSetFunc) (void* ptr, PChar name, int index, double value);
typedef double(__stdcall* TObjectGetFunc) (void* ptr, PChar name, int index);

typedef void(__stdcall* TObjectsDeleteAllProc) (void* ptr, int window, int ObjType);
typedef bool(__stdcall* TObjectSetTextFunc) (void* ptr, PChar name, PChar text, int FontSize,
    PChar FontName, int Color);

typedef void(__stdcall* TSetIndicatorBuffStyleProc) (void* ptr, int IndicatorHandle,
    int BuffIndex, int _style, int width, int color);

typedef int(__stdcall* TIBarShiftFunc) (void* ptr, PChar Symbol, int TimeFrame, TDateTime time, bool Exact);
typedef int(__stdcall* TIHighestFunc) (void* ptr, PChar Symbol, int TimeFrame, int _type, int count, int index);
typedef int(__stdcall* TILowestFunc) (void* ptr, PChar Symbol, int TimeFrame, int _type, int count, int index);

typedef bool(__stdcall* TCloseOrderPartialFunc) (void* ptr, int OrderHandle, double LotSize);

typedef PChar(__stdcall* TObjectGetTextFunc) (void* ptr, PChar name);


// pointers to interface procedures

#pragma pack(push)
struct TInterfaceProcRec {
    LongWord dwSize;

    TRegOptionProc RegOption;
    void* pRegOption;

    TAddOptionValueProc AddOptionValue;
    void* pAddOptionValue;

    TSetOptionRange SetOptionRange;
    void* pSetOptionRange;

    TSetOptionDigitsProc SetOptionDigits;
    void* pSetOptionDigits;

    TPrintProc Print;
    void* pPrint;

    TStrategyShortNameProc StrategyShortName;
    void* pStrategyShortName;

    TStrategyDescriptionProc StrategyDescription;
    void* pStrategyDescription;

    TGetCurrencyInfoFunc GetCurrencyInfo;
    void* pGetCurrencyInfo;

    TSetCurrencyAndTimeframeFunc SetCurrencyAndTimeframe;
    void* pSetCurrencyAndTimeframe;

    TMarketInfoFunc MarketInfo;
    void* pMarketInfo;

    TGetDoubleFunc Bid;
    void* pBid;

    TGetDoubleFunc Ask;
    void* pAsk;

    TGetPCharFunc Symbol;
    void* pSymbol;

    TGetIntegerFunc Digits;
    void* pDigits;

    TGetDoubleFunc Point;
    void* pPoint;

    TSendInstantOrderFunc SendInstantOrder;
    void* pSendInstantOrder;

    TSendPendingOrderFunc SendPendingOrder;
    void* pSendPendingOrder;

    TModifyOrderFunc ModifyOrder;
    void* pModifyOrder;

    TDeleteOrderFunc DeleteOrder;
    void* pDeleteOrder;

    TCloseOrderFunc CloseOrder;
    void* pCloseOrder;

    TOrderClosedFunc OrderClosed;
    void* pOrderClosed;

    TGetOrderInfoFunc GetOrderInfo;
    void* pGetOrderInfo;

    TOrderSelectFunc OrderSelect;
    void* pOrderSelect;

    TGetDoubleFunc OrderProfit;
    void* pOrderProfit;

    TGetDoubleFunc OrderProfitPips;
    void* pOrderProfitPips;

    TGetIntegerFunc HistoryTotal;
    void* pHistoryTotal;

    TGetIntegerFunc OrdersTotal;
    void* pOrdersTotal;

    TGetDateTimeFunc OrderOpenTime;
    void* pOrderOpenTime;

    TGetDateTimeFunc OrderCloseTime;
    void* pOrderCloseTime;

    TGetDoubleFunc OrderLots;
    void* pOrderLots;

    TGetIntegerFunc OrderTicket;
    void* pOrderTicket;

    TGetIntegerFunc OrderType;
    void* pOrderType;

    TGetDoubleFunc OrderStopLoss;
    void* pOrderStopLoss;

    TGetDoubleFunc OrderTakeProfit;
    void* pOrderTakeProfit;

    TGetDoubleFunc OrderOpenPrice;
    void* pOrderOpenPrice;

    TGetDoubleFunc OrderClosePrice;
    void* pOrderClosePrice;

    TGetPCharFunc OrderSymbol;
    void* pOrderSymbol;

    TGet_iOHLCVFunc iOpen;
    void* piOpen;

    TGet_iOHLCVFunc iClose;
    void* piClose;

    TGet_iOHLCVFunc iHigh;
    void* piHigh;

    TGet_iOHLCVFunc iLow;
    void* piLow;

    TGet_iOHLCVFunc iVolume;
    void* piVolume;

    TGet_iTimeFunc iTime;
    void* piTime;

    TGet_iBarsFunc iBars;
    void* piBars;

    TGetOHLCVFunc Open;
    void* pOpen;

    TGetOHLCVFunc Close;
    void* pClose;

    TGetOHLCVFunc High;
    void* pHigh;

    TGetOHLCVFunc Low;
    void* pLow;

    TGetOHLCVFunc Volume;
    void* pVolume;

    TGetTimeFunc Time;
    void* pTime;

    TGetBarsFunc Bars;
    void* pBars;

    // extensions ver 1.1 (dwSize > 412)
    TGetDoubleFunc AccountBalance;
    void* pAccountBalance;

    TGetDoubleFunc AccountEquity;
    void* pAccountEquity;

    TGetDoubleFunc AccountMargin;
    void* pAccountMargin;

    TGetDoubleFunc AccountFreeMargin;
    void* pAccountFreeMargin;

    TGetIntegerFunc AccountLeverage;
    void* pAccountLeverage;

    TGetDoubleFunc AccountProfit;
    void* pAccountProfit;

    TBreakpointProc Breakpoint;
    void* pBreakpoint;

    // extensions ver 1.2 (dwSize > 468)
    TCreateIndicatorFunc CreateIndicator;
    void* pCreateIndicator;

    TGetIndicatorValueFunc GetIndicatorValue;
    void* pGetIndicatorValue;

    // extensions ver 1.3 (dwSize > 484)
    TSendInstantOrder2Func SendInstantOrder2;
    void* pSendInstantOrder2;

    TSendPendingOrder2Func SendPendingOrder2;
    void* pSendPendingOrder2;

    TGetPCharFunc OrderComment;
    void* pOrderComment;

    TGetIntegerFunc OrderMagicNumber;
    void* pOrderMagicNumber;

    // extensions ver 1.4 (dwSize > 516)
    TPauseProc Pause;
    void* pPause;

    TResumeProc Resume;
    void* pResume;

    // extensions ver 1.41 (dwSize > 532)
    T_SendInstantOrderFunc _SendInstantOrder;
    void* p_SendInstantOrder;

    T_CloseOrderFunc _CloseOrder;
    void* p_CloseOrder;

    // extensions ver 1.5 (dwSize > 548)
    TGetInterfaceVersionProc GetInterfaceVersion;
    void* pGetInterfaceVersion;

    TObjectCreateFunc ObjectCreate;
    void* pObjectCreate;

    TObjectDeleteProc ObjectDelete;
    void* pObjectDelete;

    TObjectExistsFunc ObjectExists;
    void* pObjectExists;

    TObjectTypeFunc ObjectType;
    void* pObjectType;

    TObjectSetFunc ObjectSet;
    void* pObjectSet;

    TObjectGetFunc ObjectGet;
    void* pObjectGet;

    TObjectsDeleteAllProc ObjectsDeleteAll;
    void* pObjectsDeleteAll;

    TObjectSetTextFunc ObjectSetText;
    void* pObjectSetText;

    // extentions ver 1.7
    TGetDateTimeFunc TimeCurrent;
    void* pTimeCurrent;

    TSetIndicatorBuffStyleProc SetIndicatorBuffStyle;
    void* pSetIndicatorBuffStyle;

    // extensions ver 1.8 (dwSize > 636)
    TIBarShiftFunc iBarShift;
    void* piBarShift;

    TIHighestFunc iHighest;
    void* piHighest;

    TILowestFunc iLowest;
    void* piLowest;

    // extensions ver 1.9 (dwSize > 660)
    TCloseOrderPartialFunc CloseOrderPartial;
    void* pCloseOrderPartial;

    // extensions ver 1.10 (dwSize > 668)
    TObjectGetTextFunc ObjectGetText;
    void* pObjectGetText;

    // extensions ver 1.11 (dwSize > 676)
    TGetDoubleFunc OrderSwap;
    void* pOrderSwap;
};
#pragma pack(pop)


class __declspec(dllexport)  StrategyFunctions {
	public:
        //-----Sell-------------------------------------------------------------------
        static int Sell(double LotSize, double StopLoss, double TakeProfit, const char * comment = "");

        //-----Buy-------------------------------------------------------------------
        static int Buy(double LotSize, double StopLoss, double TakeProfit, const char * comment = "");

        //-----Get currency information-----------------------------------------------
        static bool GetCurrencyInfo(const char * Symbol, PCurrencyInfo& info);

        //-----Register option--------------------------------------------------------
        static void RegOption(const char * OptionName, TOptionType OptionType, void* option);

        //-----Add separator----------------------------------------------------------
        static void AddSeparator(const char * text);

        //-----Add option value (for drop down box options)---------------------------
        static void AddOptionValue(const char * OptionName, const char * value);

        //-----Set option range (for integer, longword and double types)--------------
        static void SetOptionRange(const char * OptionName, double LowValue, double HighValue);

        //-----Set option digits------------------------------------------------------
        static void SetOptionDigits(const char * OptionName, Word digits);

        //-----Print text in "Journal" window in ForexTester--------------------------
        static void Print(const char * s);

        //-----Set strategy short name------------------------------------------------
        static void StrategyShortName(const char * name);

        //-----Set strategy description-----------------------------------------------
        static void StrategyDescription(const char * desc);

        //-----Get Bid price----------------------------------------------------------
        static double Bid();

        //-----Get Ask price----------------------------------------------------------
        static double Ask();

        //-----Currency name----------------------------------------------------------
        static const char * Symbol();

        //-----Currency digits after point--------------------------------------------
        static int Digits();

        //-----Minimal currency point-------------------------------------------------
        static double Point();

        //-----Get open value---------------------------------------------------------
        static double iOpen(const char * Symbol, int TimeFrame, int index);

        //-----Get close value--------------------------------------------------------
        static double iClose(const char * Symbol, int TimeFrame, int index);

        //-----Get high value---------------------------------------------------------
        static double iHigh(const char * Symbol, int TimeFrame, int index);

        //-----Get low value----------------------------------------------------------
        static double iLow(const char * Symbol, int TimeFrame, int index);

        //-----Get volume-------------------------------------------------------------
        static double iVolume(const char * Symbol, int TimeFrame, int index);


        //-----Get time of bar--------------------------------------------------------
        static TDateTime iTime(const char * Symbol, int TimeFrame, int index);

        //-----Get number of bars-----------------------------------------------------
        static int iBars(const char * Symbol, int TimeFrame);

        //-----Get open value in default currency and timeframe-----------------------
        static double Open(int index);

        //-----Get close value in default currency and timeframe----------------------
        static double Close(int index);

        //-----Get high value in default currency and timeframe-----------------------
        static double High(int index);

        //-----Get low value in default currency and timeframe------------------------
        static double Low(int index);

        //-----Get volume in default currency and timeframe---------------------------
        static double Volume(int index);

        //-----Get time of bar in default currency and timeframe----------------------
        static TDateTime Time(int index);

        //-----Get number of bars in default currency and timeframe-------------------
        static int Bars();

        //-----Set currency and timeframe---------------------------------------------
        static bool SetCurrencyAndTimeframe(const char * Symbol, int TimeFrame);

        //-----Get market information-------------------------------------------------
        static double MarketInfo(const char * Symbol, TMarketInfo _type);

        //-----Send instant order-----------------------------------------------------
        static bool SendInstantOrder(const char * Symbol, TInstantOrderType OperationType, double LotSize,
            double StopLoss, double TakeProfit, const char * Comment, int MagicNumber, int& OrderHandle);

        //-----Send pending order-----------------------------------------------------
        static bool SendPendingOrder(const char * Symbol, TPendingOrderType OperationType, double LotSize,
            double StopLoss, double TakeProfit, double ExecutionPrice,
            const char * Comment, int MagicNumber, int& OrderHandle);

        //-----Modify order-----------------------------------------------------------
        static bool ModifyOrder(int OrderHandle, double NewPrice, double StopLoss, double TakeProfit);

        //-----Delete order-----------------------------------------------------------
        static bool DeleteOrder(int OrderHandle);

        //-----Close order------------------------------------------------------------
        static bool CloseOrder(int OrderHandle);

        //-----Get order information--------------------------------------------------
        static bool GetOrderInfo(int OrderHandle, TTradePosition& info);

        //-----Select order-----------------------------------------------------------
        static bool OrderSelect(int index, TOrderSelectMode flags, TSearchMode pool);

        //-----Get profit in dollars of selected order--------------------------------
        static double OrderProfit();

        //-----Get profit in pips of selected order-----------------------------------
        static double OrderProfitPips();

        //-----Check if order was closed----------------------------------------------
        static bool OrderClosed(int OrderHandle);

        //-----Number of closed positions---------------------------------------------
        static int HistoryTotal();

        //-----Number of opened positions---------------------------------------------
        static int OrdersTotal();

        //-----Open time of selected order--------------------------------------------
        static TDateTime OrderOpenTime();

        //-----Close time of selected order-------------------------------------------
        static TDateTime OrderCloseTime();

        //-----Lot size of selected order---------------------------------------------
        static double OrderLots();

        //-----Handle of selected order-----------------------------------------------
        static int OrderTicket();

        //-----Type of the selected order---------------------------------------------
        static TTradePositionType OrderType();

        //-----Stop loss of selected order--------------------------------------------
        static double OrderStopLoss();

        //-----Take profit of selected order------------------------------------------
        static double OrderTakeProfit();

        //-----Open price of selected order-------------------------------------------
        static double OrderOpenPrice();

        //-----Close price of selected order------------------------------------------
        static double OrderClosePrice();

        //-----Currency of selected order---------------------------------------------
        static const char * OrderSymbol();

        //-----Get stop loss in points------------------------------------------------
        static int GetStopLossPoints(int OrderHandle);

        //-----Get take profit points-------------------------------------------------
        static int GetTakeProfitPoints(int OrderHandle);

        //-----Set stop loss in points------------------------------------------------
        static void SetStopLossPoints(int OrderHandle, int NewStopLoss);

        //-----Set take profit in points----------------------------------------------
        static void SetTakeProfitPoints(int OrderHandle, int NewTakeProfit);

        //-----Get account balance----------------------------------------------------
        static double AccountBalance();

        //-----Get account equity-----------------------------------------------------
        static double AccountEquity();

        //-----Get account margin-----------------------------------------------------
        static double AccountMargin();

        //-----Get account free margin------------------------------------------------
        static double AccountFreeMargin();

        //-----Get account leverage---------------------------------------------------
        static int AccountLeverage();

        //-----Get account profit-----------------------------------------------------
        static double AccountProfit();

        //-----Breakpoint-------------------------------------------------------------
        static void Breakpoint(int number, const char * text);


        //-----Create indicator and obtaind id----------------------------------------
        static int CreateIndicator(const char* Symbol, int TimeFrame, const char* IndicatorName, const char* parameters);

        //-----Get indicator value----------------------------------------------------
        static double GetIndicatorValue(int IndicatorHandle, int index, int BufferIndex);

        //-----Get order MagicNumber--------------------------------------------------
        static int OrderMagicNumber();

        //-----Get order comment------------------------------------------------------
        static const char * OrderComment();

        //-----Order swap-------------------------------------------------------------
        static double OrderSwap();

        //-----Pause------------------------------------------------------------------
        static void Pause(const char * text);

        //-----Resume-----------------------------------------------------------------
        static void Resume();

        //-----Send instant order with selected price---------------------------------
        static bool _SendInstantOrder(const char * Symbol, TInstantOrderType OperationType, double price,
            double LotSize, double StopLoss, double TakeProfit, const char * Comment, int MagicNumber, int& OrderHandle);

        //-----Close order with requested price---------------------------------------
        static bool _CloseOrder(int OrderHandle, double price);

        //-----Create object----------------------------------------------------------
        static bool ObjectCreate(const char * name, TObjectType ObjType, int window,
            TDateTime time1, double price1, TDateTime time2, double price2,
            TDateTime time3, double price3);

        //-----Delete object by name--------------------------------------------------
        static void ObjectDelete(const char * name);

        //-----Check if object already exists-----------------------------------------
        static bool ObjectExists(const char * name);

        //-----Get object type--------------------------------------------------------
        static TObjectType ObjectType(const char * name);

        //-----Set object property----------------------------------------------------
        static bool ObjectSet(const char * name, int index, double value);

        //-----Get object property----------------------------------------------------
        static double ObjectGet(const char * name, int index);

        //-----Delete all objects-----------------------------------------------------
        static void ObjectsDeleteAll(int window, TObjectType ObjType);

        //-----Get interface version--------------------------------------------------
        static void GetInterfaceVersion(int& MajorValue, int& MinorValue);

        //-----Set text---------------------------------------------------------------
        static bool ObjectSetText(const char * name, const char * text, int FontSize, const char * FontName, TColor Color);

        //-----Get text---------------------------------------------------------------
        static const char * ObjectGetText(const char * name);

        //-----Get current time-------------------------------------------------------
        static TDateTime  TimeCurrent();

        //-----Set indicator's buffer style-------------------------------------------
        static void SetIndicatorBuffStyle(int IndicatorHandle, int BuffIndex, TPenStyle _style,
            int width, TColor color);

        //-----Get bar shift by its time----------------------------------------------
        static int iBarShift(const char * Symbol, int TimeFrame, TDateTime time, bool Exact);

        //-----Get highest value in array---------------------------------------------
        static int iHighest(const char * Symbol, int TimeFrame, int _type, int count, int index);

        //-----Get lowest value in array----------------------------------------------
        static int iLowest(const char * Symbol, int TimeFrame, int _type, int count, int index);

        //-----Close part of position-------------------------------------------------
        static bool CloseOrderPartial(int OrderHandle, double LotSize);
};


