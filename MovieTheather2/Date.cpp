#include "Date.h"

Date::Date(unsigned day, unsigned month, unsigned year) : day(day), month(month), year(year) {};

void Date::setDate(unsigned day, unsigned month, unsigned year)
{
	this->day = day;
	this->month = month;
	this->year = year;
};

unsigned Date::getDay() const
{
	return this->day;
}

unsigned Date::getMonth() const
{
	return this->month;
}

unsigned Date::getYear() const
{
	return this->year;
}