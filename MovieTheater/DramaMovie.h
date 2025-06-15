#pragma once
#include "Movie.h"

class DramaMovie : public Movie
{
public:
    DramaMovie();
    DramaMovie(const MyString& title, unsigned length, unsigned room, Date releaseDate, Date screenDate, Time startTime, Time endTime, bool hasComedyElements);
    void setHasComedyElements(bool hasComedyElements);
    bool getHasComedyElements() const;
    
    double calculatePrice() const override;

    void serialize(std::ofstream& out) const override;
    void deserialize(std::ifstream& in) override;

    Movie* clone() const override;
private:
    static constexpr double BASE_PRICE = 7;
    static constexpr double COMEDY_MODIFIER = 2.0;
    bool hasComedyElements;
};