#include "DramaMovie.h"

DramaMovie::DramaMovie(const MyString& title, unsigned length, unsigned room, Date releaseDate, Date screenDate, Time startTime, Time endTime, bool hasComedyElements) : Movie(title, length, room, releaseDate, screenDate, startTime, endTime), hasComedyElements(hasComedyElements)
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

Movie* DramaMovie::clone() const
{
	return new DramaMovie(*this);
}

bool DramaMovie::getHasComedyElements() const
{
	return this->hasComedyElements;
}
void DramaMovie::setHasComedyElements(bool hasComedyElements) 
{
	this->hasComedyElements = hasComedyElements;
}