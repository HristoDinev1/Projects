#include "Movie.h"
Movie::Movie(std::string title, double rating, unsigned length, unsigned room, Date releaseDate, Date screenDate, Time startTime, Time endTime) :
	title(title), rating(rating), length(length), room(room), releaseDate(releaseDate), screenDate(screenDate), startTime(startTime), endTime(endTime) {}

void Movie::setTitle(std::string title)
{
	this->title = title;
}
void Movie::setRating(double rating)
{
	this->rating = rating;
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

std::string Movie::getTitle() const
{
	return this->title;
}
double Movie::getRating() const
{
	return this->rating;
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