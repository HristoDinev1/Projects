#include "Movie.h"
Movie::Movie(const MyString& title, unsigned length, unsigned room, Date releaseDate, Date screenDate, Time startTime, Time endTime) :
	title(title), length(length), room(room), releaseDate(releaseDate), screenDate(screenDate), startTime(startTime), endTime(endTime) {}

void Movie::print() const
{
	std::cout << this->title << std::endl;
	std::cout << this->screenDate.getDay() << "." << this->screenDate.getMonth()<<std::endl;
	std::cout << this->startTime.getHour() << ":" << this->startTime.getMinute() << std::endl;
}

void Movie::addRating(double newRating) {
	if (newRating < 1.0 || newRating > 5.0)
		throw std::invalid_argument("Rating must be between 1 and 5");

	totalRating += newRating;
	++ratingCount;
}

bool Movie::hasPassed() const {
	constexpr int TM_YEAR_OFFSET = 1900;   
	constexpr int TM_MONTH_OFFSET = 1;    

	std::tm movieTime = {};
	movieTime.tm_year = static_cast<int>(screenDate.getYear()) - TM_YEAR_OFFSET;
	movieTime.tm_mon = static_cast<int>(screenDate.getMonth()) - TM_MONTH_OFFSET;
	movieTime.tm_mday = static_cast<int>(screenDate.getDay());
	movieTime.tm_hour = static_cast<int>(endTime.getHour());
	movieTime.tm_min = static_cast<int>(endTime.getMinute());
	movieTime.tm_sec = 0;

	std::time_t movieEndEpoch = std::mktime(&movieTime);
	std::time_t now = std::time(nullptr);

	return movieEndEpoch < now;
}

void Movie::setTitle(const MyString& title)
{
	this->title = title;
}

void Movie::setRoom(unsigned room)
{
	this->room = room;
}
void Movie::setReleaseDate(Date releaseDate)
{
	this->releaseDate = releaseDate;
}
void Movie::setScreenDate(Date screenDate)
{
	this->screenDate = screenDate;
}
void Movie::setStartTime(Time startTime)
{
	this->startTime = startTime;
}
void Movie::setEndTime(Time endTime)
{
	this->endTime = endTime;
}
void Movie::setLength(unsigned length)
{
	this->length = length;
}


MyString Movie::getTitle() const
{
	return this->title;
}
double Movie::getRating() const
{
	return this->totalRating/ratingCount;
}
unsigned Movie::getRoom() const
{
	return this->room;
}
Date Movie::getScreenDate() const
{
	return this->screenDate;
}
Date Movie::getReleaseDate() const
{
	return this->releaseDate;
}
Time Movie::getEndTime() const
{ 
	return this->endTime;
} 
Time Movie::getStartTime() const
{
	return this->startTime;
}
unsigned Movie::getLength() const
{
	return this->length;
}

Movie::Genre Movie::getGenre() const
{
	return this->genre;
}