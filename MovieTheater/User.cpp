#include "User.h"
User::User(const MyString& name, const MyString& password) : name(name), password(password), balance(0) {}

bool User::validateLoginData(const MyString& name, const MyString& password)
{
	if (this->name == name && this->password == password)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void User::buyTicket(const Movie& movie)
{
	if (movie.hasPassed())
	{
		std::cout << "Movie has already passed";
		return;
	}
	if (movie.calculatePrice() > this->balance)
	{
		std::cout << "Not enough cash";
		return;
	}
	else
	{
		this->balance -= movie.calculatePrice();
		tickets.push_back(&movie);
	}
}


void User::rate(double rating, Movie& movie)
{
	for (size_t i = 0; i < tickets.size(); i++)
	{
		if (tickets[i]->getTitle() == movie.getTitle())
		{
			movie.addRating(rating);
			return;
		}
	}
	std::cout << "Cant rate a movie user hasnt watched";
}

MyString User::getName() const
{
	return name;
}

void User::printTickets() const
{
	for (size_t i = 0; i < tickets.size(); i++)
	{
		if (!tickets[i]->hasPassed())
		{
			tickets[i]->print();
		}
	}
}
void User::printWatchedMovies() const
{
	for (size_t i = 0; i < tickets.size(); i++)
	{
		if (tickets[i]->hasPassed())
		{
			std::cout << tickets[i]->getTitle()<<" ";
		}
	}
}