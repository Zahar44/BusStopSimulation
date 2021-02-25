#pragma once
#include "Human.h"
#define BUS_MAX_SEATS 30
class Bus
{
private:
	Arr<Human> seats;

	static size_t becomeChanse[(size_t)DayTime::end];

	size_t stopTime;
	int currentStation;

	static size_t idCnt;
	size_t id;

	void setSeats();
public:
	Bus();

	Arr<Human>& human();
	void addHuman(const Human& h);

	size_t getFreeSeats();
	size_t getStopTime();
	void setStopTime(size_t newTime);
	int getCurrentStation();
	void setCurrentStation(int newValue);

	static void setBecomeChanse(size_t avrTime, DayTime dayTime);
	static size_t getBecomeChanse(DayTime dayTime);

	bool operator==(size_t val);
	void operator++(int);
	void operator=(const Bus& b);
	friend std::ostream& operator<<(std::ostream& os, const Bus& obj);
};
size_t Bus::idCnt = 0;
size_t Bus::becomeChanse[(size_t)DayTime::end] = {};
std::ostream& operator<<(std::ostream& os, const Bus& obj);

