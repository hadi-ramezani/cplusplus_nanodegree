#include <iostream>
#include "processor.h"
#include "linux_parser.h"

// Return the aggregate CPU utilization
float Processor::Utilization() { 
    long total_jiffies = LinuxParser::Jiffies();
    long idle_jffies = LinuxParser::IdleJiffies();
    return 1.0 * (total_jiffies - idle_jffies) / total_jiffies; 
}