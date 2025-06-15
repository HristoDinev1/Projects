#pragma once
#include "ActionMovie.h"
#include "DramaMovie.h"
#include "DocumentaryMovie.h"
#include "MyString.h"

namespace MovieFactory
{
	Movie* create(const MyString& genre, const MyString& title, unsigned length, unsigned room, Date releaseDate, Date screenDate, Time startTime, Time endTime, uint8_t priceModifier);
}

