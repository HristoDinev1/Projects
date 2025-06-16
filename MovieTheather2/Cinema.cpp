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

void Cinema::serialize(std::ofstream& out) const
{
	size_t hallCount = this->halls.size();
	out.write(reinterpret_cast<const char*>(&hallCount), sizeof(hallCount));

	for (size_t i = 0; i < hallCount; ++i)
	{
		this->halls[i].serialize(out);
	}

	size_t movieCount = this->catalogue.size();
	out.write(reinterpret_cast<const char*>(&movieCount), sizeof(movieCount));

	for (size_t i = 0; i < movieCount; ++i)
	{
		Genre genre = this->catalogue[i]->getGenre();
		out.write(reinterpret_cast<const char*>(&genre), sizeof(genre));

		this->catalogue[i]->serialize(out);
	}
}


void Cinema::deserialize(std::ifstream& in) 
{
	size_t hallCount = 0;
	in.read(reinterpret_cast<char*>(&hallCount), sizeof(hallCount));

	for (size_t i = 0; i < hallCount; ++i)
	{
		CinemaHall hall(0, 0);
		hall.deserialize(in);
		halls.push_back(hall);
	}

	size_t movieCount = 0;
	in.read(reinterpret_cast<char*>(&movieCount), sizeof(movieCount));

	for (size_t i = 0; i < movieCount; ++i)
	{
		Genre genre;
		in.read(reinterpret_cast<char*>(&genre), sizeof(genre));
		Movie* temp = MovieFactory::create(genre);

		temp->deserialize(in);
		catalogue.push_back(temp);
	}
}
