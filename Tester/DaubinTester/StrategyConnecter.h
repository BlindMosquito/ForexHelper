#pragma once

#include <stdio.h>
#include <Windows.h>

#pragma warning (disable : 4996)

#define EXPORT extern "C" __declspec(dllexport)

#define PChar const char*
#define TDateTime double
#define TColor unsigned long
#define PCurrencyInfo TCurrencyInfo*
#define PInterfaceProcRec TInterfaceProcRec*


typedef unsigned short    Word;
typedef unsigned long     LongWord;

enum TPenStyle { psSolid, psDash, psDot, psDashDot, psDashDotDot, psClear, psInsideFrame };

#define clRed       RGB(0xFF,0,0) 
#define clGreen     RGB(0,0xFF,0) 
#define clBlue      RGB(0,0,0xFF) 
#define clYellow    RGB(0xFF,0xFF,0)

// timeframes
#define PERIOD_M1  1
#define PERIOD_M5  5
#define PERIOD_M15 15
#define PERIOD_H1  60
#define PERIOD_H4  60*4
#define PERIOD_D1  60*24
#define PERIOD_W1  60*24*7

// object properties constants
#define OBJPROP_TIME1              0
#define OBJPROP_PRICE1             1
#define OBJPROP_TIME2              2
#define OBJPROP_PRICE2             3
#define OBJPROP_TIME3              4
#define OBJPROP_PRICE3             5
#define OBJPROP_COLOR              6
#define OBJPROP_STYLE              7
#define OBJPROP_WIDTH              8
#define OBJPROP_ELLIPSE           11
#define OBJPROP_FIBOCLOSEDENDS    12
#define OBJPROP_FIBOSHOWPRICE     13
#define OBJPROP_FIBOENDWIDTH      14
#define OBJPROP_FIBOLEVELS        15
#define OBJPROP_FIBOLEVELN        16
#define OBJPROP_LEVELCOLOR        17
#define OBJPROP_LEVELSTYLE        18
#define OBJPROP_LEVELWIDTH        19
#define OBJPROP_LEVELVALUE        20
#define OBJPROP_FONTSIZE          21
#define OBJPROP_HALIGNMENT        22
#define OBJPROP_VALIGNMENT        23
#define OBJPROP_FONTNAME          24
#define OBJPROP_XDISTANCE         25
#define OBJPROP_YDISTANCE         26
#define OBJPROP_TEXT              27
#define OBJPROP_NAME              28
#define OBJPROP_SCREENCOORDS      29
#define OBJPROP_SCRHALIGNMENT     30
#define OBJPROP_SCRVALIGNMENT     31

// text alignment
#define tlTop             0
#define tlCenter          1
#define tlBottom          2

#define taLeftJustify     0
#define taRightJustify    1
#define taCenter          2

#define MODE_OPEN    0
#define MODE_LOW     1
#define MODE_HIGH    2
#define MODE_CLOSE   3
#define MODE_VOLUME  4
#define MODE_TIME    5



