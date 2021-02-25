#include "Emulator.h"

#include <iostream>
#include <Windows.h>

int main()
{
	srand(time(NULL));

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
