#include "CommandParser.h"



CommandParser& CommandParser::getsInstance()
{
	static CommandParser instance;
	return instance;
}

void CommandParser::readCommand()
{
	MyString command;
	std::cin >> command;
	if (command == "register" || command == "Register" || command == "REGISTER")
	{

	}
	if (command == "login" || command == "LOGIN" || command == "Login")
	{

	}
	if (command == "exit" || command == "EXIT" || command == "Exit")
	{

	}
	if (command == "buy-ticket" || command == "Buy-Ticket" || command == "BUY-TICKET" || command == "Buy-ticket")
	{

	}
	if (command == "list-movies" || command == "List-Movies" || command == "LIST-MOVIES" || command == "List-movies")
	{

	}
	if (command == "rate-movie" || command == "Rate-Movie" || command == "RATE-MOVIE" || command == "Rate-movie")
	{

	}
	//admin commands
	if (command == "add-movie" || command == "Add-Movie" || command == "ADD-MOVIE" || command == "Add-movie")
	{

	}
	if (command == "open-haul" || command == "Open-Haul" || command == "OPEN-HAUL" || command == "Open-haul")//????? hall??????
	{

	}
	if (command == "remove-movie" || command == "Remove-Movie" || command == "REMOVE-MOVIE" || command == "Remove-movie")
	{

	}
	if (command == "close-haul" || command == "Close-Haul" || command == "CLOSE-HAUL" || command == "Close-haul")
	{

	}
	if (command == "update-movie" || command == "Update-Movie" || command == "UPDATE-MOVIE" || command == "Update-movie")
	{

	}
	if (command == "update-movie-hall" || command == "Update-Movie-Hall" || command == "UPDATE-MOVIE-HALL" || command == "Update-movie-hall")
	{

	}

}