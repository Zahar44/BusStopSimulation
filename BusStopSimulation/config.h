#pragma once
#include <string>
#include <vector>

typedef std::pair<std::string, std::string> VarValue;
typedef std::vector<VarValue> Settings;

bool blank(std::string& line);
VarValue getVarValue(std::string& _str);
Settings config(const char* PATH);
