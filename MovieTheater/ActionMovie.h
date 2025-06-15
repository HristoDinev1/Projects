#pragma once
#include "Movie.h"

class ActionMovie : public Movie
{
public:
    ActionMovie(std::string title, double rating, unsigned length, unsigned room, Date releaseDate, Date screenDate, Time startTime, Time endTime, uint8_t actionIntensity);
    ActionMovie();

    void setActionIntensity(uint8_t actionIntensity);
    uint8_t getActionIntensity() const;

    double calculatePrice() const override;
private:
    static constexpr double BASE_PRICE = 9;
    static constexpr double ACTION_MODIFIER = 1.5;
    uint8_t actionIntensity;
};