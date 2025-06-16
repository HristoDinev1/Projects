#include "MyString.h"

static unsigned RoundToPowerOfTwo(size_t n)
{
	n--;
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	n++;
	return n;
}

static size_t dataToAllocateForString(size_t length)
{
	return std::max(RoundToPowerOfTwo(length), 16u);
}

static const char* getSourcePtr(const MyString& str)
{
	return (str.isSSO()) ? str.SSO_buffer : str.data;
}

static char* getDestinationPtr(MyString& str)
{
	return (str.isSSO()) ? str.SSO_buffer : str.data;
}

static void AllocateMemory(char*& data, unsigned capacity)
{
	data = new (std::nothrow) char[capacity];
	if (data == nullptr) throw std::bad_alloc();
}

void MyString::AllocateAndCopy(const char* str)
{
	size_t strSize = strlen(str) + 1;
	if (strSize <= SSO_BUFFER_SIZE)
	{
		this->_capacity = SSO_BUFFER_SIZE;
		memcpy(SSO_buffer, str, strSize);
	}
	else
	{
		this->_capacity = dataToAllocateForString(strSize);
		AllocateMemory(this->data, _capacity);
		memcpy(data, str, strSize);
	}
	this->_size = strSize;
}

void MyString::CopyFrom(const MyString& other)
{
	if (other.isSSO())
	{
		memcpy(this->SSO_buffer, other.SSO_buffer, other._size);
	}
	else
	{
		AllocateMemory(this->data, other._capacity);
		memcpy(this->data, other.data, other._capacity);
	}
	this->_size = other._size;
	this->_capacity = other._capacity;
}

void MyString::MoveFrom(MyString&& other)
{
	if (other.isSSO()) // find a better way to move
	{
		memcpy(this->SSO_buffer, other.SSO_buffer, SSO_BUFFER_SIZE);
	}
	else
	{
		this->data = other.data;
		other.data = nullptr;
	}

	this->_size = other._size;
	this->_capacity = other._capacity;

	other._size = 0;
	other._capacity = 0;
}

void MyString::free()
{
	if (!isSSO())
	{
		delete[] data;
		data = nullptr;
	}
	_capacity = 0;
	_size = 0;
}

bool MyString::isSSO() const
{
	return _capacity <= SSO_BUFFER_SIZE;
}


MyString::MyString() : MyString("")
{

}
MyString::MyString(const char* str)
{
	if (str == nullptr)
	{
		AllocateAndCopy("");
	}
	else
	{
		AllocateAndCopy(str);
	}
}
MyString::MyString(const MyString& other)
{
	CopyFrom(other);
}
MyString::MyString(MyString&& other) noexcept
{
	MoveFrom(std::move(other));
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		CopyFrom(other);
	}
	return *this;
}
MyString& MyString::operator=(MyString&& other) noexcept
{
	if (this != &other)
	{
		free();
		MoveFrom(std::move(other));
	}
	return *this;
}

MyString& MyString::operator=(const char* str)
{
	if (getSourcePtr(*this) != str)
	{
		free();
		AllocateAndCopy(str);
	}
	return *this;
}
MyString& MyString::operator+=(const MyString& other)
{
	(*this) = (*this) + other;
	return *this;
}

char& MyString::operator[](size_t index)
{
	if (index >= _size) throw std::out_of_range("Index out of string");
	return (isSSO()) ? SSO_buffer[index] : data[index];
}
const char& MyString::operator[](size_t index) const
{
	if (index >= _size) throw std::out_of_range("Index out of string");
	return (isSSO()) ? SSO_buffer[index] : data[index];
}

const char* MyString::c_str() const
{
	return getSourcePtr(*this);
}
size_t MyString::size() const
{
	return _size;
}

size_t MyString::length() const
{
	return _size - 1;
}

bool MyString::operator==(const MyString& other) const
{
	return strcmp(getSourcePtr(*this), getSourcePtr(other)) == 0;
}
bool MyString::operator!=(const MyString& other) const
{
	return !(*this == other);
}
bool MyString::operator<(const MyString& other) const
{
	return strcmp(getSourcePtr(*this), getSourcePtr(other)) == -1;
}
bool MyString::operator>(const MyString& other) const
{
	return strcmp(getSourcePtr(*this), getSourcePtr(other)) == 1;
}
bool MyString::operator>=(const MyString& other) const
{
	return  !(*this < other);
}
bool MyString::operator<=(const MyString& other) const
{
	return !(*this > other);
}

MyString::operator bool() const
{
	return _size > 1;
}

std::istream& operator>>(std::istream& stream, MyString& obj)
{
	char buffer[1024];
	stream >> buffer;
	obj = buffer;
	return stream;
}
std::ostream& operator<<(std::ostream& stream, const MyString& obj)
{
	stream << obj.c_str();
	return stream;
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString newStr;

	newStr._size = lhs._size + rhs._size - 1;
	newStr._capacity = dataToAllocateForString(newStr._size);

	if (newStr._capacity > MyString::SSO_BUFFER_SIZE)
	{
		AllocateMemory(newStr.data, newStr._capacity);
	}

	const char* lhsSource = getSourcePtr(lhs);
	const char* rhsSource = getSourcePtr(rhs);
	char* newStrSource = getDestinationPtr(newStr);

	memcpy(newStrSource, lhsSource, lhs._size - 1);
	memcpy(newStrSource + (lhs._size - 1) * sizeof(char), rhsSource, rhs._size);

	return newStr;
}

MyString::~MyString()
{
	free();
}