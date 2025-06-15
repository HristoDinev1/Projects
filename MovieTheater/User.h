#pragma once
#include "MyVector.hpp"
#include "PolymorphicPtr.hpp"
#include "Movie.h"
#include "MyString.h"

class User
{
public:
    User(const MyString& name, const MyString& password);

    bool validateLoginData(const MyString& name, const MyString& password);
    void buyTicket(const Movie& movie);
    void rate(double rating, Movie& movie); //mechanism to see if its in the movies

    void printWatchedMovies() const;
    void printTickets() const;

    MyString getName() const;
private:
    MyString name;
    MyString password;
    double balance;
    MyVector<const Movie*> tickets;

};