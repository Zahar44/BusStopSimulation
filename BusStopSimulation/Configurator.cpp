#include "Configurator.h"
#include <algorithm>
#include <fstream>
#include <conio.h>

Configurator::Configurator() {}
Configurator::Configurator(const char* _PATH)
{
	PATH = _PATH;
	setConfig();
}
void Configurator::setPath(const char* _PATH)
{
	PATH = _PATH;
	setConfig();
}

bool Configurator::blank(std::string& line)
{
	if (line[0] == '/' && line[1] == '/')
		return true;
	if (line.empty())
		return true;
	if (line[0] == ' ')
		return true;
	return false;
}
void Configurator::toLower(Settings& s)
{
	std::for_each(s.begin(), s.end(), [&](VarValue& vv) {
		std::for_each(vv.first.begin(), vv.first.begin() + vv.first.length(),
			[&](char& c) -> void {
				c = tolower(c);
			});
		});
}

VarValue Configurator::getVarValue(std::string& _str)
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
Settings Configurator::getSettings()
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
	toLower(settings);
	return settings;
}

int Configurator::checkSign(std::string& str)
{
	if (str == "speed")
		return 1;
	if (str == "busstationamount")
		return 2;
	if (str == "hour")
		return 3;
	if (str == "humanchanse")
		return 4;
	if (str[0] == 'r' && str[1] == 'o' && str[2] == 'u' && str[3] == 't' && str[4] == 'e')
		return 5;
	return 0;
}
void Configurator::isConfigurate()
{
	if (speed < 0)
		throw std::exception("Wrong speed value");
	if (!busStations.size())
		throw std::exception("Wrong buses amount");
	if (!hour || hour == UINT32_MAX)
		throw std::exception("Wrong hour value");
	if (humanChanse[(size_t)DayTime::morning] == 0 ||
		humanChanse[(size_t)DayTime::evening] == 0 ||
		humanChanse[(size_t)DayTime::noonday] == 0 ||
		humanChanse[(size_t)DayTime::night] == 0)
		throw std::exception("Wrong human become time");
	if (!routes.size())
		throw std::exception("Wrong buses input");
}

void Configurator::setConfig()
{
	Settings conf = getSettings();
	Arr<std::string> values;
	for (size_t i = 0; i < conf.size(); i++)
	{
		switch (checkSign(conf[i].first))
		{
		case 1:
			speed = stoi(conf[i].second);
			break;
		case 2:
			for (size_t j = 0; j < stoi(conf[i].second); j++)
				busStations.push_back(*(new BusStation()));
			break;
		case 3:
			hour = stoi(conf[i].second);
			break;
		case 4:
			values = toValue(conf[i].second);
			for (size_t i = 0; i < (size_t)DayTime::end; i++)
				humanChanse[i] = stoi(values[i]);
			break;
		case 5:
			[&](size_t ii) {
				values = toValue(conf[ii].second);
				Arr<int> routeWay;
				std::string index;
				size_t interval = stoi(values[values.size() - 1]);
				for (size_t j = 5; j < conf[ii].first.length(); j++)
					index += conf[ii].first[j];
				size_t i = 0;
				for (; values[i] != "]"; i++)
					routeWay.push_back(stoi(values[i]));
				i++;
				for (size_t j = 0; j < stoi(values[i]); j++)
					if (routes.find(stoi(index)) == routes.end())
						routes.insert(
							std::pair<int, std::pair<Arr<Bus>, size_t>>(
								stoi(index),
								std::pair<Arr<Bus>, size_t>(*(new Bus(routeWay, stoi(index))), interval))
						);
					else
						routes[stoi(index)].first.push_back(*(new Bus(routeWay, stoi(index))));
				i++;
				for (size_t j = 0; j < routes[stoi(index)].first.size(); j++)
				{
					routes[stoi(index)].first[j].setStopTime(j * -stoi(values[i]));
				}
			}(i);
			break;
		default:
			break;
		}
		values.~Arr();
	}
	try
	{
		isConfigurate();
	}
	catch (const std::exception& ex)
	{
		std::cout << "Config file corrupted!\n"
			<< "Error: " << ex.what()
			<< "\nDefault settings will be set.\n";
		conf.clear();
		Configurator::Configurator();
		_getch();
	}
}


