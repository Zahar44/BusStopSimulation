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
	size_t i = 0;
	for (; _str[i] != '=' && i < _str.length(); i++)
		res.first += _str[i];
	for (i++; i < _str.length(); i++)
		res.second += _str[i];
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