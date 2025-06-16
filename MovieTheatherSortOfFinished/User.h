#pragma once
#include "MyVector.hpp"
#include "PolymorphicPtr.hpp"
#include "Movie.h"
#include "MyString.h"
#include <fstream>
#include "Cinema.h"

class User
{
public:
    User(const MyString& name, const MyString& password);
    User(const MyString& name, const MyString& password, bool hasAdminRights);

    bool validateLoginData(const MyString& name, const MyString& password);
    void buyTicket(const Movie& movie);
    void rate(double rating, Movie& movie); //mechanism to see if its in the movies

    void printWatchedMovies() const;
    void printTickets() const;

    void serialize(std::ofstream& out)const;
    void deserialize(std::ifstream& in, Cinema& allMovies);

    bool isAdmin() const;
    MyString getName() const;
private:
    bool hasAdminRights; // create logicC 
    MyString name;
    MyString password;
    double balance;
    MyVector<const Movie*> tickets;

};