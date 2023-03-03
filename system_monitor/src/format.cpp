#include <string>
#include <sstream>
#include <iomanip>

#include "format.h"

using std::string;

#define HOUR 3600
#define MINUTE 60

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) {
    int h = seconds/HOUR;
    seconds = seconds % HOUR;
    int m = seconds/MINUTE;
    seconds %= MINUTE;
    std::stringstream buffer;
    buffer << std::setw(2) << std::setfill('0') << h << ":" 
           << std::setw(2) << std::setfill('0') << m << ":" 
           << std::setw(2) << std::setfill('0') << seconds;
    return buffer.str();
}