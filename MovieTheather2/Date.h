#pragma once

class Date
{
public:
	Date() = default;
	Date(unsigned day,unsigned month,unsigned year);
	void setDate(unsigned day, unsigned month, unsigned year);
	unsigned getDay() const;
	unsigned getMonth() const;
	unsigned getYear() const;
private:
	unsigned day, month, year;
	
};

