#include "DocumentaryMovie.h"

double DocumentaryMovie::calculatePrice() const
{
	return this->BASE_PRICE + this->basedOnTrueEvents * this->TRUE_EVENT_MODIFIER;
}

DocumentaryMovie::DocumentaryMovie(std::string title, double rating, unsigned length, unsigned room, Date releaseDate, Date screenDate, Time startTime, Time endTime, bool basedOnTrueEvents) : Movie(title, rating, length, room, releaseDate, screenDate, startTime, endTime), basedOnTrueEvents(basedOnTrueEvents)
{
	this->genre = Genre::Documentary;
}

DocumentaryMovie::DocumentaryMovie()
{
	this->genre = Genre::Documentary;
}


void DocumentaryMovie::setBasedOnTrueEvents(bool basedOnTrueEvents)
{
	this->basedOnTrueEvents = basedOnTrueEvents;
}

bool DocumentaryMovie::getBasedOnTrueEvents() const
{
	return this->basedOnTrueEvents;
}