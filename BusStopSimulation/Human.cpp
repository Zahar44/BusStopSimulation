#include "Human.h"
class Human
{
private:
	static size_t becomeChanse[(size_t)DayTime::end];
	static size_t idCnt;
	size_t id;
	size_t waitingTime;
public:
	Human()
	{
		id = ++idCnt;
		waitingTime = 0;
	}

	size_t getTime() const { return waitingTime; }

	static void setBecomeChanse(size_t avrTime, DayTime dayTime)
	{
		becomeChanse[(size_t)dayTime] = ((double)1 / (double)avrTime) * 100;
	}
	static size_t getBecomeChanse(DayTime dayTime)
	{
		return becomeChanse[(size_t)dayTime];
	}

	void operator++(int)
	{
		this->waitingTime++;
	}
	void operator=(const Human& obj)
	{
		this->id = obj.id;
		idCnt--;
		this->waitingTime = obj.waitingTime;
	}
	friend std::ostream& operator<<(std::ostream& os, const Human& obj);
};
size_t Human::idCnt = 0;
size_t Human::becomeChanse[(size_t)DayTime::end] = {};
std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	os << obj.waitingTime;
	return os;
}