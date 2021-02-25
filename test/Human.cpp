#include "Human.h"

Human::Human()
{
	id = ++idCnt;
	waitingTime = 0;
}

size_t Human::getTime() const { return waitingTime; }

void Human::operator++(int)
{
	this->waitingTime++;
}
void Human::operator=(const Human& obj)
{
	this->id = obj.id;
	idCnt--;
	this->waitingTime = obj.waitingTime;
}

std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	os << obj.getTime();
	return os;
}

size_t Human::idCnt = 0;
size_t Human::becomeChanse[(size_t)DayTime::end] = {};

