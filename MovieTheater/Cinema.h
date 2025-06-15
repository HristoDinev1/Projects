#pragma once
#include <vector>
#include "PolymorphicPtr.hpp"
#include "Movie.h"
#include "CinemaHall.h"

class Cinema
{
public:
    Cinema() = default;

    void addHall(unsigned rows, unsigned colls);
    void removeHall(unsigned hallId);
    void printHall(unsigned hallId) const;

    void addMovie(); // genre
    void removeMovie();
private:
    std::vector<CinemaHall> halls;
    std::vector<PolymorphicPtr<Movie>> catalogue;

};