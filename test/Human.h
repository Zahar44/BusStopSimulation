#pragma once
#include "DayTime.h"
#include <iostream>

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

	static void setBecomeChanse(size_t avrTime, DayTime dayTime) {
		becomeChanse[(size_t)dayTime] = ((double)1 / (double)avrTime) * 100;
	}
	static size_t getBecomeChanse(DayTime dayTime) { return becomeChanse[(size_t)dayTime]; }

	void operator++(int);
	void operator=(const Human& obj);
	friend std::ostream& operator<<(std::ostream& os, const Human& obj);
};
std::ostream& operator<<(std::ostream& os, const Human& obj);
