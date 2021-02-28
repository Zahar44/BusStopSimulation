#include "Bus.h"
#include <stdlib.h>
#include <iostream>

Bus::Bus(const Arr<int>& _route)
{
	setSeats();
	id = ++idCnt;
	stopTime = 0;
	currentStation = 1;
	route = _route;
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
void Bus::operator=(const Bus& b)
{
	this->id = b.id;
	idCnt--;
	this->seats = b.seats;
}

size_t Bus::idCnt = 0;

std::ostream& operator<<(std::ostream& os, const Bus& obj)
{
	os << "Bus #" << obj.id << std::endl
		<< "Humans { " << obj.seats.size() << " }";
	return os;
}


