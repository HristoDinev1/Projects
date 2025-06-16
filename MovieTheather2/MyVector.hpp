#pragma once
#include <iostream>

template <typename T>
class MyVector
{
public:
	MyVector();
	MyVector(size_t InitialSize);
	MyVector(const MyVector<T>& other);
	MyVector(MyVector<T>&& other) noexcept;
	MyVector<T>& operator=(const MyVector<T>& other);
	MyVector<T>& operator=(MyVector<T>&& other) noexcept;

	void push_back(const T& elem);
	void pop_back();
	void clear();

	size_t size() const;
	size_t capacity() const;

	const T& operator[](size_t index) const;
	T& operator[](size_t index);

	~MyVector();
private:
	char* data;
	size_t _size;
	size_t _capacity;

	void resize();
	void free();
	void CopyFrom(const MyVector<T>& other);
	void MoveFrom(MyVector<T>&& other);
};

template <typename T>
void MyVector<T>::resize()
{
	size_t newCap = (_capacity == 0) ? 1 : _capacity * 2;
	char* newData = new (std::nothrow) char[newCap * sizeof(T)];
	if (newData == nullptr) throw std::bad_alloc();
	for (size_t i = 0; i < _size; i++)
	{
		new (newData + i * sizeof(T)) T(std::move(*reinterpret_cast<T*>(data + i * sizeof(T))));
		reinterpret_cast<T*>(data + i * sizeof(T))->~T();

	}
	delete[] data;
	this->data = newData;
	this->_capacity = newCap;
}

template <typename T>
void MyVector<T>::free()
{
	if (data != nullptr)
	{
		for (size_t i = 0; i < _size; i++)
		{
			reinterpret_cast<T*>(data + i * sizeof(T))->~T();
		}
		delete[] data;
	}
	data = nullptr;
	_size = 0;
	_capacity = 0;
}

template <typename T>
void MyVector<T>::CopyFrom(const MyVector<T>& other)
{
	this->data = new (std::nothrow) char[other._capacity * sizeof(T)];
	if (data == nullptr) throw std::bad_alloc();

	for (size_t i = 0; i < other._size; i++)
	{
		new (this->data + i * sizeof(T)) T(*reinterpret_cast<T*>(other.data + i * sizeof(T)));
	}

	this->_capacity = other._capacity;
	this->_size = other._size;
}

template <typename T>
void MyVector<T>::MoveFrom(MyVector<T>&& other)
{
	this->data = other.data;
	this->_size = other._size;
	this->_capacity = other._capacity;

	other.data = nullptr;
	other._size = 0;
	other._capacity = 0;

}


template <typename T>
MyVector<T>::MyVector() : data(nullptr), _size(0), _capacity(0)
{

}

template <typename T>
MyVector<T>::MyVector(size_t InitialSize) : _size(InitialSize), _capacity(InitialSize)
{
	data = new char[InitialSize * sizeof(T)];
}

template <typename T>
MyVector<T>::MyVector(const MyVector<T>& other)
{
	CopyFrom(other);
}

template <typename T>
MyVector<T>::MyVector(MyVector<T>&& other) noexcept
{
	MoveFrom(std::move(other));
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other)
{
	if (this != &other)
	{
		free();
		CopyFrom(other);
	}
	return *this;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(MyVector<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		MoveFrom(std::move(other));
	}
	return *this;

}

template <typename T>
void MyVector<T>::push_back(const T& elem)
{
	if (_size == _capacity) resize();
	new (data + _size * sizeof(T)) T(elem);
	_size++;
}

template <typename T>
void MyVector<T>::pop_back()
{
	if (_size == 0) throw std::underflow_error("Vector is empty. ");
	_size--;
	reinterpret_cast<T*>(data + _size * sizeof(T))->~T();
}

template <typename T>
const T& MyVector<T>::operator[](size_t index) const
{
	if (index >= _size) throw std::out_of_range("Index out of range");
	return *reinterpret_cast<const T*>(data + index * sizeof(T));
}

template <typename T>
T& MyVector<T>::operator[](size_t index)
{
	if (index >= _size) throw std::out_of_range("Index out of range");
	return *reinterpret_cast<T*>(data + index * sizeof(T));
}


template <typename T>
MyVector<T>::~MyVector()
{
	free();
}

template <typename T>
size_t MyVector<T>::size() const
{
	return _size;
}

template <typename T>
size_t MyVector<T>::capacity() const
{
	return _capacity;
}

template <typename T>
void MyVector<T>::clear()
{
	free();
}