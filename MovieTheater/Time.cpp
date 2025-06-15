#include "Time.h"


Time::Time(unsigned hour, unsigned minute) : hour(hour), minute(minute) {};

void Time::SetTime(unsigned hour, unsigned minute)
{
	this->hour = hour;
	this->minute = minute;
}

unsigned Time::getHour() const
{
	return this->hour;
}

unsigned Time::getMinute() const
{
	return this->minute;
}