#include <fstream>
#include "configuration.h"

Configuration::Configuration(std::string path)
{
    jsonFile = parseJson(path);
    modelPath = jsonFile["model_path"];
    metaDataPath = jsonFile["metadata_path"];
    classesPath = jsonFile["classes_path"];
    minConfidenceScore = jsonFile["min_confidence_score"];
}

Configuration::~Configuration()
{
}

json Configuration::parseJson(std::string path)
{
    std::ifstream f(path);
    json data = json::parse(f);
    return data;
}