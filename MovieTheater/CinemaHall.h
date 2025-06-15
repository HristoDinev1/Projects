#pragma once
#include <vector>
#include"PolymorphicPtr.hpp"
#include"Movie.h"
#include"BitSet.h"

class CinemaHall
{
public:
    CinemaHall(unsigned rows, unsigned cols);

    void printSeats() const;
    void takeSeat(unsigned row, unsigned col);
    void freeSeat(unsigned row, unsigned col);

private:
    std::vector<BitSet> seats;
    unsigned rows, cols;
};