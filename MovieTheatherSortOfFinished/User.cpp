#include "User.h"
User::User(const MyString& name, const MyString& password) : name(name), password(password), balance(0), hasAdminRights(false) {}

User::User(const MyString& name, const MyString& password, bool hasAdminRights) : name(name), password(password), balance(1000), hasAdminRights(hasAdminRights) {}


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
		std::cout << "Movie has already passed" << std::endl;
		return;
	}
	if (movie.calculatePrice() > this->balance)
	{
		std::cout << "Not enough cash" << std::endl;
		return;
	}
	else
	{
		this->balance -= movie.calculatePrice();
		tickets.push_back(&movie);
		std::cout << "Ticket Bought"<<std::endl;
	}
}


void User::rate(double rating, Movie& movie)
{
	for (size_t i = 0; i < tickets.size(); i++)
	{
		if (tickets[i]->getTitle() == movie.getTitle())
		{
			movie.addRating(rating);
			std::cout << "Movie Rated" << std::endl;
			return;
		}
	}
	std::cout << "Cant rate a movie user hasnt watched";
}

bool User::isAdmin() const
{
	return hasAdminRights;
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

void User::serialize(std::ofstream& out) const {
	size_t nameLen = name.length();
	out.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
	out.write(name.c_str(), nameLen);

	size_t passLen = password.length();
	out.write(reinterpret_cast<const char*>(&passLen), sizeof(passLen));
	out.write(password.c_str(), passLen);

	out.write(reinterpret_cast<const char*>(&balance), sizeof(balance));

	size_t ticketCount = tickets.size();
	out.write(reinterpret_cast<const char*>(&ticketCount), sizeof(ticketCount));

	for (size_t i = 0; i < ticketCount; ++i) {
		int movieId = tickets[i]->getId();
		out.write(reinterpret_cast<const char*>(&movieId), sizeof(movieId));
	}
}


void User::deserialize(std::ifstream& in, Cinema& cinema) {
	size_t nameLen;
	in.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
	char* nameBuffer = new char[nameLen + 1];
	in.read(nameBuffer, nameLen);
	nameBuffer[nameLen] = '\0';
	name = MyString(nameBuffer);
	delete[] nameBuffer;

	size_t passLen;
	in.read(reinterpret_cast<char*>(&passLen), sizeof(passLen));
	char* passBuffer = new char[passLen + 1];
	in.read(passBuffer, passLen);
	passBuffer[passLen] = '\0';
	password = MyString(passBuffer);
	delete[] passBuffer;

	in.read(reinterpret_cast<char*>(&balance), sizeof(balance));

	size_t ticketCount;
	in.read(reinterpret_cast<char*>(&ticketCount), sizeof(ticketCount));

	tickets.clear();
	for (size_t i = 0; i < ticketCount; ++i) {
		int movieId;
		in.read(reinterpret_cast<char*>(&movieId), sizeof(movieId));

		const Movie* moviePtr = cinema.getMovie(movieId);
		if (moviePtr) {
			tickets.push_back(moviePtr);
		}
	}
}

