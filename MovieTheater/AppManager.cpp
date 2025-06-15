#include "AppManager.h"


void AppManager::initialize()
{
	this->commandParser = CommandParser::getsInstance();
	
}
void AppManager::run()
{
	MyString command;
	while (true)
	{
		std::cin >> command;
		if (command == "register")
		{
			Register();
		}
		else if (command == "login")
		{
			Login();
		}
		else if (command == "exit")
		{
			exit();
		}
		else if (command == "buy-ticket")
		{
			buyTicket();
		}
		else if (command == "list-movies")
		{
			listMovies();
		}
		else if (command == "rate-movie")
		{
			rateMovie();
		}
		//admin commands
		else if (command == "add-movie" )
		{
			addMovie();
		}
		else if (command == "open-haul" || command == "Open-Haul" || command == "open-hall" || command == "Open-hall")//hall?haul??
		{
			openHall();
		}
		else if (command == "remove-movie")
		{
			removeMovie();
		}
		else if (command == "close-haul" || command == "Close-Haul" || command == "close-hall" || command == "Close-hall")
		{
			closeHaul();
		}
		else if (command == "update-movie")
		{
			updateMovie();
		}
		else if (command == "update-movie-hall")
		{
			updateMovieHall();
		}
		else if (command == "list-users")
		{
			listUsers();
		}
		else if (command == "list-user-history")
		{
			listUserHistory();
		}	
		else if (command == "list-user-tickets")
		{
			listUserHistory();
		}
		else if (command == "remove-user")
		{
			removeUser();
		}
		else
		{
			std::cout << "unknown command"<<std::endl;
		}
		
	}
}
void AppManager::save()
{

}


void AppManager::updateMovieHall()
{
	size_t movieId;
	unsigned newHall;
	std::cin >> movieId >> newHall;
	cinema.getMovie(movieId)->setRoom(newHall);
}

void AppManager::Register()
{
	MyString name, password;
	std::cin >> name >> password; //  check for duplicates?

	this->userList.push_back(User(name, password));
}
void AppManager::Login()
{
	MyString name, password;
	std::cin >> name >> password;

	for (size_t i = 0; i < userList.size(); i++)
	{
		if (userList[i].validateLoginData(name, password))
		{
			this->currentUserId = i;
			return;
		}
	}
	std::cout << "Incorrect login data";
}
void AppManager::buyTicket()
{
	size_t movieId;
	std::cin >> movieId;
	userList[currentUserId].buyTicket(*(cinema.getMovie(movieId)));
}
void AppManager::listMovies()
{
	cinema.printMovies();
}
void AppManager::listTickets()
{
	userList[currentUserId].printTickets(); // print available tickets
}
void AppManager::rateMovie()
{
	double rating;
	size_t movieId;
	std::cin >>movieId>>rating;
	userList[currentUserId].rate(rating, *(cinema.getMovie(movieId)));
}
void AppManager::exit()
{
	save();
}

void AppManager::addMovie()
{
	MyString genre;
	std::cin >> genre;
	MyString title;
	unsigned length, room;
	unsigned releaseDay, releaseMonth, releaseYear;
	unsigned screenDay, screenMonth, screenYear;
	unsigned startHour, startMinute;
	unsigned endHour, endMinute;
	uint8_t priceModifier;

	std::cout << "Enter movie title: ";
	std::cin >> title;

	std::cout << "Enter movie length (minutes): ";
	std::cin >> length;

	std::cout << "Enter room number: ";
	std::cin >> room;

	std::cout << "Enter release date (day month year): ";
	std::cin >> releaseDay >> releaseMonth >> releaseYear;

	std::cout << "Enter screen date (day month year): ";
	std::cin >> screenDay >> screenMonth >> screenYear;

	std::cout << "Enter start time (hour minute): ";
	std::cin >> startHour >> startMinute;

	std::cout << "Enter end time (hour minute): ";
	std::cin >> endHour >> endMinute;

	std::cout << "Enter : "; // make it dependant on the genre
	std::cin >> priceModifier;

	cinema.addMovie(MovieFactory::create(genre, title, length, room, Date(releaseDay, releaseMonth, releaseYear), Date(screenDay, screenMonth, screenYear), Time(startHour, startMinute), Time(endHour, endMinute), priceModifier));

}
void AppManager::openHall()
{
	unsigned rows, cols;
	std::cin >> rows >> cols;
	cinema.addHall(rows, cols);
}
void AppManager::closeHaul()
{
	size_t hallId;
	std::cin >> hallId;
	cinema.removeHall(hallId);
}

void AppManager::removeMovie()
{
	size_t movieId;
	std::cin >> movieId;
	cinema.removeMovie(movieId);
}
void AppManager::updateMovie()
{
	size_t movieId;
	MyString newTitle;
	std::cin >> movieId>>newTitle;
	cinema.getMovie(movieId)->setTitle(newTitle);
}
void AppManager::listUserHistory()
{
	size_t userId;
	std::cin >> userId;
	userList[userId].printWatchedMovies();
}
void AppManager::listUserTickets()
{
	size_t userId;
	std::cin >> userId;
	userList[userId].printTickets();
}
void AppManager::listUsers()
{
	for (size_t i = 0; i < userList.size(); i++)
	{
		std::cout << userList[i].getName() << " ";
	}
}
void AppManager::removeUser()
{
	size_t userId;
	std::cin >> userId;
	std::swap(this->userList[userId], this->userList[this->userList.size() - 1]);
	this->userList.pop_back();
}
