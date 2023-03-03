#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <iostream>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// Return this process's ID
int Process::Pid() const { return id_; }

void Process::SetPid(int id){id_ = id;}

// Return this process's CPU utilization
float Process::CpuUtilization() { 
    vector<string> tokens = LinuxParser::CpuUtilization(Pid());
    long uptime, utime, stime, cutime, cstime, starttime, total_time, seconds;
    float cpu_usage;
    uptime = LinuxParser::UpTime();

    utime = std::stol(tokens[13]);
    stime = std::stol(tokens[14]);
    cutime = std::stol(tokens[15]);
    cstime = std::stol(tokens[16]);
    starttime = std::stol(tokens[21]);
    total_time = utime + stime + cutime + cstime;
    
    seconds = uptime - (starttime/ sysconf(_SC_CLK_TCK));
    cpu_usage = 100.0 * total_time / sysconf(_SC_CLK_TCK)/seconds; 
    return cpu_usage; 
}

// Return the command that generated this process
string Process::Command() { return LinuxParser::Command(Pid()); }

// Return this process's memory utilization
string Process::Ram() const { return LinuxParser::Ram(Pid()); }

// Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Pid()); }

// Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(Pid()); }


// Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const { 
    return std::stol(Ram()) > std::stol(a.Ram());
}