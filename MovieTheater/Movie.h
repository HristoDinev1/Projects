#pragma once
#include <vector>
#include <string>
#include "Date.h"
#include "Time.h"
#include <iostream>

class Movie
{
public:
    Movie() = default;
    Movie(std::string title, double rating, unsigned length, unsigned room, Date releaseDate, Date screenDate, Time startTime, Time endTime);

    void setTitle(std::string title);
    void setRating(double rating);
    void setRoom(unsigned room);
    void setReleaseDate(Date releaseDate);
    void setScreenDate(Date screenDate);
    void setStartTime(Time startTime);
    void setEndTime(Time endTime);
    void setLength(unsigned length);

    std::string getTitle() const;
    double getRating() const;
    unsigned getRoom() const;
    Date getScreenDate() const;
    Date getReleaseDate() const;
    Time getEndTime() const;
    Time getStartTime() const;
    unsigned getLength() const;

    virtual double calculatePrice() const = 0;
    virtual ~Movie() = default;
protected:
    enum class Genre
    {
        Action,
        Documentary,
        Drama
    };
    Genre genre;

    Genre getGenre() const;
private:
    std::string title;
    double rating;
    unsigned length;
    unsigned room;
    Date releaseDate;
    Date screenDate;
    Time startTime;
    Time endTime;
};