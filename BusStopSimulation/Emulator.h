#pragma once
#include "EmulatorBase.h"
#include "Configurator.h"
#include <map>

class Emulator : public EmulatorBase
{
private:
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	Arr<BusStation> busStations;
	Route routes;
	std::map<size_t, size_t> lastBusOnRoute;
	size_t avrWaitingTime;

	DayTime dayTime;
	size_t hour;

	int speed;

	void moveBus();
	void provideBusStations();
	void setDayTime();
	void nextTick();

	std::string getDayPeriodInStr();
	double getRecomendedTime();
	void dayInfo();
public:
	Emulator(Configurator conf);
	void addBusStation(const BusStation& bs);

	void operator()();
};


