#include "DramaMovie.h"

DramaMovie::DramaMovie(std::string title, double rating, unsigned length, unsigned room, Date releaseDate, Date screenDate, Time startTime, Time endTime, bool hasComedyElements) : Movie(title, rating, length, room, releaseDate, screenDate, startTime, endTime), hasComedyElements(hasComedyElements)
{
	this->genre = Genre::Drama;
}

double DramaMovie::calculatePrice() const 
{
	return this->BASE_PRICE + hasComedyElements * this->COMEDY_MODIFIER;
}

DramaMovie::DramaMovie()
{
	this->genre = Genre::Drama;
}

bool DramaMovie::getHasComedyElements() const
{
	return this->hasComedyElements;
}
void DramaMovie::setHasComedyElements(bool hasComedyElements) 
{
	this->hasComedyElements = hasComedyElements;
}