#include "Bus.h"

std::ostream& operator<<(std::ostream& os, const Bus& obj)
{
	os << "Bus #" << obj.id << std::endl
		<< "Humans { " << obj.seats.size() << " }";
	return os;
}


