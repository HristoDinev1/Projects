#include <iostream>
#include <string>
#include <vector>


class Cinema
{
    //seats bitset array
    //movie het container  - catalogue
    //
};


class User
{
public:
    User(std::string name, std::string passowrd) : name(name), password(password), balance(0) {};
private:
    std::string name;
    std::string password;
    double balance;


};

class Administrator : public User
{

};


class Movie
{

public:
    virtual ~Movie();
private:
    std::string title;
    double rating;
    unsigned length;
    unsigned room;
    // date , начален и краен час
};

class ActionMovie : public Movie
{
public:
    virtual double calculatePrice() const = 0;
private:
    static constexpr double BASE_PRICE = 9;
    static constexpr double ACTION_MODIFIER = 1.5;
    uint8_t actionIntensity;
};


class DramaMovie : public Movie
{
public:
    double calculatePrice() const override;
private:
    static constexpr double BASE_PRICE = 7;
    static constexpr double COMEDY_MODIFIER = 2.0;
    bool hasComedyElements;
};

class DocumentaryMovie : public Movie
{
public:
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

class Ticket
{
    Movie* ticketTo;
    //date?
};














int main()
{
    std::cout << "Hello World!\n";
}