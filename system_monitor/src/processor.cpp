#include <iostream>
#include "processor.h"
#include "linux_parser.h"

// Return the aggregate CPU utilization
float Processor::Utilization() { 
    long total_jiffies = LinuxParser::Jiffies();
    long active_jffies = LinuxParser::ActiveJiffies();
    return 1.0 * active_jffies / total_jiffies; 
}