#include "AppManager.h"


AppManager& AppManager::getInstance()
{
	static AppManager instance;
	return instance;
}


void AppManager::parseCommands()
{
	MyString command;
	try
	{
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
				save();
				break;
			}
			else if (command == "list-movies")
			{
				listMovies();
			}
			else if (hasLoggedIn)
			{
				if (command == "buy-ticket")
				{
					buyTicket();
				}
				else if (command == "rate-movie")
				{
					rateMovie();
				}
				if (userList[currentUserId].isAdmin())
				{
					if (command == "add-movie")
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
						std::cout << "Unknown Command" << std::endl;
					}
				}
			}
			else
			{
				std::cout << "Unknown Command" << std::endl;
			}
		}
	}
	catch(std::exception& e)
	{
		std::cout << e.what()<<std::endl;
	}
}

void AppManager::initialize()
{
	this->userList.push_back(User("admin", "pass", true));

	std::ifstream MovieFile(CINEMA_DATA_FILE.c_str(), std::ios::binary);
	if (!MovieFile.is_open())
	{
		throw std::runtime_error("Movie Config file not found");
	}
	this->cinema.deserialize(MovieFile);
	MovieFile.close();

	std::ifstream UserFile(USER_DATA_FILE.c_str(), std::ios::binary);
	if (!UserFile.is_open())
	{
		throw std::runtime_error("User Config file not found");
	}
	size_t userListSize;
	UserFile.read(reinterpret_cast<char*>(&userListSize), sizeof(userListSize));
	for (size_t i = 0; i < userListSize; i++)
	{
		User temp("", "");
		temp.deserialize(UserFile, this->cinema);
		userList.push_back(temp);
	}
	UserFile.close();
	
}
void AppManager::run()
{
	initialize();
	try
	{
		parseCommands();
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
}
void AppManager::save()
{
	std::ofstream MovieFile(CINEMA_DATA_FILE.c_str(), std::ios::binary);
	if (!MovieFile.is_open())
	{
		throw std::runtime_error("Cinema data file not found");
	}
	this->cinema.serialize(MovieFile);
	MovieFile.close();

	std::ofstream UserFile(USER_DATA_FILE.c_str(), std::ios::binary);
	if (!UserFile.is_open())
	{
		throw std::runtime_error("User Data file not found");
	}
	size_t userListSize = userList.size();
	UserFile.write(reinterpret_cast<const char*>(&userListSize), sizeof(userListSize));
	for (size_t i = 0; i < userList.size(); i++)
	{
		userList[i].serialize(UserFile);
	}
	UserFile.close();
}


void AppManager::updateMovieHall()
{
	size_t movieId;
	unsigned newHall;
	std::cin >> movieId >> newHall;
	cinema.getMovie(movieId)->setRoom(newHall);
	std::cout << "Movie hall updated" <<std::endl;
}


void AppManager::Register()
{
	MyString name, password;
	std::cin >> name >> password; //  check for duplicates?

	this->userList.push_back(User(name, password));
	std::cout << "User: "<<name <<" registered" << std::endl;
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
			hasLoggedIn = true;
			std::cout << "logged in as "<< userList[i].getName() << std::endl;
			return;
		}
	}
	std::cout << "Incorrect login data"<<std::endl;
}
void AppManager::buyTicket()
{
	size_t movieId;
	std::cin >> movieId;
	userList[currentUserId].buyTicket(*(cinema.getMovie(movieId)));
}
void AppManager::listMovies()
{
	std::cout << "Listing Movies" << std::endl;
	cinema.printMovies();
}
void AppManager::listTickets()
{
	std::cout << "Current tickets: " << std::endl;
	userList[currentUserId].printTickets(); // print available tickets

}
void AppManager::rateMovie()
{
	double rating;
	size_t movieId;
	std::cin >>movieId>>rating;
	userList[currentUserId].rate(rating, *(cinema.getMovie(movieId)));
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
	std::cout << "Hall opened" << std::endl;
}
void AppManager::closeHaul()
{
	size_t hallId;
	std::cin >> hallId;
	cinema.removeHall(hallId);
	std::cout << "Hall removed" << std::endl;
}

void AppManager::removeMovie()
{
	size_t movieId;
	std::cin >> movieId;
	cinema.removeMovie(movieId);
	std::cout << "Movie opened" << std::endl;
}
void AppManager::updateMovie()
{
	size_t movieId;
	MyString newTitle;
	std::cin >> movieId>>newTitle;
	cinema.getMovie(movieId)->setTitle(newTitle);
	std::cout << "Movie updated" << std::endl;
}
void AppManager::listUserHistory()
{

	size_t userId;
	std::cin >> userId;
	std::cout << "User: " << userList[userId].getName() << " history displayed " << std::endl;
	userList[userId].printWatchedMovies();
}
void AppManager::listUserTickets()
{
	size_t userId;
	std::cin >> userId;
	std::cout << "User: " << userList[userId].getName() << " tickets displayed " << std::endl;
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
	std::cout << "User: " << userList[userId].getName() << " removed " << std::endl;
}
