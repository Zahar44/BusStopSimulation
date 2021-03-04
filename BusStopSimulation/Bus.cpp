#include "Bus.h"
#include <stdlib.h>
#include <iostream>

Bus::Bus(const Arr<int>& _route, size_t _index)
{
	seats.~Arr();
	id = ++idCnt;
	stopTime = 0;
	currentStation = 0;
	route = _route;
	routeId = _index;
	isRevers = false;
	/*
	color = [](size_t value) -> size_t {
		while (value > 14)
		{
			value -= 15;
		}
		return value;
	}(routeId);*/
	srand(routeId);
	color = 1 + rand() % 14;
}
void Bus::setSeats()
{
	size_t size = rand() % BUS_MAX_SEATS;
	for (size_t i = 0; i < size; i++)
		Bus::seats.push_back(*(new Human()));
}
void Bus::addHuman(const Human& h)
{
	Bus::seats.push_back(h);
}
void Bus::goToNextStation()
{
	if (currentStation == 0) {
		currentStation = route[0]; return;
	}
	size_t i = 0;
	for (; i < route.size(); i++)
		if (route[i] == currentStation)
			break;
	if (!isRevers)
		currentStation = i < route.size() - 1 ? route[i + 1] : route[i - 1];
	else
		currentStation = i > 0 ? route[i - 1] : route[i + 1];
	if (currentStation == route[0])
		isRevers = false;
	else if (currentStation == route[route.size() - 1])
		isRevers = true;
}
void Bus::operator=(const Bus& b)
{
	this->id = b.id;
	idCnt--;
	this->seats = b.seats;
}

size_t Bus::idCnt = 0;

std::ostream& operator<<(std::ostream& os, const Bus& obj)
{
	os << "Bus #" << obj.routeId << std::endl
		<< "Humans { " << obj.seats.size() << " }";
	return os;
}


