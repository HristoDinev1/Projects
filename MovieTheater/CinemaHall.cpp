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
			std::cout<<seats[i].contains(j)<<' ';
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

void CinemaHall::serialize(std::ofstream& out) const {
	out.write(reinterpret_cast<const char*>(&rows), sizeof(rows));
	out.write(reinterpret_cast<const char*>(&cols), sizeof(cols));

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			char c = seats[i].contains(j) ? '1' : '0';
			out.write(&c, sizeof(char));
		}
	}
}

void CinemaHall::deserialize(std::ifstream& in) {
	in.read(reinterpret_cast<char*>(&rows), sizeof(rows));
	in.read(reinterpret_cast<char*>(&cols), sizeof(cols));

	seats = MyVector<BitSet>(rows);

	for (size_t i = 0; i < rows; i++) {
		BitSet row(cols);

		for (size_t j = 0; j < cols; j++) {
			char c;
			in.read(&c, sizeof(char));
			if (c == '1') {
				row.add(j);  
			}
		}
		seats[i] = std::move(row);
	}
}

