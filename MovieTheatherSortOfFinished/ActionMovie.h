#pragma once
#include "Movie.h"

class ActionMovie : public Movie
{
public:
    ActionMovie(const MyString& title, unsigned length, unsigned room, Date releaseDate, Date screenDate, Time startTime, Time endTime, unsigned actionIntensity);
    ActionMovie();

    void setActionIntensity(uint8_t actionIntensity);
    uint8_t getActionIntensity() const;

    double calculatePrice() const override;

    void serialize(std::ofstream& out) const override;
    void deserialize(std::ifstream& in) override;

    Movie* clone() const override;
private:
    static constexpr uint8_t MAX_ACTION_INTENSITY = 20;
    static constexpr double BASE_PRICE = 9;
    static constexpr double ACTION_MODIFIER = 1.5;
    uint8_t actionIntensity;
};