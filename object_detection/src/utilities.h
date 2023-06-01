#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

std::vector<std::string> readFileIntoVector(std::string path)
{
    std::vector<std::string> v;
    std::ifstream ifs(path.c_str());
    std::string line;

    // Load in all the classes from the file
    while (std::getline(ifs, line))
    {   
        v.push_back(line);
    } 
    return v;
}

#endif