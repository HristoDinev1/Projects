#pragma once
#include "Movie.h"

class DocumentaryMovie : public Movie
{
public:
    DocumentaryMovie();
    DocumentaryMovie(std::string title, double rating, unsigned length, unsigned room, Date releaseDate, Date screenDate, Time startTime, Time endTime, bool basedOnTrueEvents);
    
    void setBasedOnTrueEvents(bool basedOnTrueEvents);
    bool getBasedOnTrueEvents() const;
    double calculatePrice() const override;
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
