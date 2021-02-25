#pragma once
#ifndef BUS_H
#define BUS_H

#include "Arr.h"
#include "Human.h"

#define BUS_MAX_SEATS 30

class Bus
{
public:
	int id = 2;
	Arr<Human> seats;
	friend std::ostream& operator<<(std::ostream& os, const Bus& obj);
};
std::ostream& operator<<(std::ostream& os, const Bus& obj);

#endif // !BUS_H

