#pragma once
#include "Cinema.h"
#include "CommandParser.h"
#include "MyVector.hpp"
#include "User.h"
#include "MovieFactory.h"

class AppManager
{
public:
	AppManager() = default;

	void initialize();
	void run();
	void save();

private:
	const MyString CINEMA_CONFIG_FILE = "CinemaConfig.txt";
	const MyString USER_CONFIG_FILE = "CinemaConfig.txt";

	Cinema cinema;
	CommandParser& commandParser;
	MyVector<User> userList;

	size_t currentUserId;


	void Register();
	void Login();
	void buyTicket();
	void listMovies();
	void listTickets();
	void rateMovie();
	void exit();

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

