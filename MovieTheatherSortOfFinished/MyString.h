#pragma once
#include <iostream>

class MyString
{
public:
	MyString();
	MyString(const char* str);
	MyString(const MyString& other);
	MyString(MyString&& other) noexcept;

	MyString& operator=(const MyString& other);
	MyString& operator=(MyString&& other) noexcept;

	MyString& operator=(const char* str);
	MyString& operator+=(const MyString& other);

	char& operator[](size_t index);
	const char& operator[](size_t index) const;

	const char* c_str() const;
	size_t size() const;
	size_t length() const;

	bool operator==(const MyString& other) const;
	bool operator!=(const MyString& other) const;
	bool operator<(const MyString& other) const;
	bool operator>(const MyString& other) const;
	bool operator>=(const MyString& other) const;
	bool operator<=(const MyString& other) const;

	operator bool() const;

	friend std::istream& operator>>(std::istream& stream, MyString& obj);
	friend std::ostream& operator<<(std::ostream& stream, const MyString& obj);

	friend static const char* getSourcePtr(const MyString& str);
	friend static char* getDestinationPtr(MyString& str);

	friend MyString operator+(const MyString& lhs, const MyString& rhs);

	~MyString();
private:
	static constexpr size_t SSO_BUFFER_SIZE = 16;
	union
	{
		char* data;
		char SSO_buffer[SSO_BUFFER_SIZE];
	};

	size_t _size;
	size_t _capacity;

	void AllocateAndCopy(const char* str);
	void CopyFrom(const MyString& other);
	void MoveFrom(MyString&& other);
	void free();

	bool isSSO() const;
};
