#include "Emulator.h"
#include "stuff.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <math.h>
#include <algorithm>

Emulator::Emulator(Configurator conf)
{
	speed = conf.getSpeed();
	hour  = conf.getHour();
	busStations = conf.getBusStation();
	routes = conf.getRoutes();
	for (size_t i = 1; i <= routes.size(); i++)
		lastBusOnRoute[i] = 0;
	Human::setBecomeChanse(conf.getHumanChanse());
}

void Emulator::moveBus()
{
	std::for_each(routes.begin(), routes.end(), [&](std::pair<const int, std::pair<Arr<Bus>, size_t>>& el) //each route
		{
			for (size_t j = lastBusOnRoute[el.first]; j < el.second.first.size(); j++)  //bus on route
			{
				if (el.second.first[j].getStopTime() < TIME_WITCH_BUS_WAIT_AT_STATION)
					el.second.first[j].setStopTime(el.second.first[j].getStopTime() + 1);
				else {
					el.second.first[j].goToNextStation();
					el.second.first[j].setStopTime(0);
				}
			}
		});
}
void Emulator::provideBusStations()
{
	Arr<Bus*> tmp;
	for (size_t i = 0; i < busStations.size(); i++)
	{
		for (size_t j = 1; j <= routes.size(); j++)					//find all buses that must be at this station
			for (size_t c = 0; c < routes[j].first.size(); c++)
				if ((routes[j].first[c].getCurrentStation() - 1) == i)
					tmp.push_back(&routes[j].first[c]);

		busStations[i].emulate(tmp, busStations.size(), dayTime);	//emulate station
	}
}
void Emulator::setDayTime()
{
	if (++hour == 25)
		hour = 1;
	switch (hour)
	{
	case 6:
		dayTime = DayTime::morning;
		break;
	case 12:
		dayTime = DayTime::noonday;
		break;
	case 18:
		dayTime = DayTime::evening;
		break;
	case 24:
		dayTime = DayTime::night;
		break;
	default:
		break;
	}
}

void Emulator::nextTick()
{
	Sleep(speed);
	std::cout << " ";
	system("cls");
}

std::string Emulator::getDayPeriodInStr()
{
	switch (dayTime)
	{
	case DayTime::morning:
		return "morning";
		break;
	case DayTime::noonday:
		return "noonday";
		break;
	case DayTime::evening:
		return "evening";
		break;
	case DayTime::night:
		return "night";
		break;
	default:
		break;
	}
}
double Emulator::getRecomendedTime()
{
	double timeBetweenBuses = 10;//(double)1 / (double)Bus::getBecomeChanse(dayTime) * 100;
	double timeBetweenHumans = (double)1 / (double)Human::getBecomeChanse(dayTime) * 100;

	double humansForOneBus = timeBetweenBuses / timeBetweenHumans;
	double humansProbablyRemainAtStation = humansForOneBus * (100 - CHANSE_THAT_HUMAN_SEAT_TO_BUS) / 100;
	//10 -> 1 = 8
	//10 -> 2 = 6.4
	//10 -> 3 = 5.12
	//10 -> 4 = 4.1

	while (!(humansProbablyRemainAtStation < 5))
	{
		timeBetweenBuses--;
		humansForOneBus = timeBetweenBuses / timeBetweenHumans;
		humansProbablyRemainAtStation = humansForOneBus * (100 - CHANSE_THAT_HUMAN_SEAT_TO_BUS) / 100;
	}

	return timeBetweenBuses;
}
void Emulator::dayInfo()
{
	SetConsoleTextAttribute(hConsole, 15);
	gotoxy(0, 0);
	for (size_t i = 0; i < 3; i++)
		std::cout << "                                                           ";
	gotoxy(0, 0);
	std::cout << "Current day period is: " << getDayPeriodInStr() << ", hour: " << hour << std::endl
		<< "Human appearance chanse: " << Human::getBecomeChanse(dayTime) << std::endl
		<< "Recomended time between buses: " << getRecomendedTime();
}
void Emulator::addBusStation(const BusStation& bs)
{
	busStations.push_back(bs);
}

void Emulator::operator()()
{
	setDayTime();
	dayInfo();
	moveBus();
	provideBusStations();
	nextTick();
}
