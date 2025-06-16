#include "DocumentaryMovie.h"

double DocumentaryMovie::calculatePrice() const
{
	return this->BASE_PRICE + this->basedOnTrueEvents * this->TRUE_EVENT_MODIFIER;
}

DocumentaryMovie::DocumentaryMovie(const MyString& title, unsigned length, unsigned room, Date releaseDate, Date screenDate, Time startTime, Time endTime, bool basedOnTrueEvents) : Movie(title, length, room, releaseDate, screenDate, startTime, endTime), basedOnTrueEvents(basedOnTrueEvents) 
{
	this->genre = Genre::Documentary;
}

DocumentaryMovie::DocumentaryMovie()
{
	this->genre = Genre::Documentary;
}

Movie* DocumentaryMovie::clone() const
{
	return new DocumentaryMovie(*this);
}

void DocumentaryMovie::setBasedOnTrueEvents(bool basedOnTrueEvents)
{
	this->basedOnTrueEvents = basedOnTrueEvents;
}

bool DocumentaryMovie::getBasedOnTrueEvents() const
{
	return this->basedOnTrueEvents;
}

void DocumentaryMovie::serialize(std::ofstream& out) const
{
	Movie::serialize(out);
	out.write(reinterpret_cast<const char*>(&basedOnTrueEvents), sizeof(basedOnTrueEvents));
}


void DocumentaryMovie::deserialize(std::ifstream& in)
{
	Movie::deserialize(in);
	in.read(reinterpret_cast<char*>(&basedOnTrueEvents), sizeof(basedOnTrueEvents));
}
