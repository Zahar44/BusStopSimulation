#pragma once
#include "Arr.h"
#include "Human.h"
#include <Windows.h>

#define BUS_MAX_SEATS 30

class Bus
{
private:
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	UINT16 color;

	Arr<Human> seats;

	size_t stopTime;
	int currentStation;

	size_t routeId;
	Arr<int> route;
	bool isRevers;

	static size_t idCnt;
	size_t id;

	void setSeats();
public:
	Bus(const Arr<int>& _route, size_t _index);
	Arr<Human>& human() { return seats; }
	void addHuman(const Human& h);

	size_t getId()			{ return id; }
	size_t getFreeSeats()	{ return BUS_MAX_SEATS - seats.size(); }
	size_t getStopTime()	{ return stopTime; }
	size_t getRouteId()		{ return routeId; }
	int getCurrentStation() { return currentStation; }
	Arr<int>& getRoute()	{ return route; }

	void setStopTime(size_t newTime)	 { stopTime = newTime; }
	void setRouteId(size_t _routeId)	 { routeId = _routeId; }
	void setCurrentStation(int newValue) { currentStation = newValue; }
	void goToNextStation();

	void setRoute(const Arr<int>& _route) {
		route = _route;
	}
	UINT16 getColor() { return color; }
	bool operator==(size_t val) { return currentStation == val; }
	void operator++(int) { this->stopTime++; }
	void operator=(const Bus& b);
	friend std::ostream& operator<<(std::ostream& os, const Bus& obj);
};
std::ostream& operator<<(std::ostream& os, const Bus& obj);
