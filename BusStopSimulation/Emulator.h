#pragma once
#include"BusStation.h"

class Emulator
{
private:
	Arr<BusStation> busStations;
	Arr<Bus> buses;
	size_t avrWaitingTime;

	DayTime dayTime;
	size_t hour;

	void tryAddBus();
	void checkForLastStation();
	void setDayTime();

	std::string getDayPeriodInStr();
	double getRecomendedTime();
	void dayInfo();

	void inputs();
public:
	Emulator();
	Emulator(Arr<BusStation>& arr);
	void addBusStation(const BusStation& bs);

	void operator()();
};


