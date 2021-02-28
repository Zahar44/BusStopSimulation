#pragma once
#include "Arr.h"
#include "Human.h"

#define BUS_MAX_SEATS 30

class Bus
{
private:
	Arr<Human> seats;

	size_t stopTime;
	int currentStation;

	Arr<int> route;

	static size_t idCnt;
	size_t id;

	void setSeats();
public:
	Bus(const Arr<int>& _route);
	Arr<Human>& human() { return seats; }
	void addHuman(const Human& h);

	size_t getFreeSeats() { return BUS_MAX_SEATS - seats.size(); }
	size_t getStopTime() { return stopTime; }
	void setStopTime(size_t newTime) { stopTime = newTime; }

	int getCurrentStation() { return currentStation; }
	void setCurrentStation(int newValue) { this->currentStation = newValue; }

	Arr<int>& getRoute() { return route; }
	void setRoute(const Arr<int>& _route) {
		route = _route;
	}

	bool operator==(size_t val) { return currentStation == val; }
	void operator++(int) { this->stopTime++; }
	void operator=(const Bus& b);
	friend std::ostream& operator<<(std::ostream& os, const Bus& obj);
};
std::ostream& operator<<(std::ostream& os, const Bus& obj);
