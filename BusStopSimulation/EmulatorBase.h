#pragma once
#include "BusStation.h"
#include <map>

typedef std::map<int, std::pair<Arr<Bus>, size_t>> Buses;

class EmulatorBase abstract
{
protected:
	int speed;
	int hour;
	Buses buses;
	Arr<BusStation> busStations;
	EmulatorBase();
};
