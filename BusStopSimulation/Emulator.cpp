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
	Human::setBecomeChanse(conf.getHumanChanse());
}

void Emulator::tryAddBus()
{

}
void Emulator::checkForLastStation()
{
	for (size_t i = 0; i < buses.size(); i++)
		if (buses[1].first[i].getCurrentStation() == busStations.size() + 1)
			buses.erase(i);
}
void Emulator::setDayTime()
{
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
	tryAddBus();
	for (size_t i = 0; i < busStations.size(); i++)
		busStations[i].emulate(buses[1].first, dayTime);
	checkForLastStation();
	if (++hour == 25)
		hour = 1;
	Sleep(speed);
	std::cout << " ";
	system("cls");
}
