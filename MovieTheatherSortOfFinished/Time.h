#pragma once
class Time
{
public:
	Time() = default;
	Time(unsigned hour, unsigned minute);

	void SetTime(unsigned hour, unsigned minute);
	unsigned getHour() const;
	unsigned getMinute() const;
private:
	unsigned hour, minute;
};

