#pragma once
#include"MyVector.hpp"
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

    void serialize(std::ofstream& out) const;
    void deserialize(std::ifstream& in);

private:
    MyVector<BitSet> seats;
    unsigned rows, cols;
};