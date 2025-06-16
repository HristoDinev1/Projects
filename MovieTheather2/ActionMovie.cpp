#include "ActionMovie.h"

ActionMovie::ActionMovie(const MyString& title, unsigned length, unsigned room, Date releaseDate, Date screenDate, Time startTime, Time endTime, uint8_t actionIntensity) : Movie(title, length, room, releaseDate, screenDate, startTime, endTime)
{
	if (actionIntensity > 20) throw std::out_of_range("actionIntensity incorrect construction value"); //add const max Acion intensity
	this->actionIntensity = actionIntensity;
	this->genre = Genre::Action;
}

ActionMovie::ActionMovie()
{
	this->genre = Genre::Action;
}

Movie* ActionMovie::clone() const
{
	return new ActionMovie(*this);
}

void ActionMovie::setActionIntensity(uint8_t actionIntensity)
{
	if (actionIntensity > 20) throw std::out_of_range("actionIntensity incorrect value");
	this->actionIntensity = actionIntensity;
}
uint8_t ActionMovie::getActionIntensity() const
{
	return this->actionIntensity;
}

double ActionMovie::calculatePrice() const
{
	return this->BASE_PRICE + this->actionIntensity * ACTION_MODIFIER;
}

void ActionMovie::serialize(std::ofstream& out) const
{
	Movie::serialize(out);
	out.write(reinterpret_cast<const char*>(&actionIntensity), sizeof(actionIntensity));
}
void ActionMovie::deserialize(std::ifstream& in)
{
	Movie::deserialize(in);
	in.read(reinterpret_cast<char*>(&actionIntensity), sizeof(actionIntensity));
}