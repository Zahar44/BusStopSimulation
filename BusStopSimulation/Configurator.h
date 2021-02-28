#pragma once
#include "EmulatorBase.h"
#include <string>
#include <vector>

typedef std::pair<std::string, std::string> VarValue;
typedef std::vector<VarValue> Settings;

class Configurator : public EmulatorBase
{
private:
	const char* PATH;
	size_t humanChanse[(size_t)DayTime::end];

	bool blank(std::string& line);
	void toLower(Settings& s);
	
	VarValue getVarValue(std::string& _str);
	Settings getSettings();
	
	int checkSign(std::string& str); //only low chars
	void isConfigurate();

	void setConfig();
public:
	Configurator();
	Configurator(const char* _PATH);
	void setPath(const char* _PATH);

	int getSpeed()						{ return speed; }
	int getHour()						{ return hour; }
	size_t* getHumanChanse()			{ return humanChanse; }
	Buses& getBuses()					{ return buses; }
	Arr<BusStation>& getBusStation()	{ return busStations; }
};

