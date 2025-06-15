#pragma once
class CommandParser
{
public:
	static CommandParser& getsInstance();
	void readCommand();
private:
	CommandParser() = default;


	void Register();
	void Login();
	void buyTicket();
	void listMovies();
	void listTickets();
	void rateMovie();
	void exit();

	void addMovie();
	void openHaul();
	void closeHaul();
	void updateMovie();
	void listUserHistory();
	void listUserTickets();
	void listUsers();
	void removeUser();
};

