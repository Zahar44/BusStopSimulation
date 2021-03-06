#pragma once
#include "Arr.h"
#include "Bus.h"
#include "stuff.h"

#define CHANSE_THAT_HUMAN_SEAT_TO_BUS 20
#define TIME_WITCH_BUS_WAIT_AT_STATION 5

class BusStation
{
private:
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	UINT16 color;

	size_t id;
	static size_t idCnt;

	Arr<int> busAtStation;
	Arr<Human> humans;

	double avrWaitingTime;

	size_t getBusesThatBeforeThisStation(Arr<Bus*>& buses);

	void setBuses(Arr<Bus*>& buses);
	void tryAddSubjects(DayTime dayTime);
	void tryMoveSubjects(Arr<Bus*>& buses, uint16_t busStationsAmount);

	void updateTime(Arr<Bus*>& buses);
	void clearScreen(Arr<Bus*>& buses);
	void info(Arr<Bus*>& buses);
public:
	BusStation();
	~BusStation();
	void emulate(Arr<Bus*>& buses, uint16_t busStationsAmount, DayTime dayTime);
	size_t getId() { return id; }
};


