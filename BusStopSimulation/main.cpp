#include "Emulator.h"
#include "config.h"

#include <iostream>
#include <Windows.h>
#include <conio.h>

int main(int argc, char* argv[])
{
	srand(time(NULL));
	Settings settings;
	try
	{
		settings = config("..\\BusStopSimulation\\config.txt");
	}
	catch (const std::exception& ex)
	{
		std::cout << "Config file is not opened!\n"
			<< "Error: " << ex.what()
			<< "\nDefault settings will be set.\n";
		settings.clear();
		_getch();
	}


	Emulator emulate;
	emulate.addBusStation(*(new BusStation()));
	emulate.addBusStation(*(new BusStation()));
	emulate.addBusStation(*(new BusStation()));

	while (true)
	{
		std::cout << " ";
		system("cls");
		emulate();
		Sleep(1000);
	}
}

