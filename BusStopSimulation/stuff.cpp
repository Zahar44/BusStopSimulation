#include "stuff.h"

void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}
Arr<std::string> toValue(std::string& str)
{
	Arr<std::string> res;
	std::string num;
	for (size_t i = str.find_first_of('[') + 1; i <= str.find_first_of(']'); i++)
	{
		if (str[i] == ',' || i == str.find_first_of(']')) {
			res.push_back(num); num.clear(); continue;
		}
		num += str[i];
	}
	for (size_t i = str.find_first_of(']'); i <= str.find_first_of('}') && i < str.length(); i++)
	{
		if (str[i] == ',' || i == str.find_first_of('}')) {
			res.push_back(num); num.clear(); continue;
		}
		num += str[i];
	}
			
	return res;
}
