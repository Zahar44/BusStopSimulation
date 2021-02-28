#pragma once
#include "EmulatorBase.h"
#include "Configurator.h"
#include <map>

class Emulator : public EmulatorBase
{
private:
	Arr<BusStation> busStations;
	Buses buses;
	size_t avrWaitingTime;

	DayTime dayTime;
	size_t hour;

	int speed;

	void tryAddBus();
	void checkForLastStation();
	void setDayTime();

	std::string getDayPeriodInStr();
	double getRecomendedTime();
	void dayInfo();
public:
	Emulator();
	Emulator(Configurator conf);
	void addBusStation(const BusStation& bs);

	void operator()();
};


