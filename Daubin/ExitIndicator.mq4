#include "ExitIndicator.mqh"

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Abstract class to determine when crossing the baseline
///////////////////////////////////////////////////////////////////////////////////////////////////////
ExitIndicator::ExitIndicator(const string txt,int time) : symbol(txt), period(time) { }        // Constructor
///////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////
// Relative Vigor Index for Close
///////////////////////////////////////////////////////////////////////////////////////////////////////
RviExit::RviExit(const string txt,int time) : green(0), red(0), greenTop(0), ExitIndicator(txt, time) { 
   SetLines();
   if(green > red) greenTop = true;
   else greenTop = false;
}

// Calculates if trade should close
bool RviExit::Calculate() {
   SetLines();                                                    // Set the line values for red and green
   bool tGreenTop = false;                                        // set temp value for bool
   if(green > red) tGreenTop = true;                              // If green is greater then red change bool
   if(greenTop == tGreenTop) return false;                        // If the values are the same then not ready to close yet
   greenTop = tGreenTop;                                          // Values are different so update greenTop
   return true;                                                   // Ready to close
   return false;
}


// Sets the green and red lines     
void RviExit::SetLines() {
   green = iRVI(symbol, period, 7, MODE_MAIN, 0);                // Set green value
   red = iRVI(symbol, period, 7, MODE_SIGNAL, 0);                // set red value
}

///////////////////////////////////////////////////////////////////////////////////////////////////////