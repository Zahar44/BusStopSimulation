#include "BusStation.h"
#include <iostream>

BusStation::BusStation()
{
	id = ++idCnt;
	avrWaitingTime = 0;
}

size_t BusStation::getBusesThatBeforeThisStation(Arr<Bus>& buses)
{
	size_t res = 0;
	for (size_t i = 0; i < buses.size(); i++)
	{
		if (busAtStation[i] < id)
			res++;
	}
	return res;
}

void BusStation::setBuses(Arr<Bus>& buses)
	{
		for (size_t i = 0; i < buses.size(); i++)
		{
			if (busAtStation.size() <= i)
				busAtStation.push_back(buses[i].getCurrentStation());
			else
				busAtStation[i] = buses[i].getCurrentStation();
		}
	}
void BusStation::tryAddSubjects(DayTime dayTime)
	{
		size_t chanse = rand() % 100;
		if (chanse <= Human::getBecomeChanse(dayTime))
			humans.push_back(*(new Human()));
	}
void BusStation::tryMoveSubjects(Arr<Bus>& buses)
	{
		for (size_t i = 0; i < buses.size(); i++)
		{
			if (busAtStation[i] != id)
				continue;
			for (size_t j = 0; j < humans.size() && buses[i].getFreeSeats(); j++)
			{
				size_t chanse = rand() % 100;
				if (chanse < CHANSE_THAT_HUMAN_SEAT_TO_BUS)
				{
					buses[i].addHuman(humans[j]);
					humans.erase(j);
				}
			}
			for (size_t i = 0; i < buses.size(); i++)
			{
				if (buses[i].getStopTime() > TIME_WITCH_BUS_WAIT_AT_STATION)
				{
					buses[i].setCurrentStation(buses[i].getCurrentStation() + 1);
					buses[i].setStopTime(0);
				}
			}
		}
	}

void BusStation::updateTime(Arr<Bus>& buses)
	{
		double tmp = 0;
		for (size_t i = 0; i < humans.size(); i++)
		{
			humans[i]++;
			tmp += humans[i].getTime();
		}
		tmp = humans.size() ? tmp / humans.size() : tmp;
		avrWaitingTime = (avrWaitingTime + tmp) / 2;

		for (size_t i = 0; i < buses.size(); i++)
		{
			if (busAtStation[i] == id)
				buses[i]++;
		}
	}
void BusStation::clearScreen(Arr<Bus>& buses)
	{
		gotoxy(0, id * 4 + (getBusesThatBeforeThisStation(buses) * 2) - 1);
		size_t busesAtThisStation = 0;
		for (size_t i = 0; i < buses.size(); i++)
			if (busAtStation[i] == id)
				busesAtThisStation++;
		for (size_t i = 0; i <= 3 + busesAtThisStation * 2; i++)
			std::cout << "                                                             " << '\n';
		gotoxy(0, id * 4 + (getBusesThatBeforeThisStation(buses) * 2));
	}
void BusStation::info(Arr<Bus>& buses)
	{
		clearScreen(buses);
		std::cout << "Bus stop #" << id << std::endl;
		std::cout << "Avarage waiting time for bus: " << avrWaitingTime << std::endl;
		std::cout << "Humans { ";
		for (size_t i = 0; i < humans.size(); i++)
			std::cout << humans[i].getTime() << ", ";
		humans.size() ? std::cout << "\b\b }" << '\n' : std::cout << " }" << '\n';
		if (buses.size())
			for (size_t i = 0; i < buses.size(); i++)
				if (busAtStation[i] == id)
					std::cout << buses[i] << '\n';
				else
					continue;
	}
void BusStation::emulate(Arr<Bus>& buses, DayTime dayTime)
	{
		setBuses(buses);
		updateTime(buses);
		info(buses);
		tryAddSubjects(dayTime);
		tryMoveSubjects(buses);
	}

size_t BusStation::idCnt = 0;