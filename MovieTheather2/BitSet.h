#pragma once
#include <iostream>

class BitSet
{
public:
	BitSet(unsigned highestNumber);
	BitSet(const BitSet& other);
	BitSet(BitSet&& other) noexcept;
	BitSet& operator=(const BitSet& other);
	BitSet& operator=(BitSet&& other) noexcept;

	void add(unsigned num);
	void remove(unsigned num);
	bool contains(unsigned num) const;
	void clear();
	void print() const;
	unsigned MaxNum() const;

	~BitSet();
private:
	uint8_t* data;
	unsigned bucketCount;
	unsigned N;

	static constexpr unsigned ELEMENTS_IN_BUCKET = sizeof(bool) * 8;

	void CopyFrom(const BitSet& other);
	void MoveFrom(BitSet&& other);
	void free();

	unsigned getBucketIndex(unsigned num) const;
	unsigned getMask(unsigned num) const;
};