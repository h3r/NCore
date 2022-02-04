#pragma once
#include <nlohmann/json.hpp>
using json = nlohmann::json;


//Some extension----------------------------------------------------------------------------------
json LoadJson(const std::string& filename);
json Merge(const json& a, const json& b);
void GenerateDefaultAssets();
