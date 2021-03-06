﻿#include "Emulator.h"
#include "Configurator.h"

#include <iostream>
#include <conio.h>

//Version 1.11

int main(int argc, char* argv[])
{
	srand(time(NULL));
  
	Configurator conf;
	try
	{
		conf.setPath(argv[1]);
	}
	catch (const std::exception& ex)
	{
		std::cout << "Config file is not opened!\n"
			<< "Error: " << ex.what()
			<< "\nDefault settings will be set.\n";
		_getch();
		conf.setDefault();
	}
	
	Emulator emulate(conf);

	while (true)
	{
		emulate();
	}
}

