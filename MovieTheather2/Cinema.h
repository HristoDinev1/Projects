#pragma once
#include "MyVector.hpp"
#include "PolymorphicPtr.hpp"
#include "Movie.h"
#include "CinemaHall.h"
#include "MovieFactory.h"

class Cinema
{
public:
    Cinema() = default;

    void addHall(unsigned rows, unsigned cols);
    void removeHall(unsigned hallId);
    void printHall(unsigned hallId) const;

    void addMovie(Movie* movie); // genre
    void removeMovie(size_t movieId);

    void printMovies()const ;
    void printPassedMovies() const;
    
    void serialize(std::ofstream& out) const;
    void deserialize(std::ifstream& in);

    Movie* getMovie(size_t movieId);
private:
    MyVector<CinemaHall> halls;
    MyVector<PolymorphicPtr<Movie>> catalogue;

};