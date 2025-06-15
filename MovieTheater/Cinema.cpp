#include "Cinema.h"

Movie* Cinema::getMovie(size_t movieId)
{
	return &(*catalogue[movieId]);
}

void Cinema::addHall(unsigned rows, unsigned cols)
{
	this->halls.push_back(CinemaHall(rows, cols));
}
void Cinema::removeHall(unsigned hallId)
{
	std::swap(this->halls[hallId], this->halls[this->halls.size() - 1]);
	this->halls.pop_back();
}
void Cinema::printHall(unsigned hallId) const
{
	this->halls[hallId].printSeats();
}

void Cinema::addMovie(Movie* movie) // genre
{
	this->catalogue.push_back(movie);
}
void Cinema::removeMovie(size_t movieId)
{
	std::swap(this->catalogue[movieId], this->catalogue[this->catalogue.size() - 1]);
	this->catalogue.pop_back();
}


void Cinema::printMovies() const
{
	for (size_t i = 0; i < catalogue.size(); i++)
	{
		if (!catalogue[i]->hasPassed())
		{
			catalogue[i]->print();
		}
	}
}
void Cinema::printPassedMovies() const
{
	for (size_t i = 0; i < catalogue.size(); i++)
	{
		if (catalogue[i]->hasPassed())
		{
			std::cout << catalogue[i]->getTitle() << " ";
		}
	}
}
