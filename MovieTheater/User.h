#pragma once
#include <string>
#include <vector>
#include "Ticket.h"
#include "PolymorphicPtr.hpp"
#include "Movie.h"

class User
{
public:
    User(std::string name, std::string password);

    bool validateLoginData(std::string name, std::string password);
    void buyTicket(Ticket* ticket);
    void printWatchedMovies() const;
    // rate a movie ?

private:
    std::string name;
    std::string password;
    double balance;
    std::vector<PolymorphicPtr<Ticket>> tickets;
    std::vector<PolymorphicPtr<Movie>> watchedMovies;

};