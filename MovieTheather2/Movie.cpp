#include "Movie.h"

int Movie::nextId = 0;
Movie::Movie(const MyString& title, unsigned length, unsigned room, Date releaseDate, Date screenDate, Time startTime, Time endTime) :
	title(title), length(length), room(room), releaseDate(releaseDate), screenDate(screenDate), startTime(startTime), endTime(endTime) 
{
	this->id = nextId;
	nextId++;
}

int Movie::getId() const
{
	return this->id;
}
void Movie::print() const
{
	std::cout << this->title << std::endl;
	std::cout << this->screenDate.getDay() << "." << this->screenDate.getMonth()<<std::endl;
	std::cout << this->startTime.getHour() << ":" << this->startTime.getMinute() << std::endl;
}

void Movie::addRating(double newRating) {
	if (newRating < 1.0 || newRating > 5.0)
		throw std::invalid_argument("Rating must be between 1 and 5");

	totalRating += newRating;
	++ratingCount;
}

bool Movie::hasPassed() const {
	constexpr int TM_YEAR_OFFSET = 1900;   
	constexpr int TM_MONTH_OFFSET = 1;    

	std::tm movieTime = {};
	movieTime.tm_year = static_cast<int>(screenDate.getYear()) - TM_YEAR_OFFSET;
	movieTime.tm_mon = static_cast<int>(screenDate.getMonth()) - TM_MONTH_OFFSET;
	movieTime.tm_mday = static_cast<int>(screenDate.getDay());
	movieTime.tm_hour = static_cast<int>(endTime.getHour());
	movieTime.tm_min = static_cast<int>(endTime.getMinute());
	movieTime.tm_sec = 0;

	std::time_t movieEndEpoch = std::mktime(&movieTime);
	std::time_t now = std::time(nullptr);

	return movieEndEpoch < now;
}

void Movie::setTitle(const MyString& title)
{
	this->title = title;
}

void Movie::setRoom(unsigned room)
{
	this->room = room;
}
void Movie::setReleaseDate(Date releaseDate)
{
	this->releaseDate = releaseDate;
}
void Movie::setScreenDate(Date screenDate)
{
	this->screenDate = screenDate;
}
void Movie::setStartTime(Time startTime)
{
	this->startTime = startTime;
}
void Movie::setEndTime(Time endTime)
{
	this->endTime = endTime;
}
void Movie::setLength(unsigned length)
{
	this->length = length;
}


MyString Movie::getTitle() const
{
	return this->title;
}
double Movie::getRating() const
{
	return this->totalRating/ratingCount;
}
unsigned Movie::getRoom() const
{
	return this->room;
}
Date Movie::getScreenDate() const
{
	return this->screenDate;
}
Date Movie::getReleaseDate() const
{
	return this->releaseDate;
}
Time Movie::getEndTime() const
{ 
	return this->endTime;
} 
Time Movie::getStartTime() const
{
	return this->startTime;
}
unsigned Movie::getLength() const
{
	return this->length;
}

Genre Movie::getGenre() const
{
	return this->genre;
}

void Movie::serialize(std::ofstream& out) const
{
	out.write(reinterpret_cast<const char*>(&id), sizeof(id));
	size_t len = strlen(title.c_str());
	out.write(reinterpret_cast<const char*>(&len), sizeof(len));
	out.write(title.c_str(), len);

	out.write(reinterpret_cast<const char*>(&ratingCount), sizeof(ratingCount));
	out.write(reinterpret_cast<const char*>(&totalRating), sizeof(totalRating));

	out.write(reinterpret_cast<const char*>(&length), sizeof(length));
	out.write(reinterpret_cast<const char*>(&room), sizeof(room));

	unsigned day = releaseDate.getDay();
	unsigned month = releaseDate.getMonth();
	unsigned year = releaseDate.getYear();
	out.write(reinterpret_cast<const char*>(&day), sizeof(day));
	out.write(reinterpret_cast<const char*>(&month), sizeof(month));
	out.write(reinterpret_cast<const char*>(&year), sizeof(year));

	day = screenDate.getDay();
	month = screenDate.getMonth();
	year = screenDate.getYear();
	out.write(reinterpret_cast<const char*>(&day), sizeof(day));
	out.write(reinterpret_cast<const char*>(&month), sizeof(month));
	out.write(reinterpret_cast<const char*>(&year), sizeof(year));

	unsigned hour = startTime.getHour();
	unsigned minute = startTime.getMinute();
	out.write(reinterpret_cast<const char*>(&hour), sizeof(hour));
	out.write(reinterpret_cast<const char*>(&minute), sizeof(minute));

	hour = endTime.getHour();
	minute = endTime.getMinute();
	out.write(reinterpret_cast<const char*>(&hour), sizeof(hour));
	out.write(reinterpret_cast<const char*>(&minute), sizeof(minute));
}
void Movie::deserialize(std::ifstream& in)
{
	in.read(reinterpret_cast<char*>(&id), sizeof(id));
	in.read(reinterpret_cast<char*>(&genre), sizeof(genre));
	size_t len;
	in.read(reinterpret_cast<char*>(&len), sizeof(len));
	char* buffer = new char[len + 1];
	in.read(buffer, len);
	buffer[len] = '\0';
	title = MyString(buffer);
	delete[] buffer;

	in.read(reinterpret_cast<char*>(&ratingCount), sizeof(ratingCount));
	in.read(reinterpret_cast<char*>(&totalRating), sizeof(totalRating));

	in.read(reinterpret_cast<char*>(&length), sizeof(length));
	in.read(reinterpret_cast<char*>(&room), sizeof(room));

	unsigned day, month, year;
	in.read(reinterpret_cast<char*>(&day), sizeof(day));
	in.read(reinterpret_cast<char*>(&month), sizeof(month));
	in.read(reinterpret_cast<char*>(&year), sizeof(year));
	releaseDate.setDate(day, month, year);

	in.read(reinterpret_cast<char*>(&day), sizeof(day));
	in.read(reinterpret_cast<char*>(&month), sizeof(month));
	in.read(reinterpret_cast<char*>(&year), sizeof(year));
	screenDate.setDate(day,month,year);

	unsigned hour, minute;
	in.read(reinterpret_cast<char*>(&hour), sizeof(hour));
	in.read(reinterpret_cast<char*>(&minute), sizeof(minute));
	startTime.SetTime(hour,minute);

	in.read(reinterpret_cast<char*>(&hour), sizeof(hour));
	in.read(reinterpret_cast<char*>(&minute), sizeof(minute));
	endTime.SetTime(hour,minute);
}