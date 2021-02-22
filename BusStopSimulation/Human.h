#pragma once
#include <iostream>
#include "DayTime.h"
class Human
{
private:
	static size_t becomeChanse[(size_t)DayTime::end];
	static size_t idCnt;
	size_t id;
	size_t waitingTime;
public:
	Human();

	size_t getTime() const;

	static void setBecomeChanse(size_t avrTime, DayTime dayTime);
	static size_t getBecomeChanse(DayTime dayTime);

	void operator++(int);
	void operator=(const Human& obj);
	friend std::ostream& operator<<(std::ostream& os, const Human& obj);
};
size_t Human::idCnt = 0;
size_t Human::becomeChanse[(size_t)DayTime::end] = {};
std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	os << obj.waitingTime;
	return os;
}