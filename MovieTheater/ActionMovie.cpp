#include "ActionMovie.h"

ActionMovie::ActionMovie(std::string title, double rating, unsigned length, unsigned room, Date releaseDate, Date screenDate, Time startTime, Time endTime, uint8_t actionIntensity) : Movie(title, rating, length, room, releaseDate, screenDate, startTime, endTime)
{
	if (actionIntensity > 20) throw std::out_of_range("actionIntensity incorrect construction value");
	this->actionIntensity = actionIntensity;
	this->genre = Genre::Action;
}

ActionMovie::ActionMovie()
{
	this->genre = Genre::Action;
}

void ActionMovie::setActionIntensity(uint8_t actionIntensity)
{
	if (actionIntensity > 20) throw std::out_of_range("actionIntensity incorrect value");
	this->actionIntensity = actionIntensity;
}
uint8_t ActionMovie::getActionIntensity() const
{
	return this->actionIntensity;
}

double ActionMovie::calculatePrice() const
{
	return this->BASE_PRICE + this->actionIntensity * ACTION_MODIFIER;
}

