#include "Emulator.h"
class Emulator
{
private:
	Arr<BusStation> busStations;
	Arr<Bus> buses;
	size_t avrWaitingTime;

	DayTime dayTime;
	size_t hour;

	void tryAddBus()
	{
		size_t chanse = rand() % 100;
		if (chanse < Bus::getBecomeChanse(dayTime))
			buses.push_back(*(new Bus()));
	}
	void checkForLastStation()
	{
		for (size_t i = 0; i < buses.size(); i++)
			if (buses[i].getCurrentStation() == busStations.size() + 1)
				buses.erase(i);
	}
	void setDayTime()
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

	std::string getDayPeriodInStr()
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
	double getRecomendedTime()
	{
		double timeBetweenBuses = (double)1 / (double)Bus::getBecomeChanse(dayTime) * 100;
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
	void dayInfo()
	{
		gotoxy(0, 0);
		for (size_t i = 0; i < 3; i++)
			std::cout << "                                                           ";
		gotoxy(0, 0);
		std::cout << "Current day period is: " << getDayPeriodInStr() << ", hour: " << hour << std::endl
			<< "Bus appearance chanse: " << Bus::getBecomeChanse(dayTime) << ", Human appearance chanse: " << Human::getBecomeChanse(dayTime) << std::endl
			<< "Recomended time between buses: " << getRecomendedTime();
	}

	void inputs()
	{
		size_t c;
		std::cout << "Average time between appearances for bus:" << '\n';
		std::cout << "Morning: ";
		std::cin >> c;
		Bus::setBecomeChanse(c, DayTime::morning);
		std::cout << "Noonday: ";
		std::cin >> c;
		Bus::setBecomeChanse(c, DayTime::noonday);
		std::cout << "Evening: ";
		std::cin >> c;
		Bus::setBecomeChanse(c, DayTime::evening);
		std::cout << "Night: ";
		std::cin >> c;
		Bus::setBecomeChanse(c, DayTime::night);

		std::cout << "Average time between appearances for human:" << '\n';
		std::cout << "Morning: ";
		std::cin >> c;
		Human::setBecomeChanse(c, DayTime::morning);
		std::cout << "Noonday: ";
		std::cin >> c;
		Human::setBecomeChanse(c, DayTime::noonday);
		std::cout << "Evening: ";
		std::cin >> c;
		Human::setBecomeChanse(c, DayTime::evening);
		std::cout << "Night: ";
		std::cin >> c;
		Human::setBecomeChanse(c, DayTime::night);
	}
public:
	Emulator() : avrWaitingTime(0), hour(1)
	{
		setDayTime();
		Bus::setBecomeChanse(10, DayTime::morning);
		Bus::setBecomeChanse(15, DayTime::noonday);
		Bus::setBecomeChanse(20, DayTime::evening);
		Bus::setBecomeChanse(25, DayTime::night);

		Human::setBecomeChanse(5, DayTime::morning);
		Human::setBecomeChanse(7, DayTime::noonday);
		Human::setBecomeChanse(10, DayTime::evening);
		Human::setBecomeChanse(15, DayTime::night);
	}
	Emulator(Arr<BusStation>& arr) : Emulator()
	{
		busStations = arr;
	}
	void addBusStation(const BusStation& bs)
	{
		busStations.push_back(bs);
	}

	void operator()()
	{
		setDayTime();
		dayInfo();
		tryAddBus();
		for (size_t i = 0; i < busStations.size(); i++)
			busStations[i].emulate(buses, dayTime);
		checkForLastStation();
		if (++hour == 25)
			hour = 1;
	}
};
