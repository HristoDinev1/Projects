#pragma once
#include "Movie.h"

class DocumentaryMovie : public Movie
{
public:
    DocumentaryMovie();
    DocumentaryMovie(const MyString& title, unsigned length, unsigned room, Date releaseDate, Date screenDate, Time startTime, Time endTime, bool basedOnTrueEvents);
    
    void setBasedOnTrueEvents(bool basedOnTrueEvents);
    bool getBasedOnTrueEvents() const;
    double calculatePrice() const override;

    void serialize(std::ofstream& out) const override;
    void deserialize(std::ifstream& in) override;

    Movie* clone() const override;
private:
    static constexpr double BASE_PRICE = 5;
    static constexpr double TRUE_EVENT_MODIFIER = 3.0;
    enum class Theme
    {
        nature,
        history,
        person
    };
    Theme theme;
    bool basedOnTrueEvents;
};
