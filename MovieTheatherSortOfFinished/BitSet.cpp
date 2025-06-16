#pragma once
#include "BitSet.h"

void BitSet::CopyFrom(const BitSet& other)
{
	this->bucketCount = other.bucketCount;
	this->data = new (std::nothrow) uint8_t[other.bucketCount];
	if (data == nullptr) throw std::bad_alloc();
	std::fill(data, data + bucketCount, false);

	memcpy(this->data, other.data, other.bucketCount);
	this->N = other.N;
	

}
void BitSet::MoveFrom(BitSet&& other)
{
	this->data = other.data;
	this->N = other.N;
	this->bucketCount = other.bucketCount;

	other.data = nullptr;
	other.N = 0;
	other.bucketCount = 0;
}
void BitSet::free()
{
	delete[] data;
	data = nullptr;
	N = 0;
	bucketCount = 0;
}

unsigned BitSet::getBucketIndex(unsigned num) const
{
	return num / ELEMENTS_IN_BUCKET;
}
unsigned BitSet::getMask(unsigned num) const
{
	return 1 << (num % ELEMENTS_IN_BUCKET);
}

BitSet::BitSet(unsigned highestNumber) :N(highestNumber), bucketCount(highestNumber / ELEMENTS_IN_BUCKET + 1)
{
	this->data = new (std::nothrow) uint8_t[bucketCount];
	if (data == nullptr) throw std::bad_alloc();
	std::fill(data, data + bucketCount, false);
}
BitSet::BitSet(const BitSet& other)
{
	CopyFrom(other);
}
BitSet::BitSet(BitSet&& other) noexcept
{
	MoveFrom(std::move(other));
}
BitSet& BitSet::operator=(const BitSet& other)
{
	if (this != &other)
	{
		free();
		CopyFrom(other);
	}
	return *this;
}
BitSet& BitSet::operator=(BitSet&& other) noexcept
{
	if (this != &other)
	{
		free();
		MoveFrom(std::move(other));
	}
	return *this;
}

void BitSet::add(unsigned num)
{
	if (num > N) throw std::out_of_range("Number outside of Set");
	data[getBucketIndex(num)] |= getMask(num);
}
void BitSet::remove(unsigned num)
{
	if (num > N) throw std::out_of_range("Number outside of Set");
	data[getBucketIndex(num)] &= (~getMask(num));
}
bool BitSet::contains(unsigned num) const
{
	if (num > N) return false;
	return ((data[getBucketIndex(num)] & getMask(num)) != 0);
}
void BitSet::print() const
{
	for (size_t i = 0; i < bucketCount; i++)
	{
		for (size_t j = 0; j < ELEMENTS_IN_BUCKET; j++)
		{
			unsigned num = (i * ELEMENTS_IN_BUCKET) + j;
			if (num > N) break;
			std::cout << "Contains " << num << " : " << ((data[i] & (1 << j)) != 0) << std::endl;
		}
	}
}

BitSet::~BitSet()
{
	free();
}
void BitSet::clear()
{
	std::fill(data, data + bucketCount, false);
}
unsigned BitSet::MaxNum() const
{
	return N;
}