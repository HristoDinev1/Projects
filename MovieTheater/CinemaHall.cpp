#include "CinemaHall.h"


CinemaHall::CinemaHall(unsigned rows, unsigned cols) :rows(rows), cols(cols)
{
	for (size_t i = 0; i < rows; i++)
	{
		seats.push_back(BitSet(cols));
	}
}

void CinemaHall::printSeats() const
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			std::cout<<seats[i].contains(j);
		}
		std::cout << std::endl;
	}
}
void CinemaHall::takeSeat(unsigned row, unsigned col)
{
	// seat already taken mechanism?
	seats[row].add(col);
}
void CinemaHall::freeSeat(unsigned row, unsigned col)
{
	seats[row].remove(col);
}