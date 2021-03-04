#pragma once
#include "BusStation.h"
#include <map>

typedef std::map<int, std::pair<Arr<Bus>, size_t>> Route;

class EmulatorBase abstract
{
protected:
	int speed;
	int hour;
	Route routes;
	Arr<BusStation> busStations;
	EmulatorBase();
};
