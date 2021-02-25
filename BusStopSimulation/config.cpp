#include "config.h"
#include <fstream>
#include <iostream>
#include <conio.h>

/*
	DONE

	TODO
	speed in msec
	bus station cnt
	buses routes
	buses in rout
	human avr ap
	...
	log file path
	excel file path
*/
bool blank(std::string& line)
{
	if (line[0] == '/' && line[1] == '/')
		return true;
	if (line.empty())
		return true;
	if (line[0] == ' ')
		return true;
	return false;
}
VarValue getVarValue(std::string& _str)
{
	VarValue res;
	bool first = true;
	
	for (size_t i = 0; i < _str.length(); i++)
	{
		if (_str[i] == ' ')
			continue;
		if (_str[i] == '=') {
			first = false; continue;
		}
		first ? res.first += _str[i] : res.second += _str[i];
	}
	if (res.first == "" || res.second == "")
		throw std::exception("Incorrect settings in config file");
	return res;
}

Settings config(const char* PATH)
{
	std::ifstream conf(PATH);
	Settings settings;

	if (!conf.is_open())
		throw std::exception("Incorrect path to config file");

	std::string line;

	while (!conf.eof())
	{
		std::getline(conf, line);
		if (blank(line))
			continue;
		settings.push_back(getVarValue(line));
	}
	
	conf.close();
	return settings;
}