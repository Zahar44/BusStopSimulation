#include "Human.h"

Human::Human()
	{
		id = ++idCnt;
		waitingTime = 0;
	}

size_t Human::getTime() const { return waitingTime; }

void Human::setBecomeChanse(size_t avrTime, DayTime dayTime)
{
	becomeChanse[(size_t)dayTime] = ((double)1 / (double)avrTime) * 100;
}

void Human::setBecomeChanse(size_t* _becomeChanse)
{
	for (size_t i = 0; i < (size_t)DayTime::end; i++)
		Human::setBecomeChanse(_becomeChanse[i], (DayTime)i);
}

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

