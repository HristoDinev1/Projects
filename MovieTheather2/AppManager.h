#pragma once
#include "Cinema.h"

#include "MyVector.hpp"
#include "User.h"
#include "MovieFactory.h"

class AppManager
{
public:
	static AppManager& getInstance();


	void initialize();
	void run();
	void save();

private:
	AppManager() = default;
	

	const MyString CINEMA_DATA_FILE = "CinemaData.txt";
	const MyString USER_DATA_FILE = "UserData.txt";

	Cinema cinema;
	MyVector<User> userList;

	size_t currentUserId;
	bool hasLoggedIn;

	void parseCommands();

	void Register();
	void Login();
	void buyTicket();
	void listMovies();
	void listTickets();
	void rateMovie();

	void addMovie();
	void openHall();
	void closeHaul();
	void updateMovie();
	void updateMovieHall();
	void listUserHistory();
	void listUserTickets();
	void listUsers();
	void removeUser();
	void removeMovie();
};

