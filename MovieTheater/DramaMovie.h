#pragma once
#include "Movie.h"

class DramaMovie : public Movie
{
public:
    DramaMovie();
    DramaMovie(std::string title, double rating, unsigned length, unsigned room, Date releaseDate, Date screenDate, Time startTime, Time endTime, bool hasComedyElements);
    void setHasComedyElements(bool hasComedyElements);
    bool getHasComedyElements() const;
    
    double calculatePrice() const override;
private:
    static constexpr double BASE_PRICE = 7;
    static constexpr double COMEDY_MODIFIER = 2.0;
    bool hasComedyElements;
};