#include "MovieFactory.h"

Movie* MovieFactory::create(const MyString& genre, const MyString& title, unsigned length, unsigned room, Date releaseDate, Date screenDate, Time startTime, Time endTime, uint8_t priceModifier)
{
	if (genre == "Action" || genre == "action" || genre == "ACTION")
	{
		return new ActionMovie(title, length, room, releaseDate, screenDate, startTime, endTime, priceModifier);
	}
	if (genre == "Drama" || genre == "drama" || genre == "DRAMA")
	{
		return new DramaMovie(title, length, room, releaseDate, screenDate, startTime, endTime, priceModifier);
	}
	if (genre == "Documentary" || genre == "documentary" || genre == "DOCUMENTARY")
	{
		return new DocumentaryMovie(title, length, room, releaseDate, screenDate, startTime, endTime, priceModifier);
	}
}

Movie* MovieFactory::create(Genre genre)
{
	if (genre == Genre::Action) return new ActionMovie();
	if (genre == Genre::Drama) return new DramaMovie();
	if (genre == Genre::Documentary) return new DocumentaryMovie();
}