#include "Emulator.h"
#include "stuff.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <math.h>

Emulator::Emulator() : EmulatorBase() {}
Emulator::Emulator(Configurator conf)
{
	speed = conf.getSpeed();
	hour  = conf.getHour();
	busStations = conf.getBusStation();
	buses = conf.getBuses();
	for (size_t i = 1; i <= buses.size(); i++)
		lastBusOnRoute[i] = 0;
	Human::setBecomeChanse(conf.getHumanChanse());
}

void Emulator::moveBus()
{
	for (size_t i = 0; i < buses.size(); i++)  //route
	{
		for (size_t j = lastBusOnRoute[i + 1]; j < buses[i + 1].first.size(); j++)  //bus on route
		{
			if (buses[i + 1].first[j].getStopTime() < TIME_WITCH_BUS_WAIT_AT_STATION)
				buses[i + 1].first[j].setStopTime(buses[i + 1].first[j].getStopTime() + 1);
			else {
				buses[i + 1].first[j].goToNextStation();
				buses[i + 1].first[j].setStopTime(0);
			}
		}
	}
		
}
void Emulator::provideBusStations()
{
	Arr<Bus*> tmp;
	for (size_t i = 0; i < busStations.size(); i++)
	{
		for (size_t j = 1; j <= buses.size(); j++)					//find all buses that must be at this station
			for (size_t c = 0; c < buses[j].first.size(); c++)
				if ((buses[j].first[c].getCurrentStation() - 1) == i)
					tmp.push_back(&buses[j].first[c]);

		busStations[i].emulate(tmp, dayTime);	//emulate station
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
