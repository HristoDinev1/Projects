#pragma once
#include "MyString.h"
#include "Date.h"
#include "Time.h"
#include <iostream>
#include <fstream>
#include <ctime> // to get current date and time to check if the movie has passed 

class Movie
{
public:
    Movie() = default;
    Movie(const MyString& title, unsigned length, unsigned room, Date releaseDate, Date screenDate, Time startTime, Time endTime);

    void setTitle(const MyString& title);
    void setRoom(unsigned room);
    void setReleaseDate(Date releaseDate);
    void setScreenDate(Date screenDate);
    void setStartTime(Time startTime);
    void setEndTime(Time endTime);
    void setLength(unsigned length);

    MyString getTitle() const;
    double getRating() const;
    unsigned getRoom() const;
    Date getScreenDate() const;
    Date getReleaseDate() const;
    Time getEndTime() const;
    Time getStartTime() const;
    unsigned getLength() const;

    void print() const;
    bool hasPassed() const;
    void addRating(double newRating);

    virtual void serialize(std::ofstream& out) const = 0;
    virtual void deserialize(std::ifstream& in) = 0;

    virtual Movie* clone() const = 0;

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
    MyString title;
    int ratingCount;
    double totalRating;
    unsigned length;
    unsigned room;
    Date releaseDate;
    Date screenDate;
    Time startTime;
    Time endTime;
};