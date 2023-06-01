#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <iostream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Configuration
{
private:
    json parseJson(std::string path);
    json jsonFile;
public:
    Configuration(std::string path);
    ~Configuration();
    std::string modelPath;
    std::string metaDataPath;
    std::string classesPath;
    float minConfidenceScore;
};

#endif